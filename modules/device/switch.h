/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     switch.h
 *
 *        @brief    开关硬件抽象层函数头文件
 *
 *        @version  0.1
 *        @date     2012/4/6  20:49
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/6    create orignal file
 * =====================================================================================
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "common.h"

/** 
 * switch的ID定义
 */
#define   SWITCH_START0      ((SWITCH0_PIN<<16)  | 0x0000)
#define   SWITCH_START1      ((SWITCH0_PIN<<16)  | 0x0001)
#define   SWITCH0            ((SWITCH0_PIN<<16)  | 0x0002)
#define   SWITCH1            ((SWITCH1_PIN<<16)  | 0x0003)
#define   SWITCH2            ((SWITCH2_PIN<<16)  | 0x0004)
#define   SWITCH3            ((SWITCH3_PIN<<16)  | 0x0005)
#define   SWITCH4            ((SWITCH0_PIN<<16)  | 0x0006)
#define   SWITCH5            ((SWITCH1_PIN<<16)  | 0x0007)
#define   SWITCH6            ((SWITCH2_PIN<<16)  | 0x0008)
#define   SWITCH7            ((SWITCH3_PIN<<16)  | 0x0009)
#define   SWITCH8            ((SWITCH8_PIN<<16)  | 0x000a)   /* 测试使用 */

#define   SWITCH_GROUP0      0


/** 
 * 开关的状态宏定义
 */
#define SWITCH_ON        HIGH_POWER         
#define SWITCH_OFF       LOW_POWER

/**
 *    @brief   light初始化
 */
void switch_init(void);

/**
 *    @brief   读取开关的值
 *
 *    @param   switchid  开关的ID号
 *
 *    @return  switch_state 开关的电平状态
 */
bool_t switch_read(ID switchid);

/**
 *    @brief   读取8位开关的值
 *
 *    @param   switchid  开关的ID号
 *
 *    @return  switch_state 开关的电平状态
 */
uint8_t switch_read_8bit(ID switchid);



#endif /* SWITCH_H_ */
