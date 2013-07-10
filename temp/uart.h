/*
 * =====================================================================================
 *
 *       Filename:  uart.c
 *
 *    Description:  uart header file
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

#ifndef __UART_H__
#define __UART_H__
    
/*-----------------------------------------------------------
 * Header Files
 *----------------------------------------------------------*/
#include "common.h"


/*-----------------------------------------------------------
 * Macro Definitions
 *----------------------------------------------------------*/
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

/*-----------------------------------------------------------
 * Function Declarations
 *----------------------------------------------------------*/
extern ER uart_init (uint32_t uart_no, uint32_t sys_clk, uint32_t baud);
extern int32_t uart_open(uint32_t uart_no);
extern int32_t uart_close(uint32_t uart_no);
//extern char_t  uart_getchar (uint32_t uart_no,uint8_t *p);
//extern ER uart_putchar (uint32_t uart_no, char_t ch);
//extern ER uart_read(uint32_t uart_no, uint8_t *buf, uint32_t len);
//extern ER uart_write(uint32_t uart_no, const uint8_t *buf, uint32_t len);
extern int32_t uart_ioclt(uint32_t uart_no, void *buf);
//extern ER uart_send_string(uint32_t uart_no, uint8_t *buff);
//extern void uart1_handler(void);
    
#endif
