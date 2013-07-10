/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_adc.c
 *
 *        @brief    ad测试
 *
 *        @version  0.1
 *        @date     2012/4/7  21:20
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/7    create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include "common.h"
#include "exception.h"
#include "light.h"
#include "sysinit.h"
#include "target_serial.h"
#include "serial.h"
#include "adc.h"

int g_advalue[10]; /* 全局变量,储存ad转换结果 */

void get_advalue(void)
{
    g_advalue[0] = ad_once(0, 0);
    g_advalue[1] = ad_once(0, 19);
    g_advalue[2] = ad_once(0, 1);
    g_advalue[3] = ad_once(0, 20);
    g_advalue[4] = ad_once(0, 16);
    g_advalue[5] = ad_once(1, 0);
    g_advalue[6] = ad_once(1, 19);
    g_advalue[7] = ad_once(1, 1);
    g_advalue[8] = ad_once(1, 20);
    g_advalue[9] = ad_once(1, 16);
}

int main(void)
{
    uint32_t runcount;        /* 运行计数器 */
    int i=0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    light_init();                                        /* LED灯初始化 */

    /* 初始化串口 */
    serial_initialize((intptr_t)(NULL));
    
    /* ADC */
    adc_init(0);
    adc_init(1);
    
    printf("%s\n","ADC test!");

    /* 主循环 */
    while (1)
    {
        //1 主循环计数到一定的值，使小灯的亮、暗状态切换
        runcount++;
        if (runcount >= 4000000)
        {
            runcount = 0;
            light_write(LIGHT1);//指示灯的亮、暗状态切换

            //进行一次模块1通道16采样
            get_advalue();
            for (i = 0; i <= 9; i++)
            {
                printf("\t");
                printf("%d", g_advalue[i]);
            }
            printf("\n");

        }      
    } 
}
