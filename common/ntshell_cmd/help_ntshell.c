/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     help_ntshell.c
 *
 *        @brief    help ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/4/25 17:00
 *
 *        @author  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/25   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>

#include "help_ntshell.h"
#include "task_ntshell.h"

static void help(int argc, char **argv);

/**
 *    @brief   help命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void help_cmd_initialize(intptr_t exinf)
{
    ntshell_register("help", help);
}

/**
 *    @brief   help命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void help(int argc, char **argv)
{
    printf("\nUsage: The useful command list >>>");
    printf("\n  light    control the light");
    printf("\n  motor    control the motor");
    printf("\n  speaker  control the speaker");
    printf("\n  switchs  display the switch state");
    printf("\n  decoder  display the decoder value");
    printf("\n  sd       control sd card");
    printf("\n  control  control the car\n");
}
