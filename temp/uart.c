/*
 * =====================================================================================
 *
 *       Filename:  uart.c
 *
 *    Description:  uart driver file
 *
 *        Version:  0.1
 *        Created:  2012/2/14 15:35:40
 *
 *         Author:  Hu Chunxu , hcx196@gmail.com
 *        Company:  HUST-Renesas Lab
 *       Revision:
 * =====================================================================================
 *  @0.1    Hu Chunxu   2012/2/14   create orignal file
 * =====================================================================================
 */

/*-----------------------------------------------------------
 * Header Files
 *----------------------------------------------------------*/
#include <string.h>
#include "uart.h"
#include "sysinit.h"
#include "exception.h"

/*-----------------------------------------------------------
 * Local Definitions And Declarations
 *----------------------------------------------------------*/
static UART_MemMapPtr  uart_get_base_address(uint32_t uart_no);


/*-----------------------------------------------------------
 * Main Function
 *----------------------------------------------------------*/

/**
 *    @brief   串口初始化
 *
 *    @param   uart_no 串口号
 *    @param   sys_clk  系统总线时钟，以KHz为单位
 *    @param   baud    波特率，如9600，38400等，一般来说，速度越慢，通信越稳
 *
 *    @return  0     初始化成功
 *    @return  1     初始化失败
 *
 *    @note
 */
