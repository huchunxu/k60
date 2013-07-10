/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     serial.c
 *
 *        @brief    带双环缓冲的串行口通用模块实现
 *
 *        @version  0.1
 *        @date     2012/3/14 15:20:10
 *
 *        @author:  Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei   2012/3/14 create orignal file
 *  @0.2    Hu Chunxu 2012/3/21 成功移植到K60上
 * =====================================================================================
 */
#include "t_stddef.h"
#include "target_serial.h"
#include "serial.h"


#define TNUM_PORT 1                     /**< 串行口的数量 */

/**
 *  默认串行口缓存定义
 */
#ifndef SERIAL_RCV_BUFSZ1
#define SERIAL_RCV_BUFSZ1   256         /**< 串行口1的接收缓存大小 */
#endif /* SERIAL_RCV_BUFSZ1 */

#ifndef SERIAL_SND_BUFSZ1
#define SERIAL_SND_BUFSZ1   256         /**< 串行口1的发送缓存大小 */
#endif /* SERIAL_SND_BUFSZ1 */

static uint8_t  rcv_buffer1[SERIAL_RCV_BUFSZ1];  /**< 接受缓存 */
static uint8_t  snd_buffer1[SERIAL_SND_BUFSZ1];  /**< 发送缓存 */


#if TNUM_PORT >= 2                      /**< 串行口2相关定义 */

#ifndef SERIAL_RCV_BUFSZ2
#define SERIAL_RCV_BUFSZ2   256         /**< 串行口2的接收缓存大小 */
#endif /* SERIAL_RCV_BUFSZ2 */

#ifndef SERIAL_SND_BUFSZ2
#define SERIAL_SND_BUFSZ2   256         /**< 串行口2的发送缓存大小 */
#endif /* SERIAL_SND_BUFSZ2 */

static uint8_t  rcv_buffer2[SERIAL_RCV_BUFSZ2];
static uint8_t  snd_buffer2[SERIAL_SND_BUFSZ2];

#endif /* TNUM_PORT >= 2 */

#if TNUM_PORT >= 3                      /**< 串行口3相关定义 */

#ifndef SERIAL_RCV_BUFSZ3
#define SERIAL_RCV_BUFSZ3   256         /**< 串行口3的接收缓存大小 */
#endif /* SERIAL_RCV_BUFSZ3 */

#ifndef SERIAL_SND_BUFSZ3
#define SERIAL_SND_BUFSZ3   256         /**< 串行口3的发送缓存大小 */
#endif /* SERIAL_SND_BUFSZ3 */

static uint8_t  rcv_buffer3[SERIAL_RCV_BUFSZ3];
static uint8_t  snd_buffer3[SERIAL_SND_BUFSZ3];

#endif /* TNUM_PORT >= 3 */

/**
 *  流控制相关定义
 */
#define FC_STOP         '\023'      /**< Ctrl-S */
#define FC_START        '\021'      /**< Ctrl-Q */

#define BUFCNT_STOP(bufsz)      ((bufsz) * 3 / 4)   /**< 当缓存3/4满时，发送STOP */
#define BUFCNT_START(bufsz)     ((bufsz) / 2)       /**< 当缓存一半空时，发送START */

/**
 *  串行口初始化块
 */
typedef struct serial_port_initialization_block {
    uint_t rcv_bufsz;       /**< 接收缓存大小 */
    uint8_t *rcv_buffer;    /**< 接收缓存 */
    uint_t  snd_bufsz;      /**< 发送缓存大小 */
    uint8_t *snd_buffer;    /**< 发送缓存 */
} SPINIB;

static const SPINIB spinib_table[TNUM_PORT] = {
    { SERIAL_RCV_BUFSZ1, rcv_buffer1,
      SERIAL_SND_BUFSZ1, snd_buffer1 },
#if TNUM_PORT >= 2
    { SERIAL_RCV_BUFSZ2, rcv_buffer2,
      SERIAL_SND_BUFSZ2, snd_buffer2 },
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
    { SERIAL_RCV_BUFSZ3, rcv_buffer3,
      SERIAL_SND_BUFSZ3, snd_buffer3 },
#endif /* TNUM_PORT >= 3 */
};

/**
 *  串行口控制块
 */
