/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**
 *        @file     Infrared.c
 *
 *        @brief    红外抽象层函数
 *
 *        @version  0.1
 *        @date     2012/10/17  15：36
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/10/17    create orignal file
 * =====================================================================================
 */

#ifndef INFRARED_H_
#define INFRARED_H_

#include "common.h"

/**
 * infrared的ID定义
 */
#define   INFRARED0            ((INFRARED0_PIN<<16)  | 0x0000)
#define   INFRARED1            ((INFRARED1_PIN<<16)  | 0x0001)
#define   INFRARED2            ((INFRARED2_PIN<<16)  | 0x0002)
#define   INFRARED3            ((INFRARED3_PIN<<16)  | 0x0003)
#define   INFRARED4            ((INFRARED4_PIN<<16)  | 0x0004)
#define   INFRARED5            ((INFRARED5_PIN<<16)  | 0x0005)
#define   INFRARED6            ((INFRARED6_PIN<<16)  | 0x0006)
#define   INFRARED7            ((INFRARED7_PIN<<16)  | 0x0007)
#define   INFRARED8            ((INFRARED8_PIN<<16)  | 0x0008)
#define   INFRARED9            ((INFRARED9_PIN<<16)  | 0x0009)
#define   INFRARED10           ((INFRARED10_PIN<<16) | 0x000a)
#define   INFRARED11           ((INFRARED11_PIN<<16) | 0x000b)

/**
 * 红外的状态宏定义
 */
#define INFRARED_ON        HIGH_POWER
#define INFRARED_OFF       LOW_POWER

/**
 * 红外的位置
 */
#define INFRARED_FRONT      1
#define INFRARED_BACK       0

/**
 *    @brief   红外初始化
 */
void infrared_init(void);


/**
 *    @brief   读取红外的值
 *
 *    @param   infraredid  开关的ID号
 *
 *    @return  infrared_state 开关的电平状态
 */
bool_t infrared_read(ID infraredid);

/**
 *    @brief   读取前排红外的值
 */
int infrared_read_loc(int infrared_loc);

/**
 *    @brief   从右向左找到第一个红外的值
 */
int infrared_read_num(int infrared_value);

/**
 *    @brief   读取传感器亮灯的总数
 */
int infrared_read_amount(int infrared_value);

/**
 *    @brief   读取传感器亮灯的权重
 */
int infrared_read_weight(int infrared_value);
#endif /* INFRARED_H_ */
