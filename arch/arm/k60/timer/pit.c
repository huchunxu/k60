/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     pit.c
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/3/24 20:52
 *
 *        @author  Cheng Peng ,312770398@qq.com
 *//* ==================================================================================
 *  @0.1    Cheng Peng 2012/3/24  create orignal file
 *  @0.2    Hu Chunxu  2012/4/3   修改了代码结构
 * =====================================================================================
 */

#include "pit.h"
#include "exception.h"

/**
 * 全局变量定义
 */
vuint32_t pit_count;

/**   @brief  PIT初始化函数
 *    @param  pitno     定时器模块号   
 *    @param  timeout   设定时间的值  
*/
void pit_init(ID pitno, uint32_t timeout)
{
	SIM_SCGC6|=SIM_SCGC6_PIT_MASK;              /* 使能PIT时钟 */
	PIT_MCR&=~(PIT_MCR_MDIS_MASK);              /* 使能PIT模块时钟 */
	PIT_MCR|=PIT_MCR_FRZ_MASK;                  /* 调试模式下禁止 */
	PIT_LDVAL(pitno)=timeout;                   /* 设置周期 */
	PIT_TCTRL(pitno)|=PIT_TCTRL_TEN_MASK;       /* 使能pit模块运行 */
	PIT_TCTRL(pitno)&=~(PIT_TCTRL_TIE_MASK);    /* 关pit中断 */
	
    /* 中断向量表注册，中断优先级设置 */
	switch(PIT_ID_SET(pitno))
	{
        case PIT_TIMER0:
            exc_install(INT_PIT0, pit0_timer_handler);
            exc_set_pri(INT_PIT0, 1);
            break;
        case PIT_TIMER1:
            //exc_install(INT_PIT1, pit1_timer_handler);
            //exc_set_pri(INT_PIT1, 1);
            break;
        case PIT_TIMER2:
            //exc_install(INT_PIT2, pit2_timer_handler);
            //exc_set_pri(INT_PIT2, 1);
            break;
        case PIT_TIMER3:
            //exc_install(INT_PIT3, pit3_timer_handler);
            //exc_set_pri(INT_PIT3, 1);
            break;
        default:
            break;
	}
}
    
/**   
 *    @brief    Enable_PIT_Interrupt   使能PIT中断
 *    @param    pitno  定时器模块号 
 */
void pit_enable(ID pitno)
{
	PIT_TCTRL(pitno) |= (PIT_TCTRL_TIE_MASK); /* 开pit中断 */
    exc_enable(INT_PIT0 + pitno);           /* 开接收引脚的IRQ中断 */
}

/**  
 *  @brief    使能PIT中断
 *  @param    pitno  定时器模块号 
 */
void pit_disable(ID pitno)
{
	PIT_TCTRL(pitno) &= ~(PIT_TCTRL_TIE_MASK); /* 关pit中断 */
    exc_disable(INT_PIT0 + pitno);           /* 关接收引脚的IRQ中断 */
}

/**
 * @brief pit0中断函数
 */
void pit0_timer_handler(void)
{ 
    if((PIT_TFLG(0)&PIT_TFLG_TIF_MASK)!=0)
    {
        pit_count++;  
        PIT_TFLG(0)|=PIT_TFLG_TIF_MASK;       /* 清标志 */
    }
}