typedef struct serial_port_control_block {
    const SPINIB *p_spinib;     /**< 串行口初始化块指针 */
    SIOPCB  *p_siopcb;          /**< 串行口硬件管理模块 */
    bool_t  openflag;           /**< 打开标志 */
    bool_t  errorflag;          /**< 错误标志 */
    uint_t  ioctl;              /**< IO控制 */

    uint_t  rcv_read_ptr;       /**< 接收缓存当前读指针 */
    uint_t  rcv_write_ptr;      /**< 接收缓存当前写指针 */
    uint_t  rcv_count;          /**< 接收缓存中数据数 */
    uint8_t rcv_fc_chr;         /**< 流控字符 */
    bool_t  rcv_stopped;        /**< 是否已发送STOP */
    bool_t  rcv_buf_empty;      /**< 接收缓存是否为空 */

    uint_t  snd_read_ptr;       /**< 发送缓存当前读指针 */
    uint_t  snd_write_ptr;      /**< 发送缓存当前写指针 */
    uint_t  snd_count;          /**< 发送缓存中的数据数 */
    bool_t  snd_stopped;        /**< 是否已接受STOP*/
    bool_t  snd_buf_full;       /**< 发送缓存是否为满 */
} SPCB;

static SPCB spcb_table[TNUM_PORT];

/**
 *  串行口控制块和串行口ID之间的转换
 */
#define INDEX_PORT(portid)  ((uint_t)((portid) - 1))
#define get_spcb(portid)    (&(spcb_table[INDEX_PORT(portid)]))

/**
 *  增加指针
 */
#define INC_PTR(ptr, bufsz)     { if (++(ptr) == (bufsz)) { (ptr) = 0; }}

/**
 * @brief 初始化例程
 */
void
serial_initialize(intptr_t exinf)
{
    uint_t  i;
    SPCB    *p_spcb;

    sio_initialize((intptr_t)(NULL));

    for (p_spcb = spcb_table, i = 0; i < TNUM_PORT; p_spcb++, i++) {
        p_spcb->p_spinib = &(spinib_table[i]);
        p_spcb->openflag = FALSE;
    }
    
    /*打开串口*/
    serial_opn_por(UART_NO_GET(UART_NO));
}

/**
 * @brief 打开串行口
 *
 * @param portid 串口的序号
 */
ER
serial_opn_por(ID portid)
{
    SPCB    *p_spcb;
    ER      ercd;

    if (!(0 <= portid && portid <= TNUM_PORT)) {
        return(E_ID);               /* ID号错误 */
    }
    p_spcb = get_spcb(portid);

    if (p_spcb->openflag) {         /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else {
        /*
         *  初始化变量，串行口模式：带回显，\n前附加\r, 流控接收和流控发
         *  送
         */
        p_spcb->ioctl = ((~IOCTL_ECHO) | IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV);

        p_spcb->rcv_read_ptr = p_spcb->rcv_write_ptr = 0U;
        p_spcb->rcv_count = 0U;
        p_spcb->rcv_fc_chr = '\0';
        p_spcb->rcv_stopped = FALSE;
        p_spcb->rcv_buf_empty = TRUE;

        p_spcb->snd_read_ptr = p_spcb->snd_write_ptr = 0U;
        p_spcb->snd_count = 0U;
        p_spcb->snd_stopped = FALSE;
        p_spcb->snd_buf_full = FALSE;

        /**
         *  硬件初始化
         */
        p_spcb->p_siopcb = sio_opn_por(portid, (intptr_t) p_spcb);

        /**
         *  允许接收回调函数，即允许接收中断
         */
        sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_RCV);
        p_spcb->openflag = TRUE;

        ercd = E_OK;
    }
    return(ercd);
}

/**
 * @brief 关闭串行口
 */
ER
serial_cls_por(ID portid)
{
    SPCB    *p_spcb;
    ER      ercd = E_OK;

    if (!(1 <= portid && portid <= TNUM_PORT)) {
        return(E_ID);               /* ID号参数检查 */
    }
    p_spcb = get_spcb(portid);

    if (!(p_spcb->openflag)) {      /* 是否已经关闭 */
        ercd = E_OBJ;
    }
    else {
        /**
         *  硬件关闭
         */
        sio_cls_por(portid, p_spcb->p_siopcb);
        p_spcb->openflag = FALSE;

    }

    return(ercd);
}

/**
 * @brief   发送一个字符到串行口
 *
 * @return  TRUE  发送成功
 * @return  FALSE 发送失败
 * @note    如果发送寄存器为空，则直接把待发字符填入串行口寄存器
 *          否则返回，把待发字符填入缓存
 */
Inline bool_t
serial_snd_chr(SPCB *p_spcb, uint8_t c)
{
    if (sio_snd_chr(p_spcb->p_siopcb, c)) {
        return(TRUE);
    }
    else {
        sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
        return(FALSE);
    }
}

/**
 * @brief  发送一个字符到串行口
 */
