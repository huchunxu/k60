/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     speaker_ntshell.c
 *
 *        @brief    speaker ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/4/17 18:26
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/17   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>

#include "speaker_ntshell.h"
#include "task_ntshell.h"
#include "speaker.h"

static void speaker(int argc, char **argv);
static void usage(void);

/**
 *    @brief   speaker命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void speaker_cmd_initialize(intptr_t exinf)
{
    ntshell_register("speaker", speaker);
}

/**
 *    @brief   speaker命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void speaker(int argc, char **argv)
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
                if(*optarg == '0')
                {
                    if (speaker_read(SPEAKER0) == SPEAKER_OFF)
                        speaker_open(SPEAKER0);
                    else
                        printf("The speaker0 has been powerd on!\n");
                }
                else
                {
                    usage();
                }
                break;

            case 'c':
                if(*optarg == '0')
                {
                    if (speaker_read(SPEAKER0) == SPEAKER_ON)
                        speaker_close(SPEAKER0);
                    else
                        printf("The speaker0 has been powerd off!\n");
                }
                else
                {
                    usage();
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
    printf("\nUsage: speaker [-o <open>] [-c <close>] [-h <help>]"
        "\n  -o  open the speaker e.g. -o 0"
        "\n  -c  close the speaker e.g. -c 0\n");
}
