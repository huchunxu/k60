/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     lptmr.c
 *
 *        @brief    lptmr定时器和脉冲捕捉相关函数
 *
 *        @version  0.1
 *        @date     2012/3/25 17:10:09
 *
 *        @author  Cao Shen , caoshen.1992@gmail.com
 *//* ==================================================================================
 *  @0.1    Cao Shen 2012/3/25  create orignal file
 * =====================================================================================
 */
#ifndef LPTMR_H_
#define LPTMR_H_

#include "common.h"

/**  设置捕引脚 */
#define   LPTMR_CAPTURE_PIN   PTC5     /**< 定义输入捕捉引脚PTA19、PTC5 */

/**  设置时钟 */
#define LPTMR_INTERNAL_CLOCK   0X00  /**< 定义内部时钟 */
#define LPTMR_LPO_CLOCK        0X01  /**< 定义LPO时钟 */

/**   
 *    @brief   lptmr     定时器初始化
 *
 *    @param   clock     时钟选择      
 *
 *    @return  E_OK         初始化成功
 *    @return  E_INIT       初始化失败 
 *
 *    @see    lptmr_registers_clear()  
 *    @note   在这个定时器中，由于产生不了小于35.6ms的基准定时，所以统一选择基准为50ms的定时。
 *            在移植过程中应该相应调整COMPARE寄存器和PSR寄存器中的预分频系数。  
 */ 
ER lptmr_timer_init(uint32_t clock);

/**   
 *    @brief   lptmr脉冲捕捉初始化
 *
 *    @param   pin       捕捉引脚      
 *
 *    @return  E_OK      初始化成功
 *    @return  E_PIN     初始化失败 
 *
 *    @see     lptmr_registers_clear() 
 *    @note    捕捉上升沿；捕捉一次lptmr计数器加1，到compare寄存器中的值后产生中断 
 *             移植过程中要注意根据捕捉的脉冲的频率来调整COMPARE寄存器的值，例如要捕捉频率为1000HZ的脉冲则该值设为1000.
 */ 
ER lptmr_pulse_capture_init(PIN pin);

/**   
 *    @brief   lptmr使能中断
 *    
 *    @see     enable_irq()
 *    @note    注意在中断使能中要调用common.c中的enable_irq()函数
 */ 
void lptmr_enable(void);

/**   
 *    @brief   lptmr关闭中断
 *    
 *    @see     disable_irq()
 *    @note    注意在中断使能中要调用common.c中的disable_irq()函数
 */
void lptmr_disable(void);

#endif /* LPTMR_H_ */
