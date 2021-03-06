/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     motor.h
 *
 *        @brief    电机硬件抽象层函数头文件
 *
 *        @version  0.1
 *        @date     2012/4/6  21:16
 *
 *        @author:  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/6    create orignal file
 * =====================================================================================
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "common.h"
#include "ftm_pwm.h"

/** 
 * motor的ID定义
 */

#define   MOTOR_LEFT       ((MOTOR_LEFT_PIN<<16) | 0x0000)
#define   MOTOR_RIGHT      ((MOTOR_RIGHT_PIN<<16) | 0x0001)
#define   MOTOR0 MOTOR_LEFT
#define   MOTOR1 MOTOR_RIGHT

/** 
 * motor的方向引脚
 */
#define   MOTOR_LEFT_DIR_PIN      MOTOR_LEFT_DIRECTION_PIN
#define   MOTOR_RIGHT_DIR_PIN     MOTOR_RIGHT_DIRECTION_PIN

/** 
 * motor的方向定义
 */
/* 摄像头组 */
#define   MOTOR_LEFT_FORWARD      1
#define   MOTOR_LEFT_BACKWARD     0

#define   MOTOR_RIGHT_FORWARD      0
#define   MOTOR_RIGHT_BACKWARD     1

#define   MOTOR_PWM_PRESCALE        (FTM1_PWM_CYCLE / 100)   

/** 
 * motor的方输出最值
 */
#define   MOTOR_MAX_VAL             100
#define   MOTOR_MIN_VAL             -100


/**
 *    @brief   motor初始化
 */
void motor_init(void);

/**
 *    @brief   motor输出
 *
 *    @param   motorid    电机的ID号
 *    @param   motor_duty 电机占空比
 *
 *    @return  ercd 错误码
 */
ER motor_output(ID motorid, int32_t motor_duty);

/**
 *    @brief   两个motor输出
 */
void motor_output2(int32_t motor_left_value, int32_t motor_right_value);

/**
 *    @brief   motor前进方向设置
 *
 *    @param   motorid    电机的ID号
 */
void motor_output_dir_fw(ID motorid);
        
/**
 *    @brief   motor后退方向设置
 *
 *    @param   motorid    电机的ID号
 */
void motor_output_dir_bw(ID motorid);


#endif /* MOTOR_H_ */
