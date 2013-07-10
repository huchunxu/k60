/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_acc.c
 *
 *        @brief    测试accelerometer模块
 *
 *        @version  0.1
 *        @date     2012/5/10 21:35
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *        
 *        @note     
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/10   create orignal file
 * =====================================================================================
 */
#include <stdio.h>

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "task_ntshell.h"

#include "accelerometer.h"
#include "serial.h"

void delay(uint32_t ntime);

int main(int argc, char **argv)
{
    uint8_t acc_no = 0;
    uint8_t acc_total_no = 2;
    uint8_t get_char = 0;
    vuint16_t acc_msg = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    acc_init();                                          /* 速度传感器初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    
    printf("\n Welcome to k60 software platform! \n");
    
    while (1)
    {
        printf(" *** This is a test for accelerometer module! *** \n");

        printf(" \n>>>> One accelerometer will be opened followed by another! \n");
        for (acc_no = 0; acc_no < acc_total_no; acc_no++)
        {
            delay(120);
            switch (acc_no)
            {
                case 0:
                    acc_msg = acc_read(ACC0);
                    break;
                case 1:
                    acc_msg = acc_read(ACC1);
                    break;
                default:
                    printf(" The accelerometer number is error!\n");
                    break;
            }

            if (acc_msg == (vuint16_t)E_ID)
            {
                printf(" The ID of accelerometer%d is error !\n", acc_no);
            }
            else if (acc_msg == (vuint16_t)E_ILUSE)
            {
                printf(" The port of accelerometer%d is not open !\n", acc_no);
            }
            else
            {
                printf(" The accelerometer%d has been opened!\n", acc_no);
            }
        }
        
        delay(100);
        printf(" \n>>>> The value of the accelerometer will be read!");
        printf(" \n>>>> Press 'q' to quit!");
        printf(" \n>>>> Press other keys to read once more!\n\n");
        while (1)
        {   
            acc_msg = acc_read(ACC0);
            printf(" The  accelerometer is %d\n", acc_msg);
            
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