static void
serial_wri_chr(SPCB *p_spcb, uint8_t c)
{
    /*
     *  \n(LR)直接附加\r(CR)．
     */
    if (c == '\n' && (p_spcb->ioctl & IOCTL_CRLF) != 0U) {
        serial_wri_chr(p_spcb, '\r');
        /* 如果发送缓存已满则等待 */
        while (p_spcb->snd_buf_full);
    }
    /* 禁止中断发送 */
    DisableInterrupts;

    if (p_spcb->snd_count == 0U && !(p_spcb->snd_stopped)
                                && serial_snd_chr(p_spcb, c)) {
        /**
         *  如果直接送入了发送寄存器，则发送缓存肯定为空
         *  
         */
        p_spcb->snd_buf_full = FALSE;
    }
    else {
        /**
         *  否则待发数据进入发送缓存
         */
        p_spcb->p_spinib->snd_buffer[p_spcb->snd_write_ptr] = c;
        INC_PTR(p_spcb->snd_write_ptr, p_spcb->p_spinib->snd_bufsz);
        p_spcb->snd_count++;
        p_spcb->snd_buf_full = (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz);
    }

    /* 重新使能中断 */
    EnableInterrupts;
}

/**
 * @brief 向串行口发送数据
 */
ER_UINT
serial_wri_dat(ID portid, const uint8_t *buf, uint_t len)
{
    SPCB    *p_spcb;
    uint_t  wricnt = 0U;
    ER      ercd;

    if (!(0 <= portid && portid <= TNUM_PORT)) {
        return(E_ID);               /* 检查ID号 */
    }

    p_spcb = get_spcb(portid);
    if (!(p_spcb->openflag)) {      /* 是否已经打开 */
        return(E_OBJ);
    }
    if (p_spcb->errorflag) {        /* 错误状态检查 */
        return(E_SYS);
    }

    while (wricnt < len) {
        /* 如果发送缓存已满则等待 */
        while (p_spcb->snd_buf_full);
        serial_wri_chr(p_spcb, *buf++);
        wricnt++;
    }
    
    ercd = E_OK;

    return(wricnt > 0U ? (ER_UINT) wricnt : ercd);
}

/**
 * @brief 从串行口接收1个字符
 */
static void
serial_rea_chr(SPCB *p_spcb, uint8_t *p_c)
{
    
    /* 禁止中断 */
    DisableInterrupts;

    /**
     *  从接收缓存中取数据
     */
    *p_c = p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_read_ptr];
    INC_PTR(p_spcb->rcv_read_ptr, p_spcb->p_spinib->rcv_bufsz);
    p_spcb->rcv_count--;
    /* 接收缓存是否为空 */
    p_spcb->rcv_buf_empty = (p_spcb->rcv_count == 0U);

    /**
     *  是否应发送START字符
     */
    if (p_spcb->rcv_stopped && p_spcb->rcv_count
                                <= BUFCNT_START(p_spcb->p_spinib->rcv_bufsz)) {
        if (!serial_snd_chr(p_spcb, FC_START)) {
            p_spcb->rcv_fc_chr = FC_START;
        }
        p_spcb->rcv_stopped = FALSE;
    }
    
    /* 允许中断 */
    EnableInterrupts;
}

/**
 * @brief 从串行口中接收数据
 */
ER_UINT
serial_rea_dat(ID portid, uint8_t *buf, uint_t len)
{
    SPCB    *p_spcb;
    uint_t  reacnt = 0U;
    uint8_t c = '\0';       /* 变量初始化 */
    ER      ercd;
    
    if (!(0 <= portid && portid <= TNUM_PORT)) {
        return(E_ID);               /* ID号检查 */
    }

    p_spcb = get_spcb(portid);
    if (!(p_spcb->openflag)) {      /* 是否已经打开 */
        return(E_OBJ);
    }

    while (reacnt < len) {
        /* 如果接收缓存为空，则等待 */
        while (p_spcb->rcv_buf_empty);
        serial_rea_chr(p_spcb, &c);
        *buf++ = c;
        reacnt++;
        
        /**
         *  是否需要回显处理？
         */
        if ((p_spcb->ioctl & IOCTL_ECHO) != 0U) {
            /* 如果发送缓存已满则等待 */
            while (p_spcb->snd_buf_full);
            serial_wri_chr(p_spcb, c);
        }
    }
    ercd = E_OK;

    return(reacnt > 0U ? (ER_UINT) reacnt : ercd);
}

/**
 * @brief 串行口控制
 */
ER
serial_ctl_por(ID portid, uint_t ioctl)
{
    SPCB    *p_spcb;

    if (!(0 <= portid && portid <= TNUM_PORT)) {
        return(E_ID);               /* ID号检查 */
    }

    p_spcb = get_spcb(portid);
    if (!(p_spcb->openflag)) {      /* 是否已打开？ */
        return(E_OBJ);
    }
    
    p_spcb->ioctl = ioctl;
    return(E_OK);
}

/**
 * @brief 查询串行口状态
 */
