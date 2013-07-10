/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     steer.h
 *
 *        @brief    电机硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/4/12  21:33
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/12    create orignal file
 * =====================================================================================
 */

#ifndef STEER_H_
#define STEER_H_

#include "common.h"
#include "ftm_pwm.h"

/** 
 * 舵机的ID定义
 */
#define   STEER_DIR       ((STEER_DIR_PIN<<16)   | 0x0000)
#define   STEER_SERVO     ((STEER_SERVO_PIN<<16) | 0x0001) 

/** 
 * 舵机的最值角度定义
 */
#define   STEER_DIR_MAX_ANGLE             40
#define   STEER_DIR_MIN_ANGLE            -40

#define   STEER_SERVO_MAX_ANGLE           45
#define   STEER_SERVO_MIN_ANGLE          -45

/** 
 * 舵机的最值计数值定义
 */
#define   STEER_DIR_MAX_VALUE             2340
#define   STEER_DIR_MIN_VALUE            -2340

#define   STEER_SERVO_MAX_VALUE           2000
#define   STEER_SERVO_MIN_VALUE          -2000

/** 
 * 舵机的中心值定义
 */
#define   STEER_DIR_CENTER      12300
#define   STEER_SERVO_CENTER    9375

/** 
 * 舵机的左右步长定义
 */
#define   LEFT_STEER_DIR_PRES      58
#define   RIGHT_STEER_DIR_PRES     58

#define   LEFT_STEER_SERVO_PRES    30
#define   RIGHT_STEER_SERVO_PRES   30

#define   SERVO_PRES               30

/**
 *    @brief   steer初始化
 */
void steer_init(void);


/**
 *    @brief   steer输出
 *
 *    @param   steerid    电机的ID号
 *    @param   steer_angle 电机占空比
 *
 *    @return  ercd 错误码
 */
ER steer_output_angle(ID steerid, int16_t steer_angle);

/**
 *    @brief   steer输出
 *
 *    @param   steerid         舵机的ID号
 *    @param   steer_add_value 舵机计数值在中心值的基础上增加的值
 *
 *    @return  ercd 错误码
 */
ER steer_output_value(ID steerid, int16_t steer_add_value);


#endif /* STEER_H_ */
