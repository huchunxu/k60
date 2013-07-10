/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_ftm_timer.c
 *
 *        @brief    测试ftm定时器
 *
 *        @version  0.1
 *        @date     2012/3/17 20:41:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/3/17   create orignal file
 * =====================================================================================
 */
#include "common.h"
#include "exception.h"
#include "light.h"
#include "ftm_timer.h"

int main(void)
{
    int32_t e_ftm_timer = 0;

    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    e_ftm_timer = ftm_timer_init(FTM0);
    light_init();                                        /* LED灯初始化 */

    /* 使能ftm定时器中断 */
    ftm_timer_enable(FTM0);

    /* 主循环 */
    while (1)
    {
        /* 主循环1s计数，使小灯的亮、暗状态切换 */
        if(ftm_count >= 1000)
        {
            ftm_count = 0;
            light_change(Light_Run_PORT,Light_Run2);
        } /* end_if */

    } /* end_while */
}
