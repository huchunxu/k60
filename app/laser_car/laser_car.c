/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**
 *        @file     laser_car.c
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
#include <string.h>

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "sysinit.h"

#include "light.h"
#include "switch.h"
#include "serial.h"
#include "motor.h"
#include "infrared.h"
#include "steer.h"
#include "decoder.h"
#include "telecontrol.h"

#define   FORWARD             0
#define   FORWARD_CHANGE      1
#define   FORWARD_CHANGE2     2
#define   BACKWARD            3
#define   BACKWARD_CHANGE     4
#define   BACKWARD_CHANGE2    5
#define   STOP                6


const int gl_speedDifference[45] = {
100, 98, 97, 95, 93,    91, 90, 88, 87, 85,    83, 82, 80, 79, 77,
76,  74, 73, 71, 70,    69, 67, 66, 64, 63,    61, 60, 59, 57, 56,
54,  53, 51, 50, 49,    47, 46, 44, 43, 41,    40, 38, 37, 35, 34};

void pwm_output_forward(int pwm_duty, int angle);
void pwm_output_backward(int pwm_duty, int angle);
void speed_control_forward(int expect_speed, int angle);
void speed_control_backward(int expect_speed, int angle);

int main(int argc, char **argv)
{
	int robot_state = FORWARD;
	int last_robot_state = FORWARD;
	int front_infrared_value = 0;
	int back_infrared_value = 0;
	int front_infrared_num = 0;
	int back_infrared_num = 0;
	int front_infrared_amount = 0;
	int back_infrared_amount = 0;
	int front_infrared_weight = 0;
	int back_infrared_weight = 0;
	uint32_t car_distence = 0;
	uint8_t get_char = 0;
	int change_num = 0;
	bool_t switch_state = 0;
	int detect_num = 0;
	int angle = 0;

	/* 模块初始化 */
	exc_init(); /* 中断初始化 */
	sys_timer_init(); /* 系统时钟初始化 */
	light_init(); /* 灯初始化 */
	switch_init(); /* 开关初始化 */
	serial_initialize((intptr_t) (NULL)); /* 初始化串口 */
	motor_init(); /* 电机初始化 */
	steer_init(); /* 舵机初始化 */
	decoder_init((intptr_t) (NULL)); /* 编码器初始化 */
	infrared_init(); /* 红外初始化 */

	while(1)
	{
		light_open(LIGHT2);
		light_open(LIGHT3);
	}
//    gpio_init(PORT_NO_GET(PTC0), PIN_NO_GET(PTC0), OUT_PUT, 0);
//    gpio_init(PORT_NO_GET(PTC2), PIN_NO_GET(PTC2),OUT_PUT, 1);
//    while(1)
//    {
//    	motor_output(MOTOR_LEFT, 50);
//    	motor_output(MOTOR_RIGHT, 50);
//    }

	while((get_char != 's') && (switch_state != SWITCH_ON))
	{
		 light_open_some(0x0f);
		 get_char = serial_get_char(UART_NO_GET(UART_NO));
		 switch_state = switch_read(SWITCH0);
	}

	while (1)
	{
		get_char = serial_get_char(UART_NO_GET(UART_NO));
		if(get_char == 'p')
		{
			last_robot_state = robot_state;
			robot_state = STOP;
		}

		/* 读取光电管的数据 */
		front_infrared_value = infrared_read_loc(INFRARED_FRONT);
		back_infrared_value = infrared_read_loc(INFRARED_BACK);

		/* 读取红外从右第一个亮灯的位置 */
		front_infrared_num = infrared_read_num(front_infrared_value);
		back_infrared_num = infrared_read_num(back_infrared_value);

		/* 读取传感器亮灯的总数 */
		front_infrared_amount = infrared_read_amount(front_infrared_value);
		back_infrared_amount = infrared_read_amount(back_infrared_value);

		/* 读取权值 */
		front_infrared_weight = infrared_read_weight(front_infrared_value);
		back_infrared_weight = infrared_read_weight(back_infrared_value);

		switch (robot_state)
		{
/**********************************前进*************************************/
		case FORWARD:
			light_open_some(0x01);
			light_bar_open(LIGHT_BAR0);
			light_bar_close(LIGHT_BAR1);
			if (front_infrared_amount == 1)
			{
				if (front_infrared_weight == 3)
				{
					angle = 40;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == -3)
				{
					angle = -40;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == 2)
				{
					angle = 20;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == -2)
				{
					angle = -20;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == 1)
				{
					angle = 5;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == -1)
				{
					angle = -5;
					//motor_output2(13, 13);
				}
			}
			else if (front_infrared_amount == 2)
			{
				if (front_infrared_weight == 5)
				{
					angle = 30;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == -5)
				{
					angle = -30;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == 3)
				{
					angle = 10;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == -3)
				{
					angle = -10;
					//motor_output2(13, 13);
				}
				else if (front_infrared_weight == 0)
				{
					angle = 0;
					//motor_output2(13, 13);
				}
			}
			steer_output_angle(STEER_DIR, angle);
			speed_control_forward(30,angle);

			if (front_infrared_amount > 4)
			{
				if(change_num == 4)
				{
					robot_state = STOP;
				}

				detect_num ++;
				if(detect_num > 2)
				{
					detect_num = 0;
					robot_state = FORWARD_CHANGE;
					car_distence = gl_distanceTotal;
				}
			}
			else
			{
				detect_num = 0;
			}
			break;

/**********************************前进转换1*************************************/
		case FORWARD_CHANGE:
			light_bar_open(LIGHT_BAR0);
			light_bar_open(LIGHT_BAR1);
			light_open_some(0x02);
			steer_output_angle(STEER_DIR, 40);
			//motor_output2(-25, -10);
			speed_control_backward(30,angle);

            if((gl_distanceTotal - car_distence)>9)
            {
            	robot_state = FORWARD_CHANGE2;
            }
		    break;

/**********************************前进转换2*************************************/
		case FORWARD_CHANGE2:
			light_bar_open(LIGHT_BAR0);
			light_bar_open(LIGHT_BAR1);
			light_open_some(0x02);
			steer_output_angle(STEER_DIR, 40);
			//motor_output2(-25, -10);
			speed_control_backward(30,angle);
			if((back_infrared_value & 0x30) && (!(back_infrared_value & 0x03)) && (front_infrared_amount < 3))
			{
				robot_state = BACKWARD;
				car_distence = gl_distanceTotal;
				change_num ++;
			}
			break;

/************************************后退****************************************/
		case BACKWARD:
			light_bar_open(LIGHT_BAR1);
			light_bar_close(LIGHT_BAR0);
			light_open_some(0x04);
			if (back_infrared_amount == 1)
			{
				if (back_infrared_weight == 3)
				{
					angle = -40;
					//motor_output2(-5, -22);
				}
				else if (back_infrared_weight == -3)
				{
					angle = 40;
					//motor_output2(-22, -5);
				}
				else if (back_infrared_weight == 2)
				{
					angle = -40;
					//motor_output2(-5, -20);
				}
				else if (back_infrared_weight == -2)
				{
					angle = 40;
					//motor_output2(-20, -5);
				}
				else if (back_infrared_weight == 1)
				{
					angle = -5;
					//motor_output2(-14, -14);
				}
				else if (back_infrared_weight == -1)
				{
					angle = 5;
					//motor_output2(-14, -14);
				}
			}
			else if (back_infrared_amount == 2)
			{
				if (back_infrared_weight == 5)
				{
					angle = -40;
					//motor_output2(-5, -20);
				}
				else if (back_infrared_weight == -5)
				{
					angle = 40;
					//motor_output2(-20, -5);
				}
				else if (back_infrared_weight == 3)
				{
					angle = -20;
					//motor_output2(-5, -20);
				}
				else if (back_infrared_weight == -3)
				{
					angle = 20;
					//motor_output2(-20, -5);
				}
				else if (back_infrared_weight == 0)
				{
					angle = 0;
					//motor_output2(-14, -14);
				}
			}
			steer_output_angle(STEER_DIR, angle);
			speed_control_backward(30,angle);

			if(back_infrared_amount > 4)
			{
				detect_num ++;
				if(detect_num > 2)
				{
					detect_num = 0;
					robot_state = BACKWARD_CHANGE;
					car_distence = gl_distanceTotal;
				}
			}
			else
			{
				detect_num  = 0;
			}
			break;

/************************************后退转换1****************************************/
		case BACKWARD_CHANGE:
			light_bar_open(LIGHT_BAR0);
			light_bar_open(LIGHT_BAR1);
			light_open_some(0x8);
			steer_output_angle(STEER_DIR, -35);
			speed_control_forward(30,angle);
            if((gl_distanceTotal - car_distence)>7)
            {
            	robot_state = BACKWARD_CHANGE2;
            }
		    break;

/************************************后退转换2****************************************/
		case BACKWARD_CHANGE2:
			light_bar_open(LIGHT_BAR0);
			light_bar_open(LIGHT_BAR1);
			light_open_some(0x8);
			steer_output_angle(STEER_DIR, -35);
			speed_control_forward(30,angle);
			if((front_infrared_value & 0x38) && (!(front_infrared_value & 0x03)) && (back_infrared_amount < 3))
			{
				robot_state = FORWARD;
				change_num ++;
			}
			break;

/************************************停车****************************************/
		case STOP:
			light_open_some(0x03);
			light_bar_close(LIGHT_BAR0);
			light_bar_close(LIGHT_BAR1);
			motor_output2(0, 0);
			steer_output_angle(STEER_DIR, 0);
			if(get_char == 's')
			{
				robot_state = last_robot_state;
			}
			break;
		}
	}
}

