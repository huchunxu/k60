/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_em.c
 *
 *        @brief    测试电磁组主板
 *
 *        @version  0.1
 *        @date     2012/4/16 19:33
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/16   create orignal file
 * =====================================================================================
 */

#include <stdio.h>

#include "integer.h"   
#include "ffconf.h"     /* FatFs configuration options */ 
#include "ff.h"
#include "diskio.h"

#include "ntlibc.h"
#include "ntopt.h"
#include "ntshell.h"
#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "sysinit.h"
#include "spi.h" 

#include "help_ntshell.h"
#include "target_serial.h"
#include "task_ntshell.h"
#include "light_ntshell.h"
#include "switch_ntshell.h"
#include "speaker_ntshell.h"
#include "motor_ntshell.h"
#include "decoder_ntshell.h"
#include "sd_ntshell.h"

#include "light.h"
#include "serial.h"
#include "decoder.h"
#include "switch.h"
#include "speaker.h" 
#include "motor.h"
#include "sd.h" 
#include "gyro.h" 
#include "accelerometer.h" 

FIL    test_data;                                     /* File objects */
char  test_data_name[FILE_NAME_LENGHT]="a_data.txt";  /* File name */

int main(int argc, char **argv)
{   
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    light_init();                                        /* LED灯初始化 */
    switch_init();                                       /* 开关初始化 */
    speaker_init();                                      /* 蜂鸣器初始化 */
    motor_init();                                        /* 电机初始化 */
    decoder_init();                                      /* 编码器初始化 */
    gyro_init();                                         /* 陀螺仪初始化 */
    acc_init();                                          /* 加速度传感器初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    //sd_init(&Fatfs);                                     /* 初始化SD卡，并创建文件 */
    //sd_create_file(&test_data, test_data_name);
    
    /* 命令注册 */
    help_cmd_initialize((intptr_t)(NULL));
    light_cmd_initialize((intptr_t)(NULL));
    switch_cmd_initialize((intptr_t)(NULL));
    speaker_cmd_initialize((intptr_t)(NULL));
    motor_cmd_initialize((intptr_t)(NULL));
    decoder_cmd_initialize((intptr_t)(NULL));
    //sd_cmd_initialize((intptr_t)(NULL));

    printf("\n Welcome to k60 software platform!");
    printf("\n Press 'help' to get the help! \n");
    
    light_open(LIGHT4); 

    /* ntshell测试 */
    task_ntshell((intptr_t)(NULL));
}

