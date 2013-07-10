/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     ftm_decoder.h
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/3/24 19:18
 *
 *        @author   Cheng Peng ,312770398@qq.com
 *//* ==================================================================================
 *  @0.1    Cheng Peng 2012/3/24  create orignal file
 * =====================================================================================
 */
#ifndef COUNTER_H_
#define COUNTER_H_

/**
 * 头文件包含
 */
#include "common.h"

/* PORT的宏定义 */
#define PTA8_9       0             /* PTA8   FTM1_QD_PHA     ALT6 */
                                   /* PTA9   FTM1_QD_PHB     ALT6 */
#define PTA10_11     1             /* PTA10  FTM2_QD_PHA     ALT6 */
                                   /* PTA11  FTM2_QD_PHB     ALT6 */
#define PTA12_13     2             /* PTA12  FTM1_QD_PHA     ALT7 */
                                   /* PTA13  FTM1_QD_PHA     ALT7 */
#define PTB0_1       3             /* PTB0   FTM1_QD_PHA     ALT6 */
                                   /* PTB1   FTM1_QD_PHA     ALT6 */
#define PTB18_19     4             /* PTB18  FTM2_QD_PHA     ALT6 */
                                   /* PTB19  FTM2_QD_PHA     ALT6 */    

/**   
 *    @brief    编码器初始化函数
 *    
 *    @param    port     端口号，由宏定义声明
 *    
 *    @return   ER       错误码
 *    
 *    @note    系统时钟频率最好是大于输入信号频率，可同过分频系数DIVIDE对系统进行1~128分频（寄存器FTMx_SC的后三位）
*/
extern ER ftm_decoder_init(PORT port);


#endif /* COUNTER_H_ */
