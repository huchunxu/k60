/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_light.c
 *
 *        @brief    测试light模块
 *
 *        @version  0.1
 *        @date     2012/5/8 17:00
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *        
 *        @note     主要进行light的开关状态，ID检测和端口是否打开检测
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/8   create orignal file
 * =====================================================================================
 */

#include <stdio.h>

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "task_ntshell.h"

#include "light.h"
#include "serial.h"

void delay(uint32_t ntime);

int main(void)
{
    uint8_t light_no = 0;
    uint8_t light_total_no = 9;
    uint8_t n =0;
    uint8_t get_char = 0;
    ER light_msg = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    light_init();                                        /* LED灯初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    
    printf("\n Welcome to k60 software platform! \n");
    
    while (1)
    {
        printf(" *** This is a test for light module! *** \n");
        light_close_some(0xff);
        printf(" \n>>>> One light will be powered on followed by another! \n");
        for (light_no = 0; light_no < light_total_no; light_no++)
        {
            delay(120);
            switch (light_no)
            {
                case 0:
                    light_msg = light_open(LIGHT0);
                    break;
                case 1:
                    light_msg = light_open(LIGHT1);
                    break;
                case 2:
                    light_msg = light_open(LIGHT2);
                    break;
                case 3:
                    light_msg = light_open(LIGHT3);
                    break;
                case 4:
                    light_msg = light_open(LIGHT4);
                    break;
                case 5:
                    light_msg = light_open(LIGHT5);
                    break;
                case 6:
                    light_msg = light_open(LIGHT6);
                    break;
                case 7:
                    light_msg = light_open(LIGHT7);
                    break;
                case 8:
                    light_msg = light_open(LIGHT8);
                    break;
                default:
                    printf("The light number is error!\n");
                    break;
            }

            if (light_msg == E_ID)
            {
                printf(" The ID of light %d is error !\n", light_no);
            }
            else if (light_msg == E_ILUSE)
            {
                printf(" The port of light%d is not open !\n", light_no);
            }
            else
            {
                printf(" The light%d has been powered on!\n", light_no);
            }
        }

        light_close_some(0xff);
        printf(" \n>>>> All the lights will be powered on or off!\n");
        for (n = 0; n < 20; n++)
        {
            delay(50);
            if (n % 2)
                light_open_some(0xff);
            else
                light_close_some(0xff);
        }

        light_close_some(0xff);
        printf(" \n>>>> The lights are water running!\n");

        n = 0;
        while (n < 10)
        {
            for (light_no = 0; light_no < 8; light_no++)
            {
                delay(10);
                light_close_some(0xff);
                switch (light_no)
                {
                    case 0:
                        light_open(LIGHT0);
                        break;
                    case 1:
                        light_open(LIGHT1);
                        break;
                    case 2:
                        light_open(LIGHT2);
                        break;
                    case 3:
                        light_open(LIGHT3);
                        break;
                    case 4:
                        light_open(LIGHT4);
                        break;
                    case 5:
                        light_open(LIGHT5);
                        break;
                    case 6:
                        light_open(LIGHT6);
                        break;
                    case 7:
                        light_open(LIGHT7);
                        break;
                    default:
                        printf("The light number is error!");
                        break;
                }
            }
            n++;
        }

        light_close_some(0xff);
        printf(" \n>>>> A test for light module is over!\n");
        while (1)
        {
            printf(" \n>>>> Press 'n' to test once more.\n");
            serial_rea_dat(NTSHELL_PORTID, &get_char, 1);
            
            if (get_char == 'n')
            {
                printf("Once more \n");
                delay(200);
                break;
            }
        }
    }
}

/**
 *    @brief   简单的延时函数
 *
 *    @param   ntime  延时周期
 */
void delay(uint32_t ntime)
{
    uint32_t i = 0, j = 0;
    
    for(i=0;i<ntime;i++)
        for(j=0;j<100000;j++);
}
