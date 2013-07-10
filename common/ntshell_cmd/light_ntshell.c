/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     light_ntshell.c
 *
 *        @brief    light ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/3/22 21:37:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/3/22   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>

#include "light_ntshell.h"
#include "task_ntshell.h"
#include "light.h"

static void light(int argc, char **argv);
static void usage(void);

/**
 *    @brief   light命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void light_cmd_initialize(intptr_t exinf)
{
    ntshell_register("light", light);
}

/**
 *    @brief   light命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void light(int argc, char **argv)
{
    int option = 0;

    /* 再次调用 getopt() 时的下一个argv指针的索引，如果不清零，下一次使用相同命令无响应 */
    optind = 0;
    /* 不希望getopt()印出错信息 */
    opterr = 0;

    while ((option = getopt(argc, argv, "?o:c:")) != -1)
    {
        switch (option)
        {
            case 'o':
                switch (*optarg)
                {
                    case '0':
                        if (light_read(LIGHT0) == LIGHT_OFF)
                            light_open(LIGHT0);
                        else
                            printf("The light0 has been powerd on!\n");
                        break;
                    case '1':
                        if (light_read(LIGHT1) == LIGHT_OFF)
                            light_open(LIGHT1);
                        else
                            printf("The light1 has been powerd on!\n");
                        break;
                    case '2':
                        if (light_read(LIGHT2) == LIGHT_OFF)
                            light_open(LIGHT2);
                        else
                            printf("The light2 has been powerd on!\n");
                        break;
                    case '3':
                        if (light_read(LIGHT3) == LIGHT_OFF)
                            light_open(LIGHT3);
                        else
                            printf("The ligh3 has been powerd on!\n");
                        break;
                    case '4':
                        if (light_read(LIGHT4) == LIGHT_OFF)
                            light_open(LIGHT4);
                        else
                            printf("The light4 has been powerd on!\n");
                        break;
                    case '5':
                        if (light_read(LIGHT5) == LIGHT_OFF)
                            light_open(LIGHT5);
                        else
                            printf("The light5 has been powerd on!\n");
                        break;
                    case '6':
                        if (light_read(LIGHT6) == LIGHT_OFF)
                            light_open(LIGHT6);
                        else
                            printf("The light6 has been powerd on!\n");
                        break;
                    case '7':
                        if (light_read(LIGHT7) == LIGHT_OFF)
                            light_open(LIGHT7);
                        else
                            printf("The light7 has been powerd on!\n");
                        break;
                    default:
                        usage();
                        break;
                        
                }
                break;

            case 'c':
                switch (*optarg)
                {
                    case '0':
                        if (light_read(LIGHT0) == LIGHT_ON)
                            light_close(LIGHT0);
                        else
                            printf("The light0 has been powerd off!\n");
                        break;
                    case '1':
                        if (light_read(LIGHT1) == LIGHT_ON)
                            light_close(LIGHT1);
                        else
                            printf("The light1 has been powerd off!\n");
                        break;
                    case '2':
                        if (light_read(LIGHT2) == LIGHT_ON)
                            light_close(LIGHT2);
                        else
                            printf("The light2 has been powerd off!\n");
                        break;
                    case '3':
                        if (light_read(LIGHT3) == LIGHT_ON)
                            light_close(LIGHT3);
                        else
                            printf("The light3 has been powerd off!\n");
                        break;
                    case '4':
                        if (light_read(LIGHT4) == LIGHT_ON)
                            light_close(LIGHT4);
                        else
                            printf("The light4 has been powerd off!\n");
                        break;
                    case '5':
                        if (light_read(LIGHT5) == LIGHT_ON)
                            light_close(LIGHT5);
                        else
                            printf("The light6 has been powerd off!\n");
                        break;
                    case '6':
                        if (light_read(LIGHT6) == LIGHT_ON)
                            light_close(LIGHT6);
                        else
                            printf("The light6 has been powerd off!\n");
                        break;
                    case '7':
                        if (light_read(LIGHT7) == LIGHT_ON)
                            light_close(LIGHT7);
                        else
                            printf("The light7 has been powerd off!\n");
                        break;
                    default:
                        usage();
                        break;

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
 *    @brief   lightset命令的帮助信息
 */
static void usage(void)
{
    printf("\nUsage: light [-o <open>] [-c <close>] [-h <help>]"
        "\n  -o  open the light e.g. -o 1"
        "\n  -c  close the light e.g. -c 2\n");
}

