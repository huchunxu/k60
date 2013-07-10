/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     gyro.h
 *
 *        @brief    陀螺仪硬件抽象层函数头函数
 *
 *        @version  0.1
 *        @date     2012/4/21  18：36
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/21    create orignal file
 * =====================================================================================
 */

#ifndef GYRO_H_
#define GYRO_H_

#include "common.h"

/** 
 * 陀螺仪的ID定义
 */
#define   GYRO0       ((GYRO0_PIN<<16) | 0x0000)
#define   GYRO1       ((GYRO1_PIN<<16) | 0x0001)  /* 测试使用 */

/**
 *    @brief   陀螺仪初始化
 */
void gyro_init(void);

/**
 *    @brief   读取陀螺仪的值
 *
 *    @param   gyroid  陀螺仪的ID号
 *
 *    @return  pulse_num  编码器的寄存器值
 */
vuint16_t gyro_read(ID gyroid);

#endif /* GYRO_H_ */