void speed_control_forward(int expect_speed, int angle)
{
    int speed_error = 0;

    speed_error = expect_speed - gl_curSpeed;

    if(speed_error > 20)
	{
		pwm_output_forward(30, angle);
	}
    else if(speed_error > 10)
    {
    	pwm_output_forward(25, angle);
    }
    else if(speed_error > 5)
    {
    	pwm_output_forward(20, angle);
    }
    else if(speed_error > 0)
    {
    	pwm_output_forward(15, angle);
    }
    else if(speed_error > -5)
    {
    	pwm_output_forward(13, angle);
    }
    else if(speed_error > -10)
    {
    	pwm_output_forward(10, angle);
    }
}

void speed_control_backward(int expect_speed, int angle)
{
    int speed_error = 0;

    speed_error = expect_speed - gl_curSpeed;

    if(speed_error > 20)
    {
    	pwm_output_backward(-30, angle);
    }
    else if(speed_error > 10)
    {
    	pwm_output_backward(-25, angle);
    }
    else if(speed_error > 5)
    {
    	pwm_output_backward(-20, angle);
    }
    else if(speed_error > 0)
    {
    	pwm_output_backward(-15, angle);
    }
    else if(speed_error > -5)
    {
    	pwm_output_backward(-13, angle);
    }
    else if(speed_error > -10)
    {
    	pwm_output_backward(-10, angle);
    }
}

