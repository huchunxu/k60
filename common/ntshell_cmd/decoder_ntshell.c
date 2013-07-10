/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     decoder_ntshell.c
 *
 *        @brief    decoder ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/4/18 22:19
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/18   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "decoder_ntshell.h"
#include "task_ntshell.h"
#include "decoder.h"
#include "serial.h"

static void decoder(int argc, char **argv);
static void usage(void);


/**
 *    @brief   decoder命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void decoder_cmd_initialize(intptr_t exinf)
{
    ntshell_register("decoder", decoder);
}

/**
 *    @brief   decoder命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void decoder(int argc, char **argv)
{
    int option = 0;
    uint8_t get_char;
    int decoder_no_temp = 0;
    ID  decoder_id_temp = 0;
    vuint32_t pulse_num = 0;

    /* 再次调用 getopt() 时的下一个argv指针的索引，如果不清零，下一次使用相同命令无响应 */
    optind = 0;
    /* 不希望getopt()印出错信息 */
    opterr = 0;

    while ((option = getopt(argc, argv, "?d:")) != -1)
    {
        switch (option)
        {
            case 'd':
                decoder_no_temp = atoi(optarg);
                if(decoder_no_temp == 0)
                    decoder_id_temp = DECODER;
                else
                {
                    printf("The decoder %d is not exist!\n", decoder_no_temp);
                    break;
                }
                
                printf("Press 'q' to quit, another key to continue! \n");
                while(1)
                {
                    pulse_num = decoder_read(decoder_id_temp);
                    printf("The decoder %d is %ld !\n", decoder_no_temp, pulse_num);                    
                    serial_rea_dat(NTSHELL_PORTID, &get_char, 1);
                    
                    if (get_char == 'q')
                    {
                        printf("quit \n");
                        break;
                    }
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
 *    @brief   decoderread命令的帮助信息
 */
static void usage(void)
{
    printf("\nUsage: decoder [-d <display>]"
        "\n  -d  dispaly the decoder value e.g.  -d 0 \n");
}
