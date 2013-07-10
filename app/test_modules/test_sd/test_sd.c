/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_sd.c
 *
 *        @brief    测试sd卡
 *
 *        @version  0.1
 *        @date     2012/4/16 19:33
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/16   create orignal file
 *  @0.2    Hu Chunxu   2012/5/7    测试SD卡速度最大100KB/s
 * =====================================================================================
 */
#include <stdio.h>

#include "ff.h"
#include "diskio.h"

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "sysinit.h"
#include "spi.h" 

#include "light.h"
#include "serial.h"
#include "motor.h"
#include "sd.h" 
#include "sd_rw.h"
#include "sd_send.h"

FIL    test_data;                                /* File objects */
char  test_data_name[FILE_NAME_LENGHT]="a_data.txt";  /* File name */
char  test_sd_data[65535];

int main(int argc, char **argv)
{   
    uint8_t n = 1, p = 2, q = 0, f = 0;
    uint32_t e = 0;
    uint32_t test_time = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    light_init();                                        /* LED灯初始化 */
//    motor_init();
//    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    sd_init(&Fatfs);                                     /* 初始化SD卡，并创建文件 */
    sd_create_file(&test_data, test_data_name);           /* create a file */
    
//    printf("\n Welcome to k60 software platform! \n");
//    printf(" *** This is a test for SD module! *** \n");
//    light_open(LIGHT4);
//
//    printf(" \n>>>> The data will be writen into the SD card! \n");
    
//    for(test_time = 0;test_time < 65535; test_time++)
//    {
//        test_sd_data[test_time] = test_time;
//    }
    
    /* 写数据 */
    if (test_data.fs)
    {
        f_printf(&test_data, "Hello SD Card!\n");
        f_printf(&test_data, "This is a test!\n");
        f_printf(&test_data, "1 2 3 4 5 6 7 8 9\n");
        f_printf(&test_data, "~ ! # $ % ^ & * (\n");

//        for(test_time = 0;test_time < 65535; test_time++)
//        {
//            f_printf(&test_data, "%d\t", test_sd_data[test_time]);
//        }
    }
    f_printf(&test_data, "TEST OVER\n");

    sd_close_file(&test_data); /* 关闭文件 */
    
    //for(n=0;n<128;n++)
//    while(1)
//    {
//        SD_SendData(n);
//        SD_SendData(p);
//        SD_SendData(q);
//        SD_SendData(f);
//        SD_SendData(CRLF);
//
//        for(e = 0; e< 65535; e++);
//    }
//
//    printf(" \n>>>> A test for SD module is over!\n");
    while(1)
    {
        light_open(LIGHT6); 
    }
}
