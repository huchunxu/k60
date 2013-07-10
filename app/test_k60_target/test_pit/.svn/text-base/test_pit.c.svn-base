/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_pit.c
 *
 *        @brief    测试pit模块 1s闪烁
 *
 *        @version  0.1
 *        @date     2012/4/3  20:52:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/3    create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include "common.h"
#include "exception.h"
#include "light.h"
#include "sysinit.h"
#include "target_serial.h"
#include "serial.h"
#include "pit.h"

int main(void)
{
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    light_init();                                        /* LED灯初始化 */

    /* 初始化串口 */
    serial_initialize((intptr_t)(NULL));
    
    pit_init(PIT0, BUS_CLK_50000*1000); 
    pit_enable(PIT0);  
    
    printf("%s\n","PIT test!");

    /* 主循环 */
    while (1)
    {
        //主循环计数到一定的值，使小灯的亮、暗状态切换
        if (pit_count > 0)
        {
            light_change(LIGHT0);//指示灯的亮、暗状态切换
            pit_count = 0;
        }
        pit_enable(PIT0);
    } //end_while
}
