/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_systick.c
 *
 *        @brief    测试内核定时器
 *
 *        @version  0.1
 *        @date     2012/3/9 14:07:42
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2012/3/9    create orignal file
 * =====================================================================================
 */

#include "common.h"
#include "exception.h"
#include "light.h"
#include "sys_timer.h"

int main(void)
{
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    light_init();                                        /* LED灯初始化 */

    /* 主循环 */
    //SCB_ICSR |= SCB_ICSR_NMIPENDSET_MASK;
    while (1)
    {
        /* 主循环1s计数，使小灯的亮、暗状态切换 */
        if(sys_timer_count >= 100)
        {
            sys_timer_count = 0;
            light_change(LIGHT1);
        } /* end_if */
    } /* end_while */
}
