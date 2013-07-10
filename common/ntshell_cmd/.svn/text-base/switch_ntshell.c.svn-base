/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     switch_ntshell.c
 *
 *        @brief    switch ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/4/16 22:10
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/16   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "switch_ntshell.h"
#include "task_ntshell.h"
#include "switch.h"

static void switchs(int argc, char **argv);
static void usage(void);

/**
 *    @brief   switch命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void switch_cmd_initialize(intptr_t exinf)
{
    ntshell_register("switchs", switchs);
}

/**
 *    @brief   switchs命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void switchs(int argc, char **argv)
{       
    int option = 0;
    vuint8_t switch_state = 0;
    vuint8_t switch_no = 0;
    vuint8_t state_flag = 0;
    int i;

    /* 再次调用 getopt() 时的下一个argv指针的索引，如果不清零，下一次使用相同命令无响应 */
    optind = 0;
    /* 不希望getopt()印出错信息 */
    opterr = 0;

    while ((option = getopt(argc, argv, "?d:h")) != -1)
    {
        switch (option)
        {
            case 'd':
                switch_no = atoi(optarg);
                switch (switch_no)
                {
                    case 0:
                        switch_state = switch_read(SWITCH0);
                        break;
                    case 1:
                        switch_state = switch_read(SWITCH1);
                        break;
                    case 2:
                        switch_state = switch_read(SWITCH2);
                        break;
                    case 3:
                        switch_state = switch_read(SWITCH3);
                        break;
                    case 4:
                        switch_state = switch_read(SWITCH4);
                        break;
                    case 5:
                        switch_state = switch_read(SWITCH5);
                        break;
                    case 6:
                        switch_state = switch_read(SWITCH6);
                        break;
                    case 7:
                        switch_state = switch_read(SWITCH7);
                        break;
                    default:
                        switch_state = switch_read_8bit(SWITCH_GROUP0);
                        break;

                }
                if ((switch_no >= 0) && (switch_no < 8))
                {
                    if (switch_state)
                        printf("The switch %d is ON\n", switch_no);
                    else
                        printf("The switch %d is OFF\n", switch_no);
                }
                else
                {
                    for (i = 0; i < 8; i++)
                    {
                        state_flag = switch_state & (1 << i);
                        if (state_flag)
                            printf("The switch %d is ON\n", i);
                        else
                            printf("The switch %d is OFF\n", i);
                    }

                    if (switch_read(SWITCH_START0))
                        printf("The switch start0 is ON\n");
                    else
                        printf("The switch start0 is OFF\n");

                    if (switch_read(SWITCH_START1))
                        printf("The switch start1 is ON\n");
                    else
                        printf("The switch start1 is OFF\n");
                }
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
 *    @brief   switchs命令的帮助信息
 */
static void usage(void)
{
    printf("\nUsage: switchs [-d <display>] [-h <help>]"
         "\n  -d display the seitchs state e.g. -d 2 \n");
}