ER uart_init (uint32_t uart_no, uint32_t sys_clk, uint32_t baud)
{
    register uint32_t sbr, brfa;
    uint8_t temp;

    /* 配置UART功能的GPIO接口 开启时钟 */
    switch(uart_no)
    {
        case UART0:
            if(UART0_RX==PTA1)
                PORTA_PCR1 = PORT_PCR_MUX(0x2);      /* 在PTA1上使能UART0_RXD */
            else if(UART0_RX==PTA15)
                PORTA_PCR15 = PORT_PCR_MUX(0x3);     /* 在PTA15上使能UART0_RXD */
            else if(UART0_RX==PTB16)
                PORTB_PCR16 = PORT_PCR_MUX(0x3);     /* 在PTB16上使能UART0_RXD */
            else if(UART0_RX==PTD7)
                PORTD_PCR7 = PORT_PCR_MUX(0x3);      /* 在PTD7上使能UART0_RXD */
            else
                return E_PIN;

            if(UART0_TX==PTA2)
                PORTA_PCR2 = PORT_PCR_MUX(0x2);      /* 在PTA2上使能UART0_RXD */
            else if(UART0_TX==PTA14)
                PORTA_PCR14 = PORT_PCR_MUX(0x3);     /* 在PTA14上使能UART0_RXD */
            else if(UART0_TX==PTB17)
                PORTB_PCR17 = PORT_PCR_MUX(0x3);     /* 在PTB17上使能UART0_RXD */
            else if(UART0_TX==PTD6)
                PORTD_PCR6 = PORT_PCR_MUX(0x3);      /* 在PTD6上使能UART0_RXD */
            else
                return E_PIN;

            SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;       /* 使能 UARTn 时钟 */

            /*exc_install(INT_UART0_RX_TX, uart0_handler);
            exc_set_pri(INT_UART0_RX_TX, 1);*/
            break;

        case UART1:
            if(UART1_RX==PTC3)
                PORTC_PCR3 = PORT_PCR_MUX(0x3);      /* 在PTC3上使能UART1_RXD */
            else if(UART1_RX==PTE1)
                PORTE_PCR1 = PORT_PCR_MUX(0x3);      /* 在PTE1上使能UART1_RXD */
            else
                return E_PIN;

            if(UART1_TX==PTC4)
                PORTC_PCR4 = PORT_PCR_MUX(0x3);      /* 在PTC4上使能UART1_RXD */
            else if(UART1_TX==PTE0)
                PORTE_PCR0 = PORT_PCR_MUX(0x3);      /* 在PTE0上使能UART1_RXD */
            else
                return E_PIN;

            SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;

            //exc_install(INT_UART1_RX_TX, uart1_handler);
            //exc_set_pri(INT_UART1_RX_TX, 1);
            break;

        case UART2:
            PORTD_PCR3 = PORT_PCR_MUX(0x3);         /* 在PTD3上使能UART2_TXD功能 */
            PORTD_PCR2 = PORT_PCR_MUX(0x3);         /* 在PTD2上使能UART2_RXD */
            SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;

            /*exc_install(INT_UART2_RX_TX, uart2_handler);
            exc_set_pri(INT_UART2_RX_TX, 1);*/
            break;

        case UART3:
            if(UART3_RX==PTB10)
                PORTB_PCR10 = PORT_PCR_MUX(0x3);     /* 在PTB10上使能UART3_RXD */
            else if(UART3_RX==PTC16)
                PORTC_PCR16 = PORT_PCR_MUX(0x3);     /* 在PTC16上使能UART3_RXD */
            else if(UART3_RX==PTE5)
                PORTE_PCR5 = PORT_PCR_MUX(0x3);      /* 在PTE5上使能UART3_RXD */
            else
                return E_PIN;

            if(UART3_TX==PTB11)
                PORTB_PCR11 = PORT_PCR_MUX(0x3);     /* 在PTB11上使能UART3_RXD */
            else if(UART3_TX==PTC17)
                PORTC_PCR17 = PORT_PCR_MUX(0x3);     /* 在PTC17上使能UART3_RXD */
            else if(UART3_TX==PTE4)
                PORTE_PCR4 = PORT_PCR_MUX(0x3);      /* 在PTE4上使能UART3_RXD */
            else
                return E_PIN;

            SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;

            /*exc_install(INT_UART3_RX_TX, uart3_handler);
            exc_set_pri(INT_UART3_RX_TX, 1);*/

            break;

        case UART4:
            if(UART4_RX==PTC14)
                PORTC_PCR14 = PORT_PCR_MUX(0x3);     /* 在PTC14上使能UART4_RXD */
            else if(UART4_RX==PTE25)
                PORTE_PCR25 = PORT_PCR_MUX(0x3);     /* 在PTE25上使能UART4_RXD */
            else
                return E_PIN;

            if(UART4_TX==PTC15)
                PORTC_PCR15 = PORT_PCR_MUX(0x3);     /* 在PTC15上使能UART4_RXD */
            else if(UART4_TX==PTE24)
                PORTE_PCR24 = PORT_PCR_MUX(0x3);     /* 在PTE24上使能UART4_RXD */
            else
                return E_PIN;

            SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;

            /*exc_install(INT_UART1_RX_TX, uart4_handler);
            exc_set_pri(INT_UART1_RX_TX, 1);*/
            break;

        case UART5:
            if(UART5_RX==PTD8)
                PORTD_PCR8 = PORT_PCR_MUX(0x3);     /* 在PTD8上使能UART5_RXD */
            else if(UART5_RX==PTE9)
                PORTE_PCR9 = PORT_PCR_MUX(0x3);     /* 在PTE9上使能UART5_RXD */
            else
                return E_PIN;

            if(UART5_TX==PTD9)
                PORTD_PCR9 = PORT_PCR_MUX(0x3);     /* 在PTD9上使能UART5_RXD */
            else if(UART5_TX==PTE8)
                PORTE_PCR8 = PORT_PCR_MUX(0x3);     /* 在PTE8上使能UART5_RXD */
            else
                return E_PIN;

            SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;

            /*exc_install(INT_UART5_RX_TX, uart5_handler);
            exc_set_pri(INT_UART5_RX_TX, 1);*/
            break;
        default:
            return E_PAR;
            break;
    }

    /* 获取串口的基址 */
    UART_MemMapPtr uart_ch = uart_get_base_address(uart_no);

    /* 禁止发送接受 */
    UART_C2_REG(uart_ch) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );

    /*  配置成8位无校验模式
     ** 设置UART数据格式、校验方式和停止位位数。通过设置UART模块控制寄存器C1实现 */
    UART_C1_REG(uart_ch) = 0;

    /* 计算波特率，串口0、1使用内核时钟，其它串口使用外设时钟，系统时钟为外设时钟的2倍 */
    if ((uart_ch == UART0_BASE_PTR) | (uart_ch == UART1_BASE_PTR))
    {
        sys_clk = sys_clk * 2000;    /* 内核时钟 换算单位 --> khz */
    }
    else
    {
        sys_clk = sys_clk * 1000;    /* 内部总线时钟 换算单位 --> khz */
    }

    /* 设置 UART 数据通讯波特率。通过设置 UART 模块的波特率寄存器 */
    sbr = (uint16_t)((sys_clk)/(baud << 4));

    /* Save off the current value of the UARTx_BDH except for the SBR field */
    temp = UART_BDH_REG(uart_ch) & ~(UART_BDH_SBR(0x1F));

    UART_BDH_REG(uart_ch) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(uart_ch) = (uint8_t)(sbr & UART_BDL_SBR_MASK);

    /* Determine if a fractional divider is needed to get closer to the baud rate
     **brfa = (((sys_clk*32000)/(baud * 16)) - (sbr * 32))  */
    brfa = (((sys_clk << 5)/(baud << 4)) - (sbr << 5));

    /* Save off the current value of the UARTx_C4 register except for the BRFA field */
    temp = UART_C4_REG(uart_ch) & ~(UART_C4_BRFA(0x1F));

    UART_C4_REG(uart_ch) = temp |  UART_C4_BRFA(brfa);

    /* 允许发送和接收 */
    UART_C2_REG(uart_ch) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

    /*  设置是否允许接收和发送中断。通过设置 UART 模块的 C2 寄存器的
     ** RIE 和 TIE 位实现。如果使能中断，必须首先实现中断服务程序 */

    return E_OK;
}

