/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     motor_robot.h
 *
 *        @brief    电机硬件抽象层函数头文件
 *
 *        @version  0.1
 *        @date     2012/10/17  21:16
 *
 *        @author:  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/10/17    create orignal file
 * =====================================================================================
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "common.h"
#include "ftm_pwm.h"

/** 
 * motor的ID定义
 */
#define   MOTOR0_ROBOT      ((MOTOR0_ROBOT_PIN<<16) | 0x0000)
#define   MOTOR1_ROBOT      ((MOTOR1_ROBOT_PIN<<16) | 0x0001)
#define   MOTOR2_ROBOT      ((MOTOR2_ROBOT_PIN<<16) | 0x0002)
#define   MOTOR3_ROBOT      ((MOTOR3_ROBOT_PIN<<16) | 0x0003)

#define   MOTOR_LF          MOTOR0_ROBOT
#define   MOTOR_RF          MOTOR1_ROBOT
#define   MOTOR_LR          MOTOR2_ROBOT
#define   MOTOR_RR          MOTOR3_ROBOT

#define   ANGLE_MAX         60


/** 
 * motor的方向引脚
 */
#define   MOTOR0_INA_PIN     MOTOR0_DIR_INA_PIN
#define   MOTOR0_INB_PIN     MOTOR0_DIR_INB_PIN
#define   MOTOR1_INC_PIN     MOTOR1_DIR_INC_PIN
#define   MOTOR1_IND_PIN     MOTOR1_DIR_IND_PIN
#define   MOTOR2_INA_PIN     MOTOR2_DIR_INA_PIN
#define   MOTOR2_INB_PIN     MOTOR2_DIR_INB_PIN
#define   MOTOR3_INC_PIN     MOTOR3_DIR_INC_PIN
#define   MOTOR3_IND_PIN     MOTOR3_DIR_IND_PIN

/** 
 * motor的方向定义
 */
/* 摄像头组 */
#define   MOTOR_HIGH      1
#define   MOTOR_LOW       0

#define   MOTOR_PWM_PRESCALE        (FTM1_PWM_CYCLE / 100)   

/** 
 * motor的方输出最值
 */
#define   MOTOR_MAX_VAL             100
#define   MOTOR_MIN_VAL             -100


/**
 *    @brief   motor初始化
 */
void motor_robot_init(void);

/**
 *    @brief   motor输出
 *
 *    @param   motorid    电机的ID号
 *    @param   motor_duty 电机占空比
 *
 *    @return  ercd 错误码
 */
ER motor_robot_output(ID motorid, int32_t motor_duty);

/**
 *    @brief   motor*4输出
 */
void motor_robot_handle(int speed, int angle);

/**
 *    @brief   motor*4输出
 */
void motor_robot_output4(int LR_PWM, int LF_PWM, int RR_PWM, int RF_PWM);

/**
 *    @brief   motor前进方向设置
 *
 *    @param   motorid    电机的ID号
 */
void motor_robot_output_dir_fw(ID motorid);
        
/**
 *    @brief   motor后退方向设置
 *
 *    @param   motorid    电机的ID号
 */
void motor_robot_output_dir_bw(ID motorid);


#endif /* MOTOR_H_ */
