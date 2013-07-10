/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**
 *        @file     robot_main.c
 *
 *        @brief    机器人控制
 *
 *        @version  0.1
 *        @date     2012/10/17  15:41
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/10/17   create orignal file
 * =====================================================================================
 */
#include <stdio.h>

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "sysinit.h"

#include "light.h"
#include "serial.h"
#include "motor_robot.h"
#include "infrared.h"

#define   FORWARD    0
#define   CHANGE     1
#define   BACKWARD   2


int main(int argc, char **argv)
{
	int robot_state = FORWARD;
	int front_infrared_value = 0;
	int back_infrared_value = 0;
	int front_infrared_num = 0;
	int back_infrared_num = 0;
	int front_infrared_amount = 0;
	int back_infrared_amount = 0;

    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    motor_robot_init();                                  /* 电机初始化 */
    infrared_init();                                     /* 红外初始化 */

    while(1)
    {
    	/* 读取光电管的数据 */
    	front_infrared_value = infrared_read_loc(INFRARED_FRONT);
    	back_infrared_value = infrared_read_loc(INFRARED_BACK);

    	/* 读取红外从右第一个亮灯的位置 */
    	front_infrared_num = infrared_read_num(front_infrared_value);
    	back_infrared_num  = infrared_read_num(back_infrared_value);

    	/* 读取传感器亮灯的总数 */
    	front_infrared_amount = infrared_read_amount(front_infrared_value);
    	back_infrared_amount  = infrared_read_amount(back_infrared_value);

        switch (robot_state)
        {
        	case FORWARD:
        		if((front_infrared_num == 2) || (front_infrared_num == 3))
				{
					motor_robot_output(MOTOR_LR, 40);
					motor_robot_output(MOTOR_LF, 40);
					motor_robot_output(MOTOR_RR, 40);
					motor_robot_output(MOTOR_RF, 40);
				}
				else if(front_infrared_num == 0)
				{
					motor_robot_output(MOTOR_LR, 70);
					motor_robot_output(MOTOR_LF, 70);
					motor_robot_output(MOTOR_RR, -50);
					motor_robot_output(MOTOR_RF, -50);
				}
				else if(front_infrared_num == 1)
				{
					motor_robot_output(MOTOR_LR, 60);
					motor_robot_output(MOTOR_LF, 60);
					motor_robot_output(MOTOR_RR, -20);
					motor_robot_output(MOTOR_RF, -20);
				}
				else if(front_infrared_num == 4)
				{
					motor_robot_output(MOTOR_LR, -20);
					motor_robot_output(MOTOR_LF, -20);
					motor_robot_output(MOTOR_RR, 60);
					motor_robot_output(MOTOR_RF, 60);
				}
				else if(front_infrared_num == 5)
				{
					motor_robot_output(MOTOR_LR, -50);
					motor_robot_output(MOTOR_LF, -50);
					motor_robot_output(MOTOR_RR, 70);
					motor_robot_output(MOTOR_RF, 70);
				}
				else
				{
					;
				}

        		if(back_infrared_amount > 3)
        		{
        			robot_state = CHANGE;
        		}
        		break;
        	case CHANGE:
        		motor_robot_output(MOTOR_LR, -80);
				motor_robot_output(MOTOR_LF, -80);
				motor_robot_output(MOTOR_RR, 50);
				motor_robot_output(MOTOR_RF, 50);

				if(back_infrared_num == 0)
				{
					//robot_state = BACKWARD;
				}
        		break;

        	case BACKWARD:
        		if((back_infrared_num == 2) || (back_infrared_num == 3))
				{
					motor_robot_output(MOTOR_LR, -40);
					motor_robot_output(MOTOR_LF, -40);
					motor_robot_output(MOTOR_RR, -40);
					motor_robot_output(MOTOR_RF, -40);
				}
				else if(back_infrared_num == 0)
				{
					motor_robot_output(MOTOR_LR, 30);
					motor_robot_output(MOTOR_LF, 30);
					motor_robot_output(MOTOR_RR, -70);
					motor_robot_output(MOTOR_RF, -70);
				}
				else if(back_infrared_num == 1)
				{
					motor_robot_output(MOTOR_LR, 20);
					motor_robot_output(MOTOR_LF, 20);
					motor_robot_output(MOTOR_RR, -60);
					motor_robot_output(MOTOR_RF, -60);
				}
				else if(back_infrared_num == 4)
				{
					motor_robot_output(MOTOR_LR, -60);
					motor_robot_output(MOTOR_LF, -60);
					motor_robot_output(MOTOR_RR, 20);
					motor_robot_output(MOTOR_RF, 20);
				}
				else if(back_infrared_num == 5)
				{
					motor_robot_output(MOTOR_LR, -70);
					motor_robot_output(MOTOR_LF, -70);
					motor_robot_output(MOTOR_RR, 30);
					motor_robot_output(MOTOR_RF, 30);
				}
				else
				{
					;
				}
        	    break;

        }
	}
}
