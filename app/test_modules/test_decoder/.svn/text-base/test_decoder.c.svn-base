/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_decoder.c
 *
 *        @brief    测试decoder模块
 *
 *        @version  0.1
 *        @date     2012/5/10 21:02
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

#include "decoder.h"
#include "serial.h"

void delay(uint32_t ntime);

int main(int argc, char **argv)
{
    uint8_t decoder_no = 0;
    uint8_t decoder_total_no = 3;
    uint8_t get_char = 0;
    vuint32_t decoder_msg = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    decoder_init();                                        /* 电机初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    
    printf("\n Welcome to k60 software platform! \n");
    
    while (1)
    {
        printf(" *** This is a test for decoder module! *** \n");

        printf(" \n>>>> One decoder will be opened followed by another! \n");
        for (decoder_no = 0; decoder_no < decoder_total_no; decoder_no++)
        {
            delay(120);
            switch (decoder_no)
            {
                case 0:
                    decoder_msg = decoder_read(DECODER_LEFT);
                    break;
                case 1:
                    decoder_msg = decoder_read(DECODER_RIGHT);
                    break;
                case 2:
                    decoder_msg = decoder_read(DECODER_MID);
                    break;
                default:
                    printf(" The decoder number is error!\n");
                    break;
            }

            if (decoder_msg == (vuint32_t)E_ID)
            {
                printf(" The ID of decoder%d is error !\n", decoder_no);
            }
            else if (decoder_msg == (vuint32_t)E_ILUSE)
            {
                printf(" The port of decoder%d is not open !\n", decoder_no);
            }
            else
            {
                printf(" The decoder%d has been opened!\n", decoder_no);
            }
        }
        
        delay(100);
        printf(" \n>>>> The value of the decoder will be read!");
        printf(" \n>>>> Press 'q' to quit!");
        printf(" \n>>>> Press other keys to read once more!\n\n");
        while (1)
        {   
            decoder_msg = decoder_read(DECODER_LEFT);
            printf(" The left  decoder is %ld\n", decoder_msg);
            decoder_msg = decoder_read(DECODER_RIGHT);
            printf(" The right decoder is %ld\n", decoder_msg);
            
            serial_rea_dat(NTSHELL_PORTID, &get_char, 1);
            if (get_char == 'q')
            {
                printf("quit!\n");
                break;
            }       
        }
        
        printf(" \n>>>> A test for decoder module is over!\n");
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

