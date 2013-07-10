/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_gyro.c
 *
 *        @brief    测试gyro模块
 *
 *        @version  0.1
 *        @date     2012/5/11 14:09
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *        
 *        @note     
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/11   create orignal file
 * =====================================================================================
 */
#include <stdio.h>

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "task_ntshell.h"

#include "gyro.h"
#include "serial.h"

void delay(uint32_t ntime);

int main(int argc, char **argv)
{
    uint8_t gyro_no = 0;
    uint8_t gyro_total_no = 2;
    uint8_t get_char = 0;
    vuint16_t gyro_msg = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    gyro_init();                                         /* 陀螺仪初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    
    printf("\n Welcome to k60 software platform! \n");
    
    while (1)
    {
        printf(" *** This is a test for gyro module! *** \n");

        printf(" \n>>>> One gyro will be opened followed by another! \n");
        for (gyro_no = 0; gyro_no < gyro_total_no; gyro_no++)
        {
            delay(120);
            switch (gyro_no)
            {
                case 0:
                    gyro_msg = gyro_read(GYRO0);
                    break;
                case 1:
                    gyro_msg = gyro_read(GYRO1);
                    break;
                default:
                    printf(" The gyro number is error!\n");
                    break;
            }

            if (gyro_msg == (vuint16_t)E_ID)
            {
                printf(" The ID of gyro%d is error !\n", gyro_no);
            }
            else if (gyro_msg == (vuint16_t)E_ILUSE)
            {
                printf(" The port of gyro%d is not open !\n", gyro_no);
            }
            else
            {
                printf(" The gyro%d has been opened!\n", gyro_no);
            }
        }
        
        delay(100);
        printf(" \n>>>> The value of the gyro will be read!");
        printf(" \n>>>> Press 'q' to quit!");
        printf(" \n>>>> Press other keys to read once more!\n\n");
        while (1)
        {   
            gyro_msg = gyro_read(GYRO0);
            printf(" The gyro is %d\n", gyro_msg);
            
            serial_rea_dat(NTSHELL_PORTID, &get_char, 1);
            if (get_char == 'q')
            {
                printf("quit!\n");
                break;
            }       
        }
        
        printf(" \n>>>> A test for accelerometer module is over!\n");
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

