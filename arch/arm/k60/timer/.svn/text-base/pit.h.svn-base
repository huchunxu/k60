/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     pit.h
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/3/24 20:52
 *
 *        @author  Cheng Peng ,312770398@qq.com
 *//* ==================================================================================
 *  @0.1    Cheng Peng 2012/3/24  create orignal file
 * =====================================================================================
 */
#ifndef PIT_H__
#define PIT_H__
/**
 * 头文件包含
 */
#include "common.h"

#define    PIT0    PIT_NO_GET(PIT_TIMER0)
#define    PIT1    PIT_NO_GET(PIT_TIMER1)
#define    PIT2    PIT_NO_GET(PIT_TIMER2)
#define    PIT3    PIT_NO_GET(PIT_TIMER3)

/* 定时器变量 */
extern vuint32_t pit_count;

/**   @brief  PIT初始化函数
 *    @param  pitno     定时器模块号   
 *    @param  timeout   设定时间的值  
*/
void pit_init(ID pitno, uint32_t timeout);

/**   
 *    @brief    Enable_PIT_Interrupt   使能PIT中断
 *    @param    pitno  定时器模块号 
 */
void pit_enable(ID pitno);

/**  
 *  @brief    使能PIT中断
 *  @param    pitno  定时器模块号 
 */
void pit_disable(ID pitno);

/**
 * @brief pit0中断函数
 */
void pit0_timer_handler(void);


#endif //PIT_H__
