/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     light.h
 *
 *        @brief    light.c header file
 *
 *        @version  0.1
 *        @date     2012/2/14 15:35:40
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/2/14   create orignal file
 * =====================================================================================
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "gpio.h"
#include "common.h"

/** 
 * light的ID定义
 */
#define   LIGHT0      ((LIGHT0_PIN<<16)  | 0x0000)
#define   LIGHT1      ((LIGHT1_PIN<<16)  | 0x0001)
#define   LIGHT2      ((LIGHT2_PIN<<16)  | 0x0002)
#define   LIGHT3      ((LIGHT3_PIN<<16)  | 0x0003)    
#define   LIGHT4      ((LIGHT4_PIN<<16)  | 0x0004)
#define   LIGHT5      ((LIGHT5_PIN<<16)  | 0x0005)    
#define   LIGHT6      ((LIGHT6_PIN<<16)  | 0x0006)
#define   LIGHT7      ((LIGHT7_PIN<<16)  | 0x0007)    
#define   LIGHT8      ((LIGHT8_PIN<<16)  | 0x0008)     /* 测试使用 */

#define   LIGHT_BAR0   ((LIGHT_BAR0_PIN<<16)  | 0x0000)
#define   LIGHT_BAR1   ((LIGHT_BAR1_PIN<<16)  | 0x0000)

/** 
 * light的状态宏定义
 */
#define LIGHT_ON        LOW_POWER         
#define LIGHT_OFF       HIGH_POWER        

/**
 *    @brief   light初始化
 */
void light_init(void);

/**
 *    @brief   light开灯控制函数
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
ER light_open(ID lightid);

/**
 *    @brief   打开多个light
 *
 *    @param   light_mask  多个灯的掩码
 */
void light_open_some(uint8_t light_mask);

/**
 *    @brief   关闭多个light
 *
 *    @param   light_mask  多个灯的掩码
 */
void light_close_some(uint8_t light_mask);

/**
 *    @brief   light关灯控制函数
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
ER light_close(ID lightid);

/**
 *    @brief   light状态变化
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   切换指示灯亮暗
 */

/**
 *    @brief   light状态获取函数
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
bool_t light_read(ID lightid);

/**
 *    @brief   light状态变化
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   切换指示灯亮暗
 */
ER light_change(ID lightid);

void light_bar_open(int light_bar_id);
void light_bar_close(int light_bar_id);
void light_bar_flash(void);

#endif
