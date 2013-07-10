/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     sd_ntshell.c
 *
 *        @brief    sd ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/5/6 20:51
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/6   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>

#include "sd_ntshell.h"
#include "task_ntshell.h"
#include "sd.h"
#include "diskio.h"
#include "sys_timer.h"

static void sd(int argc, char **argv);
static void usage(void);

FIL   sd_ntshell;    /* File objects */

/**
 *    @brief   help命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void sd_cmd_initialize(intptr_t exinf)
{
    ntshell_register("sd", sd);
}

/**
 *    @brief   sd命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void sd(int argc, char **argv)
{
    int option = 0;
    uint8_t init_time = 0;
    uint32_t start_time = 0;
    uint32_t end_time = 0;
    uint32_t time_spent = 0;
    char sd_ntshell_name[FILE_NAME_LENGHT]="a_sd.txt";  /* File name */
    
    /* 再次调用 getopt() 时的下一个argv指针的索引，如果不清零，下一次使用相同命令无响应 */
    optind = 0;
    /* 不希望getopt()印出错信息 */
    opterr = 0;

    while ((option = getopt(argc, argv, "?mth")) != -1)
    {
        switch (option)
        {
            case 'm':
                /* 初始化SD卡，并创建文件 */
                while(disk_initialize(0)) 
                {
                    init_time ++;
                    if(init_time > 10)
                    {
                        printf("The SD card initialize faild!\n");
                        break;
                    }
                }
                
                /* 创建文件系统 */
                f_mount(0, &Fatfs);
                
                printf("The SD card has mounted!\n");
                break;
            
            case 't':
                sd_create_file(&sd_ntshell, sd_ntshell_name);  /* create a file */
                
                if (sd_ntshell.fs)
                {
                    sys_timer_read(&start_time);
                    f_printf(&sd_ntshell, "Hello SD Card!!\n");     
                    f_printf(&sd_ntshell, "This is a test!!\n");
                    f_printf(&sd_ntshell, "1 2 3 4 5 6 7 8 9\n");
                    f_printf(&sd_ntshell, "! @ $ & * ( ) + -\n");
                    sys_timer_read(&end_time);
                }
                
                if(end_time > start_time)
                    time_spent = (end_time - start_time)/100;
                else
                    time_spent = (start_time - end_time)/100;
                
                printf("The test file has been writen in the SD card\n");
                printf("Write time: %u us, write %u bytes .\n", 
                        (unsigned int)time_spent, (unsigned int)f_size(&sd_ntshell));
                
                sd_close_file(&sd_ntshell); /* 关闭文件 */
                break;

            case 'h':
            case '?':
            default:
                usage();
                break;
        }
    }
}

/**
 *    @brief   sd命令的帮助信息
 */
static void usage(void)
{
    printf("\nUsage: sd [-m <mount>] [-t <test>] [-h <help>]"
            "\n  -m  mount the sd card e.g. -m"
            "\n  -t  test sd card e.g.  -t \n");
}
