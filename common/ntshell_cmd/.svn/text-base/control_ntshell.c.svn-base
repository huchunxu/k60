/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     control_ntshell.c
 *
 *        @brief    控制车的命令
 *
 *        @version  0.1
 *        @date     2012/5/23 16:06
 *
 *        @author  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/23   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "control_ntshell.h"
#include "task_ntshell.h"
#include "motor.h"
#include "steer.h"
#include "serial.h"

static void control(int argc, char **argv);

int32_t motor_duty_test;
int16_t steer_angle_test;

/**
 *    @brief   control命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void control_cmd_initialize(intptr_t exinf)
{
    ntshell_register("control", control);
}

/**
 *    @brief   control命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void control(int argc, char **argv)
{
    uint8_t get_char = 0;
    
    printf("\n>>> The car will be controled in manual mode!");
    printf("\n>>> Press 'w','s','a','d' to control the car!\n");
    printf("\n>>> Press 'q' to quit!\n");
    while(1)
    {
        serial_rea_dat(NTSHELL_PORTID, &get_char, 1);
                    
        if (get_char == 'w')
        {
            motor_duty_test = motor_duty_test + 5;               
        }
        else if (get_char == 's')
        {
            motor_duty_test = motor_duty_test - 5;  
        }
        else if (get_char == 'a')
        {
            steer_angle_test = steer_angle_test - 3;
        }
        else if (get_char == 'd')
        {
            steer_angle_test = steer_angle_test + 3; 
        }
        else if(get_char == 'q')
        {
            printf("\n>>> Quit!\n");
            steer_output_angle(STEER_DIR, 0);      
            motor_output(MOTOR_LEFT, 0);
            break;
        }
        else
        {
            
        }
        
        if(steer_angle_test > STEER_DIR_MAX_ANGLE)
        {
            steer_angle_test = STEER_DIR_MAX_ANGLE;
        }
        else if(steer_angle_test < STEER_DIR_MIN_ANGLE)
        {
            steer_angle_test = STEER_DIR_MIN_ANGLE;
        }
        
        if(motor_duty_test > MOTOR_MAX_VAL)
        {
            motor_duty_test = MOTOR_MAX_VAL;
        }
        else if(motor_duty_test < MOTOR_MIN_VAL)
        {
            motor_duty_test = MOTOR_MIN_VAL;
        }
            
        steer_output_angle(STEER_DIR, steer_angle_test);      
        motor_output(MOTOR_LEFT, motor_duty_test);
        printf("angle:%d, speed:%d\n", (int)steer_angle_test, (int)motor_duty_test);
    }
}
