/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     speaker.h
 *
 *        @brief    蜂鸣器硬件抽象层函数头文件
 *
 *        @version  0.1
 *        @date     2012/4/16  20：57
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/16    create orignal file
 * =====================================================================================
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "common.h"

/** 
 * speaker的ID定义
 */
#define   SPEAKER0   ((SPEAKER0_PIN<<16)  | 0x0000)
#define   SPEAKER1   ((SPEAKER1_PIN<<16)  | 0x0001)   /* 测试使用 */


#define   SPEAKER_OFF  LOW_POWER
#define   SPEAKER_ON   HIGH_POWER

/**
 *    @brief   蜂鸣器初始化
 */
void speaker_init(void);

/**
 *    @brief   speaker打开控制函数
 *
 *    @param   speakerid  蜂鸣器的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制蜂鸣器的开关
 */
ER speaker_open(ID speakerid);

/**
 *    @brief   speaker关闭控制函数
 *
 *    @param   speakerid  蜂鸣器的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制蜂鸣器的开关
 */
ER speaker_close(ID speakerid);

/**
 *    @brief   speaker状态获取函数
 *
 *    @param   speakerid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
bool_t speaker_read(ID speakerid);



#endif /* SPEAKER_H_ */
