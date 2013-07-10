/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     decoder.h
 *
 *        @brief    编码器硬件抽象层函数头文件
 *
 *        @version  0.1
 *        @date     2012/4/18  14：48
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/18    create orignal file
 * =====================================================================================
 */
#ifndef DECODER_H_
#define DECODER_H_


#include "common.h"
#include "ftm_decoder.h"

/** 
 * 编码器的ID定义
 */
#define   DECODER      ((DECODER0_MOD<<16) | 0x0000)

#define   DECODER_PIN       DECODER0_PIN_DEF    /*编码器引脚为LPTMR输入捕捉引脚*/

#define   DECODER_CNT       DECODER0_CNT_PTR     /*编码器地址设定为LPTMR地址*/

/**
 * 	Encoder Pulse Accumulate
 */
// DISTANCE_PRESCALE    每厘米脉冲数
#define   DISTANCE_PRESCALE          35       // 400

extern uint32_t	gl_distanceTotal;       /*remeber the distance*/
extern uint16_t	gl_curSpeed;


/**
 *    @brief   编码器初始化
 */
void decoder_init(intptr_t exinf);

/**
 *    @brief   读取开关的值
 *
 *    @param   decoderid  编码器的ID号
 *
 *    @return  pulse_num  编码器的寄存器值
 */
volatile uint32_t decoder_read(ID decoderid);

/**
 *    @brief   清零当前的计数值
 *
 *    @note  关闭lptmr寄存器的使能即可以清零，打开使能便重新从零开始计数。
 */
void decoder_clear(void);

/**
 *    @brief   Calculate Current Speed and distance
 */
void calculateCurSpeed(void);

#endif /* DECODER_H_ */
