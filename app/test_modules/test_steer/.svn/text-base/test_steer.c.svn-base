/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_steer.c
 *
 *        @brief    测试steer模块
 *
 *        @version  0.1
 *        @date     2012/5/8 17:00
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *        
 *        @note    
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/8   create orignal file
 * =====================================================================================
 */
#include <stdio.h>

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "task_ntshell.h"

#include "steer.h"
#include "serial.h"

void delay(uint32_t ntime);

int main(int argc, char **argv)
{
    uint8_t steer_no = 0;
    uint8_t steer_total_no = 3;
    uint8_t n =0;
    uint8_t get_char = 0;
    ER steer_msg = 0;
    int32_t steer_angle = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    steer_init();                                        /* 舵机初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    
    printf("\n Welcome to k60 software platform! \n");    
    
    
    while (1)
    {
        printf(" *** This is a test for steer module! *** \n");

        printf(" \n>>>> One steer will be powered on followed by another! \n");
        for (steer_no = 0; steer_no < steer_total_no; steer_no++)
        {
            delay(120);
            switch (steer_no)
            {
                case 0:
                    steer_msg = steer_output_angle(STEER_DIR, steer_angle);
                    break;
                case 1:
                    steer_msg = steer_output_angle(STEER_SERVO, steer_angle);
                    break;
                default:
                    printf("The steer number is error!\n");
                    break;
            }

            if (steer_msg == E_ID)
            {
                printf(" The ID of steer%d is error !\n", steer_no);
            }
            else if (steer_msg == E_ILUSE)
            {
                printf(" The port of steer%d is not open !\n", steer_no);
            }
            else
            {
                printf(" The steer%d has been powered on!\n", steer_no);
            }
        }
        
        delay(200);
        steer_angle = 0;
        printf(" \n>>>> All the steers will change the angle!\n");
        for (n = 0; n < 18; n++)
        { 
            if(n < 9)
            {
                steer_angle = steer_angle + 5;
            }
            else
            {
                steer_angle = steer_angle - 5;
            }
            printf("The angle of the steer is %d\n", (int)steer_angle);
            steer_output_angle(STEER_DIR,  steer_angle);
            steer_output_angle(STEER_SERVO,  steer_angle);
            delay(50);
        }
        
        steer_angle = 0;
        for (n = 0; n < 18; n++)
        { 
            if(n < 9)
            {
                steer_angle = steer_angle - 5;
            }
            else
            {
                steer_angle = steer_angle + 5;
            }
            printf("The angle of the steer is %d\n", (int)steer_angle);
            steer_output_angle(STEER_DIR,  steer_angle);
            steer_output_angle(STEER_SERVO,  steer_angle);
            delay(50);
        }

        printf(" \n>>>> A test for steer module is over!\n");
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

