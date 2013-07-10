/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_uart.c
 *
 *        @brief    测试双环缓冲串口程序
 *
 *        @version  0.1
 *        @date     2012/3/19 11:00:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/3/19   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include "common.h"
#include "exception.h"
#include "light.h"
#include "sysinit.h"
#include "target_serial.h"
#include "serial.h"


int main(void)
{
    vuint32_t run_counter = 0;   //运行计数器
    uint8_t get_char = 0;

    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    light_init();                                        /* LED灯初始化 */

    /* 初始化串口 */
    serial_initialize((intptr_t)(NULL));

    /* 主循环 */
    while (1)
    {
        //主循环计数到一定的值，使小灯的亮、暗状态切换
//        run_counter++;
//        if (run_counter >= 5000000)
//        {
//            light_change(LIGHT1);//指示灯的亮、暗状态切换
//            run_counter = 0;
//        }
    	//serial_wri_dat(UART_NO_GET(UART_NO), "hello", 5);
        get_char = serial_get_char(UART_NO_GET(UART_NO));

        switch(get_char)
        {
            case 'a':
                printf("a\n");
            break;
            case 's':
                printf("s\n");
            break;
            case 'd':
                 printf("d\n");
            break;
            case 'f':
                printf("f\n");
            break;
            default:
                break;
        }
    } 
}