ER
serial_ref_por(ID portid, T_SERIAL_RPOR *pk_rpor)
{
    SPCB    *p_spcb;

    if (!(0 <= portid && portid <= TNUM_PORT)) {
        return(E_ID);               /* ID号检查 */
    }

    p_spcb = get_spcb(portid);
    if (!(p_spcb->openflag)) {      /* 是否已经打开？ */
        return(E_OBJ);
    }

    pk_rpor->reacnt = p_spcb->rcv_count;
    pk_rpor->wricnt = p_spcb->snd_count;
    return(E_OK);
}

/**
 * @brief 串行口发送回调函数，该函数在串行口接收中断中被调用
 */
void
sio_irdy_snd(intptr_t exinf)
{
    SPCB    *p_spcb;

    p_spcb = (SPCB *) exinf;
    if (p_spcb->rcv_fc_chr != '\0') {
        /*
         *  发送流控字符
         */
        (void) sio_snd_chr(p_spcb->p_siopcb, p_spcb->rcv_fc_chr);
        p_spcb->rcv_fc_chr = '\0';
    }
    else if (!(p_spcb->snd_stopped) && p_spcb->snd_count > 0U) {
        /**
         *  从发送缓存中取字符发送
         */
        (void) sio_snd_chr(p_spcb->p_siopcb,
                    p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]);
        INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
        if (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz) {
            /* 发送缓存未满 */
            p_spcb->snd_buf_full = FALSE;
        }
        p_spcb->snd_count--;
    }
    else {
        /**
         *  没有后续需要发送的数据，禁止中断.
         */
        sio_dis_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
    }
}

/**
 * @brief 串行口接收回调函数，该函数在接收中断中被调用.
 */
void
sio_irdy_rcv(intptr_t exinf)
{
    SPCB    *p_spcb;
    char_t   c;

    p_spcb = (SPCB *) exinf;
    c = (char_t) sio_rcv_chr(p_spcb->p_siopcb);
    if ((p_spcb->ioctl & IOCTL_FCSND) != 0U && c == FC_STOP) {
        /**
         *  接收到流控字符，发送停止.
         */
        p_spcb->snd_stopped = TRUE;
    }
    else if (p_spcb->snd_stopped && (c == FC_START
                || (p_spcb->ioctl & IOCTL_FCANY) != 0U)) {
        /**
         *  接收到FC_START，开始发送
         */
        p_spcb->snd_stopped = FALSE;
        if (p_spcb->snd_count > 0U) {
            c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
            if (serial_snd_chr(p_spcb, c)) {
                INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
                if (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz) {
                    /* 发送缓存未满 */
                    p_spcb->snd_buf_full = FALSE;
                }
                p_spcb->snd_count--;
            }
        }
    }
    else if ((p_spcb->ioctl & IOCTL_FCSND) != 0U && c == FC_START) {
        /**
         *  丢弃流控字符
         */
    }
    else if (p_spcb->rcv_count == p_spcb->p_spinib->rcv_bufsz) {
        /**
         *   接收缓存已满，丢弃已接收到的数据。
         */
    }
    else {
        /**
         *  已接收到的数据送入接收缓存
         */
        p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_write_ptr] = c;
        INC_PTR(p_spcb->rcv_write_ptr, p_spcb->p_spinib->rcv_bufsz);
        if (p_spcb->rcv_count == 0U) {
            /* 接收缓存不为空 */
            p_spcb->rcv_buf_empty = FALSE;
        }
        p_spcb->rcv_count++;

        /**
         *  是否需要发送流控字符
         */
        if ((p_spcb->ioctl & IOCTL_FCRCV) != 0U && !(p_spcb->rcv_stopped)
                        && p_spcb->rcv_count
                            >= BUFCNT_STOP(p_spcb->p_spinib->rcv_bufsz)) {
            if (!serial_snd_chr(p_spcb, FC_STOP)) {
                p_spcb->rcv_fc_chr = FC_STOP;
            }
            p_spcb->rcv_stopped = TRUE;
        }
    }
}

/**
 * @brief 取出为尚未发送的字符
 */
bool_t
serial_get_chr(ID portid, uint8_t *p_c)
{
    SPCB    *p_spcb;

    if (0 <= portid && portid <= TNUM_PORT) {       /* ID号检查 */
        p_spcb = get_spcb(portid);
        if (p_spcb->openflag) {                 /* 是否已经打开 */
            if (p_spcb->snd_count > 0U) {
                *p_c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
                INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
                p_spcb->snd_count--;
                return(TRUE);
            }
        }
    }
    return(FALSE);
}

/**
 * @brief 接受一个字节数据
 */
uint8_t serial_get_char(ID portid)
{
    SPCB    *p_spcb;
    uint8_t c = '\0';       /* 变量初始化 */

    p_spcb = get_spcb(portid);

    if (!(p_spcb->rcv_buf_empty))
    {
        serial_rea_chr(p_spcb, &c);
    }

    return c;
}