/**
 *    @brief   打开串口
 *
 *    @param   uart_no   串口号
 *
 *    @return  0     初始化成功
 *    @return  1     初始化失败
 *
 *    @note
 */
int32_t uart_open(uint32_t uart_no)
{
    /* 获取串口的基址 */
    UART_MemMapPtr uart_ch = uart_get_base_address(uart_no);

    /* 开放UART接收中断 */
    UART_C2_REG(uart_ch)|=UART_C2_RIE_MASK;

    /* 开接收引脚的IRQ中断 */
    exc_enable(INT_UART0_RX_TX + (UART_NO_GET(uart_no) << 1));

    return E_OK;
}


/**
 *    @brief   关闭串口
 *
 *    @param   uart_no   串口号
 *
 *    @return  0     初始化成功
 *    @return  1     初始化失败
 *
 *    @note
 */
int32_t uart_close(uint32_t uart_no)
{
    /* 获取串口的基址 */
    UART_MemMapPtr uart_ch = uart_get_base_address(uart_no);

    /* 禁止UART接收中断 */
    UART_C2_REG(uart_ch)&=~UART_C2_RIE_MASK;

    /* 关接收引脚的IRQ中断 */
    exc_disable(INT_UART0_RX_TX + (UART_NO_GET(uart_no) << 1));

    return E_OK;
}


/**
 *    @brief   串行接受1个字节
 *
 *    @param   uart_no  串口号
 *    @param   p        接收成功标志的指针(0表示成功，1表示不成功)
 *
 *    @return  i     返回数据
 *
 *    @note  参数*p带回接收标志，*p = 0，收到数据；*p = 1，未收到数据
 */
//char_t uart_getchar (uint32_t uart_no,uint8_t *fp)
//{
//    unsigned long int time;
//    uint8_t  dat;
//
//    /* 获取串口的基址 */
//    UART_MemMapPtr uart_ch = uart_get_base_address(uart_no);
//
//    for (time = 0; time<0xfbbb; time++)/* 查询指定次数 */
//    {
//        /* 判断接收缓冲区是否满 */
//      if ((ReSendStatusR(uart_ch) & (1<<ReTestBit)) != 0)
//      {
//          dat = ReSendDataR(uart_ch);
//          *fp = 0x00;  /* 收到数据 */
//          break;
//      }
//    }
//  if(time >= 0xfbbb)
//  {
//      /* 未收到数据 */
//      dat = 0xff;
//      *fp = E_DROUT;
//  }
//
//    return dat;                              //返回接收到的数据
//}



/**
 *    @brief   串行发送1个字节
 *
 *    @param   uart_no  串口号
 *    @param   ch      要发送的字节
 *
 *    @return  无
 *
 *    @note
 */
