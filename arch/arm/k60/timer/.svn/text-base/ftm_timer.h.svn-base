/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     ftm_timer.h
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/3/18 14:14:45
 *
 *        @author   Cao Shen , caoshen.1992@gmail.com
 *//* ==================================================================================
 *  @0.1    Cao Shen 2012/3/18  create orignal file
 * =====================================================================================
 */
#ifndef FTM_TIMER_H_
#define FTM_TIMER_H_

/**
 * 头文件包含
 */

#include "common.h"


/* 定时器变量 */
extern volatile uint32_t ftm_count;


/**
 *    @brief ftm定时器初始化 周期：1ms
 *
 *    @param   ftm_module ftm定时器模块号
 *
 *    @return  0     初始化成功
 *    @return  1     初始化失败
 *
 *    @note   移植完毕后要根据加载的时钟相应的调整FTM_MOD寄存器中的值和分频值FTM_SC_PS_X
 */
extern ER ftm_timer_init(uint32_t ftm_module);

/**
 *    @brief   停止ftm定时器
 *
 *    @param   ftm_module ftm定时器模块号
 *    @note    未选择任何时钟
 */
extern void ftm_timer_stop(uint32_t ftm_module);

/**
 * 	  @brief   ftm定时器中断使能
 *
 *    @param   ftm_module ftm定时器模块号
 *
 *    @note
 */
extern void ftm_timer_enable(uint32_t ftm_module);

/**
 *    @brief   ftm定时器中断除能
 *
 *    @param   ftm_module ftm定时器模块号
 *
 *    @note
 */
extern void ftm_timer_disable(uint32_t ftm_module);

/**
 *    @brief ftm0定时器中断函数
 */
extern void ftm0_timer_handler(void);

/**
 *    @brief ftm1定时器中断函数
 */
extern void ftm1_timer_handler(void);

/**
 *    @brief ftm2定时器中断函数
 */
extern void ftm2_timer_handler(void);


#endif /* FTM_TIMER_H_ */
