/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_switch.c
 *
 *        @brief    测试switch模块
 *
 *        @version  0.1
 *        @date     2012/5/9 13:46
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *        
 *        @note     
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/9   create orignal file
 * =====================================================================================
 */

#include <stdio.h>

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "task_ntshell.h"

#include "switch.h"
#include "serial.h"

void delay(uint32_t ntime);

int main(int argc, char **argv)
{
    uint8_t switch_no = 0;
    uint8_t switch_total_no = 11;
    uint8_t n =0;
    uint8_t get_char = 0;
    bool_t switch_msg = 0;
    uint8_t switch_state = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    switch_init();                                       /* switch初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    
    printf("\n Welcome to k60 software platform! \n");
    
    while (1)
    {
        printf(" *** This is a test for switch module! *** \n");
        printf(" \n>>>> One switch will be read followed by another! \n");
        
        for (switch_no = 0; switch_no < switch_total_no; switch_no++)
        {
            delay(120);
            switch (switch_no)
            {
                case 0:
                    switch_msg = switch_read(SWITCH_START0);
                    break;
                case 1:
                    switch_msg = switch_read(SWITCH_START1);
                    break;
                case 2:
                    switch_msg = switch_read(SWITCH0);
                    break;
                case 3:
                    switch_msg = switch_read(SWITCH1);
                    break;
                case 4:
                    switch_msg = switch_read(SWITCH2);
                    break;
                case 5:
                    switch_msg = switch_read(SWITCH3);
                    break;
                case 6:
                    switch_msg = switch_read(SWITCH4);
                    break;
                case 7:
                    switch_msg = switch_read(SWITCH5);
                    break;
                case 8:
                    switch_msg = switch_read(SWITCH6);
                    break;
                case 9:
                    switch_msg = switch_read(SWITCH7);
                    break;
                case 10:
                    switch_msg = switch_read(SWITCH8);
                    break;
                default:
                    printf("The switch number is error!\n");
                    break;
            }

            if (switch_msg == E_ID)
            {
                printf(" The ID of switch %d is error !\n", switch_no);
            }
            else if (switch_msg == E_ILUSE)
            {
                printf(" The port of switch%d is not open !\n", switch_no);
            }
            else if(switch_msg == SWITCH_ON)
            {
                printf(" The switch%d is ON!\n", switch_no);
            }
            else
            {
                printf(" The switch%d is OFF!\n", switch_no);
            }
        }


        printf(" \n>>>> All the switchs will be read!\n");
        delay(120);
        switch_state = switch_read_8bit(SWITCH_GROUP0);
        for (n = 0; n < 8; n++)
        {
            if (switch_state & (1 << n))
                printf("The switch %d is ON\n", n);
            else
                printf("The switch %d is OFF\n", n);
        }

        if (switch_read(SWITCH_START0))
            printf("The switch start0 is ON\n");
        else
            printf("The switch start0 is OFF\n");

        if (switch_read(SWITCH_START1))
            printf("The switch start1 is ON\n");
        else
            printf("The switch start1 is OFF\n");
        
        
        delay(200);
        printf(" \n>>>> A test for switch module is over!\n");
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