/*

//ER uart_putchar (uint32_t uart_no, char_t ch)
//{
//  uint32_t time = 0;
//
//  /* 获取串口的基址 
//  UART_MemMapPtr uart_ch = uart_get_base_address(uart_no);
//
//  for (time = 0; time < 0xFBBB; time++)       /* 有次数限制 */
//  {
//      /* 判断发送缓冲区是否为空 */
//      if ((ReSendStatusR(uart_ch) & (1<<SendTestBit)) != 0)
//      {
//          ReSendDataR(uart_ch) = ch;
//          break;
//      }
//  }
//
//  if (time >= 0xFBBB)
//        return E_DSOUT; /* 发送超时 */
//    else
//        return E_OK;    /* 成功发送 */
//}
//


/**
 *    @brief   串行接收n个字节
 *
 *    @param   uart_no  串口号
 *    @param   buf      接收缓冲区
 *    @param   len      接收长度
 *
 *    @return  E_OK    数据接受成功
 *    @return  1     初始化失败
 *
 *    @note
 */
//ER uart_read(uint32_t uart_no, uint8_t *buf, uint32_t len)
//{
//    uint32_t i;
//    uint8_t flag = 0;
//
//    for (i = 0; i < len; i++)           /* 接收n个数据 */
//    {
//      buf[i] = uart_getchar(uart_no, &flag);
//
//      /* 只要有1个字节数据没接收到就返回报错 */
//      if (flag == E_DROUT) return E_DROUT;
//    }
//
//    return E_OK;
//}



/**
 *    @brief   串行发送n个字节
 *
 *    @param   uart_no  串口号
 *    @param   buf      接收缓冲区
 *    @param   len      接收长度
 *
 *    @return  0     初始化成功
 *    @return  1     初始化失败
 *
 *    @note
 */
//ER uart_write(uint32_t uart_no, const uint8_t *buf, uint32_t len)
//{
//  int i;
//  for(i=0;i<len;i++)
//  {
//      if(uart_putchar(uart_no,buf[i]))
//      {
//          break;
//      }
//  }
//
//  if (i == len)
//      return E_OK;      /* 发送成功 */
//  else
//      return E_DSOUT;   /* 发送失败 */
//}


/**
 *    @brief   从指定UART端口发送一个以'\0'结束的字符串
 *
 *    @param   uart_no  串口号
 *    @param   buf      接收缓冲区
 *
 *    @return  无
 *
 *    @note    字符串的长度范围从0到65535,内部调用了uart_putchar函数
 */
//ER uart_send_string(uint32_t uart_no, uint8_t *buff)
//{
//  unsigned short int i = 0;
//
//    for(i = 0;buff[i] != '\0';i++)
//    {
//      /* 从指定UART端口发送字符串数据 */
//      if(uart_putchar(uart_no,buff[i]))
//          return E_DSOUT;
//    }
//
//    return E_OK;
//}


/**
 *    @brief   串口io控制
 *
 *    @param   uart_no  串口号
 *    @param   buf      接收缓冲区
 *
 *    @return
 *
 *    @note
 */
int32_t uart_ioclt(uint32_t uart_no, void *buf)
{
     while(1);
}


/**
 *    @brief uart1接收数据的中断函数
 */
//void uart1_handler(void)
//{
//  uint8_t ch;
//  uint8_t flag = 1;
//
//  DisableInterrupts;
//
//  ch = uart_getchar(UART1, &flag);
//  if (0 == flag)
//  {
//      uart_putchar(UART1, ch);
//  }
//
//  EnableInterrupts;
//}



/**
 * @brief 获取串口的基址
 *
 * @param uart_no 串口号
 *
 * @return 串口的基址值
 */
static UART_MemMapPtr uart_get_base_address(uint32_t uart_no)
{
    switch(uart_no)
    {
        case UART0:
            return UART0_BASE_PTR;
            break;
        case UART1:
            return UART1_BASE_PTR;
            break;
        case UART2:
            return UART2_BASE_PTR;
            break;
        case UART3:
            return UART3_BASE_PTR;
            break;
        case UART4:
            return UART4_BASE_PTR;
            break;
        case UART5:
            return UART5_BASE_PTR;
            break;
        default :
            return NULL;
    }
}