void pwm_output_forward(int pwm_duty, int angle)
{
	int InsideRDiff = 0;			// Speed differential proportion of inside rear wheel      positive PWM
	int insidePwmDuty = 0;

	if(angle > 0)
	{
		if (angle > 44)               //  防止寻址溢出
		{
			angle = 44;
		}
		InsideRDiff = gl_speedDifference[angle];
		insidePwmDuty = pwm_duty * InsideRDiff / 100;
		motor_output2(pwm_duty, insidePwmDuty);
	}
	else
	{
		angle = 0 - angle;
		if (angle > 44)               //  防止寻址溢出
		{
			angle = 44;
		}
		InsideRDiff = gl_speedDifference[angle];
		insidePwmDuty = pwm_duty * InsideRDiff / 100;
		motor_output2(insidePwmDuty, pwm_duty);
	}
}

void pwm_output_backward(int pwm_duty, int angle)
{
	int InsideRDiff = 0;			// Speed differential proportion of inside rear wheel      positive PWM
	int insidePwmDuty = 0;

	if(angle > 0)
	{
		if (angle > 44)               //  防止寻址溢出
		{
			angle = 44;
		}
		InsideRDiff = gl_speedDifference[angle];
		insidePwmDuty = pwm_duty * InsideRDiff / 100;
		motor_output2(pwm_duty, insidePwmDuty);
	}
	else
	{
		angle = 0 - angle;
		if (angle > 44)               //  防止寻址溢出
		{
			angle = 44;
		}
		InsideRDiff = gl_speedDifference[angle];
		insidePwmDuty = pwm_duty * InsideRDiff / 100;
		motor_output2(insidePwmDuty, pwm_duty);
	}
}
