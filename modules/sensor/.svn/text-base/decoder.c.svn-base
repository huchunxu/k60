/**
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *
 *        @file     decoder.c
 *
 *        @brief    编码器硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/5/24  19：00
 *
 *        @author:  Cao Shen , caoshen.1992@gmail.com
 * =====================================================================================
 *  @0.1    Cao Shen   2012/5/24    create orignal file
 * =====================================================================================
 */

#include "decoder.h" 
#include "lptmr.h"

/**
 * 文件内部宏定义
 */
#define   DECODER_NUM    1        /**< 编码器的数量 */

/**
 *  编码器控制块
 */
typedef struct decoder_control_block {
    bool_t    openflag;           /**< 打开标志 */
    bool_t    errorflag;          /**< 错误标志 */
    volatile uint32_t value;
}DECB;

static DECB decb_table[DECODER_NUM];

/**
 *  编码器控制块和io口ID之间的转换
 */
#define  INDEX_DECODER(decoder_no)  ((uint_t)(decoder_no))
#define  get_decb(decoder_no)      (&(decb_table[INDEX_DECODER(decoder_no)]))


/** 
 * 编码器的ID方法定义
 */
#define   DECODER_NO_GET(motorid)    (motorid & 0x0000ffff)

static ER decoder_open_port(ID decoderid);

/* 全局变量 */
uint16_t	gl_curSpeed = 0;            /*show the current speed*/
uint32_t	gl_encoderTotal = 0;        /*accumulate the encoder*/
uint32_t	gl_distanceTotal = 0;       /*remeber the distance*/

/**
 *    @brief   编码器初始化
 */
void decoder_init(intptr_t exinf)
{
    uint_t i;
    DECB *p_decb;

    for (p_decb = decb_table, i = 0; i < DECODER_NUM; p_decb++, i++)
    {
        p_decb->openflag  = FALSE;
        p_decb->errorflag = E_SYS;
        p_decb->value     = 0;
    }
    
    /* 打开IO口 */
    decoder_open_port(DECODER);
}

/**
 *    @brief   打开decoder端口
 *
 *    @param   decoderid  电机的ID号
 *
 *    @return  ercd 错误码
 */
static ER decoder_open_port(ID decoderid)
{
    DECB *p_decb;
    ER ercd;
    ID decoder_no;

    decoder_no = DECODER_NO_GET(decoderid);

    if (!((0 <= decoder_no) && (decoder_no < DECODER_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    p_decb = get_decb(decoder_no);

    if (p_decb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
    	lptmr_pulse_capture_init(DECODER_PIN);
        p_decb->openflag = TRUE;
        ercd = E_OK;
    }

    return (ercd);
}

/**
 *    @brief   读取开关的值
 *
 *    @param   decoderid  编码器的ID号
 *
 *    @return  pulse_num  编码器的寄存器值
 */
volatile uint32_t decoder_read(ID decoderid)
{
    DECB *p_decb;
    ID decoder_no;
    volatile uint32_t pulse_num = 0;

    decoder_no = DECODER_NO_GET(decoderid);

    if (!((0 <= decoder_no) && (decoder_no < DECODER_NUM)))
    {
        return ((volatile uint32_t)E_ID); /* ID号错误 */
    }
    p_decb = get_decb(decoder_no);

    if (p_decb->openflag)
    { /* 检查是否已经打开 */
        pulse_num = LPTMR_CNR_REG(DECODER_CNT);                     //读LPTMR的CNT寄存器的值即当前编码器捕捉次数
        p_decb->value = pulse_num;
    }
    else
    {
        return ((volatile uint32_t)E_ILUSE);
    }

    return (pulse_num);
}

/**
 *    @brief   清零当前的计数值
 *
 *    @note  关闭lptmr寄存器的使能即可以清零，打开使能便重新从零开始计数。
 */
void decoder_clear(void)
{
	 	 LPTMR0_CSR &=(~ LPTMR_CSR_TEN_MASK);                        //关闭使能位
	 	 LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;                              //打开使能位
}

/**
 *    @brief   Calculate Current Speed and distance
 */
void calculateCurSpeed(void)
{
    uint32_t	encoderCurrent = 0;

    encoderCurrent = decoder_read(DECODER);
	gl_encoderTotal = gl_encoderTotal + encoderCurrent;
    gl_curSpeed = (encoderCurrent * 14) / 5 ;  //10ms

    decoder_clear();                   /*清零当前计数器*/

    gl_distanceTotal = (uint32_t)(gl_encoderTotal / DISTANCE_PRESCALE);  // cm
}
