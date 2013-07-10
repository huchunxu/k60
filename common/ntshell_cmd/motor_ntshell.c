/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     motor_ntshell.c
 *
 *        @brief    motor ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/4/17 22:21
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/17   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "motor_ntshell.h"
#include "task_ntshell.h"
#include "motor.h"

static void motor(int argc, char **argv);
static void usage(void);


static int motor_open_id;
static int motor_duty_temp;

/**
 *    @brief   motor命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void motor_cmd_initialize(intptr_t exinf)
{
    ntshell_register("motor", motor);
}

/**
 *    @brief   motorwrite命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void motor(int argc, char **argv)
{
    int option = 0;
    int motor_no_temp = 0;

    /* 再次调用 getopt() 时的下一个argv指针的索引，如果不清零，下一次使用相同命令无响应 */
    optind = 0;
    /* 不希望getopt()印出错信息 */
    opterr = 0;

    while ((option = getopt(argc, argv, "?o:d:")) != -1)
    {
        switch (option)
        {
            case 'o':
                motor_no_temp = atoi(optarg);
                if(motor_no_temp == 0)
                    motor_open_id = MOTOR_LEFT;
                else if(motor_no_temp == 1)
                    motor_open_id = MOTOR_RIGHT;
                
                printf("The motor %d has been opened!\n", motor_no_temp);

                break;

            case 'd':
                motor_duty_temp = atoi(optarg);
                motor_output(motor_open_id, motor_duty_temp);
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
 *    @brief   motor命令的帮助信息
 */
static void usage(void)
{
    printf("\nUsage: motor [-o <open>] [-d <duty>]"
        "\n  -o  open the motor e.g.  -o 0"
        "\n  -d  motor duty e.g. -d  50 \n");
}
