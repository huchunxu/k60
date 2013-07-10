/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     telecontrol.h
 *
 *        @brief    红外线硬件抽象层函数头函数
 *
 *        @version  0.1
 *        @date     2012/5/8    13:31
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/8    create orignal file
 * =====================================================================================
 */

#ifndef TELECTRL_H_
#define TELECTRL_H_

#include "common.h"

/** 
 * 红外接受器的ID定义
 */
#define   TELECTRLA      ((TELECTRLA_PIN<<16) | 0x0000)
#define   TELECTRLB      ((TELECTRLB_PIN<<16) | 0x0001)


/** 
 * 红外接受器的状态宏定义
 */
#define TELECTRL_S        HIGH_POWER         
#define TELECTRL_NS       LOW_POWER

/**
 *    @brief   红外接受器初始化
 */
void telectrl_init(void);

/**
 *    @brief   读取红外接受器的值
 *
 *    @param   telectrl_id  红外接受器的ID号
 *
 *    @return  telectrl_state 红外接受器的电平状态
 */
bool_t telectrl_read(ID telectrl_id);


#endif /* INFRA_H_ */
