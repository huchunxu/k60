/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2008-2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  The above copyright holders grant permission gratis to use,
 *  duplicate, modify, or redistribute (hereafter called use) this
 *  software (including the one made by modifying this software),
 *  provided that the following four conditions (1) through (4) are
 *  satisfied.
 *
 *  (1) When this software is used in the form of source code, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be retained in the source code without modification.
 *
 *  (2) When this software is redistributed in the forms usable for the
 *      development of other software, such as in library form, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be shown without modification in the document provided
 *      with the redistributed software, such as the user manual.
 *
 *  (3) When this software is redistributed in the forms unusable for the
 *      development of other software, such as the case when the software
 *      is embedded in a piece of equipment, either of the following two
 *       conditions must be satisfied:
 *
 *      (a) The above copyright notice, this use conditions, and the
 *          disclaimer shown below must be shown without modification in
 *          the document provided with the redistributed software, such as
 *              the user manual.
 *
 *      (b) How the software is to be redistributed must be reported to the
 *          TOPPERS Project according to the procedure described
 *          separately.
 *
 *  (4) The above copyright holders and the TOPPERS Project are exempt
 *      from responsibility for any type of damage directly or indirectly
 *      caused from the use of this software and are indemnified by any
 *      users or end users of this software from any and all causes of
 *      action whatsoever.
 *
 *  THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 *  THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 *  PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 *  TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 *  INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 */

/**
 * SIO driver(LPC2478)
 */

#ifndef TOPPERS_TARGET_SERIAL_H
#define TOPPERS_TARGET_SERIAL_H

#include "common.h"
#include "sysinit.h"

/**
 * the sio interrupt used by system log
 */
#define INHNO_SIO0        6     /**< handler no*/
#define INTNO_SIO0        6     /**< intno */
#define INTPRI_SIO0       -3    /**< interrupt priority */
#define INTATR_SIO0       0U    /**< interrupt attribute */

#define INHNO_SIO1        7     /**< handler no*/
#define INTNO_SIO1        7     /**< intno */
#define INTPRI_SIO1       -3    /**< interrupt priority */
#define INTATR_SIO1       0U    /**< interrupt attribute */

/**
 *  total num of sio port
 */
#define TNUM_SIOP       2   


#ifndef TOPPERS_MACRO_ONLY

/**
 *  sio control block definition 
 */
typedef struct sio_port_control_block   SIOPCB;

/**
 *  callback routine no
 */
#define SIO_RDY_SND 1U      /**< ready to send no */
#define SIO_RDY_RCV 2U      /**< ready to receive no */

/**
 * 串行通信寄存器及标志位定义
 */
#define ReSendStatusR(base)       ((base)->S1) //状态寄存器
#define ReSendDataR(base)         ((base)->D)  //数据寄存器

#define ReTestBit                  5            //接收缓冲区满标志位
#define SendTestBit                7            //发送缓冲区空标志位



/**     模块通道      端口          可选范围                             建议               */
#define UART0_RX    PTD6     /**< PTA1、PTA15、PTB16、PTD6          PTA1不要用（与Jtag冲突）*/
#define UART0_TX    PTD7     /**< PTA2、PTA14、PTB17、PTD7          PTA2不要用（与Jtag冲突）*/

#define UART1_RX    PTE1     /**< PTC3、PTE1 */
#define UART1_TX    PTE0     /**< PTC4、PTE0 */

#define UART2_RX    PTD2     /**< PTD2  */
#define UART2_TX    PTD3     /**< PTD3  */

#define UART3_RX    PTC16    /**< PTB10、PTC16、PTE5 */
#define UART3_TX    PTC17    /**< PTB11、PTC17、PTE4 */

#define UART4_RX    PTE25    /**< PTC14、PTE25 */
#define UART4_TX    PTE24    /**< PTC15、PTE24 */

#define UART5_RX    PTE9     /**< PTD8、PTE9 */
#define UART5_TX    PTE8     /**< PTD9、PTE8 */


#define  UART_BAUD_9600      9600
#define  UART_BAUD_19200     19200
#define  UART_BAUD_57600     57600
#define  UART_BAUD_115200    115200

#define  TARGET_UART_BAUD     UART_BAUD_57600
#define  TARGET_UART_CLK      BUS_CLK_50000

#define  SIO_PRI             2    /**< 串口优先级 */

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
extern ER uart_init (ID uart_no, uint32_t sys_clk, uint32_t baud);

/**
 *  @brief SIO initialize
 */
extern void sio_initialize(intptr_t exinf);

/**
 *  @brief SIO open
 */
extern SIOPCB *sio_opn_por(ID siopid, intptr_t exinf);

/**
 *  @brief SIO close
 */
extern void sio_cls_por(ID portid, SIOPCB *p_siopcb);

/**
 *  @brief sio interrupt handler
 */
extern void sio_handler0(void);
extern void sio_handler4(void);

/**
 *  @brief sio sendchar
 */
extern bool_t sio_snd_chr(SIOPCB *siopcb, char_t c);

/**
 *  @brief sio receive char
 */
extern int_t sio_rcv_chr(SIOPCB *siopcb);

/**
 *  @brief enable call back
 */
extern void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn);

/**
 *  @brief disable call back routine
 */
extern void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn);

/**
 *  @brief sio interrupt send
 */
extern void sio_irdy_snd(intptr_t exinf);

/**
 *  @brief sio interrupt receive
 */
extern void sio_irdy_rcv(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_SERIAL_H */
