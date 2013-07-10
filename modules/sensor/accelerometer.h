/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     accelerometer.h
 *
 *        @brief    加速度传感器硬件抽象层函数头函数
 *
 *        @version  0.1
 *        @date     2012/4/21  21：26
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/21    create orignal file
 * =====================================================================================
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "common.h"

/** 
 * 加速度传感器的ID定义
 */
#define   ACC0       ((ACC0_PIN<<16) | 0x0000)
#define   ACC1       ((ACC1_PIN<<16) | 0x0001) /* 测试使用 */
/**
 *    @brief   陀螺仪初始化
 */
void acc_init(void);

/**
 *    @brief   读取加速度传感器的值
 *
 *    @param   accid  加速度传感器的ID号
 *
 *    @return  acc_value  加速度传感器的寄存器值
 */
vuint16_t acc_read(ID accid);




#endif /* ACCELEROMETER_H_ */
