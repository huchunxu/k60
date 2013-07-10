/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     adc.h
 *
 *        @brief    ADC驱动头文件
 *
 *        @version  0.1
 *        @date     2012/4/7 
 *
 *        @author   zhang yue
 *//* ==================================================================================
 *  @0.1    zhang yue  2012/4/7  create orignal file
 * =====================================================================================
 */

#ifndef __ADC_H__
#define __ADC_H__

#include "common.h"

/**
 * 函数接口声明
 */

/**
 *    @brief AD初始化
 *
 *    @param   mod_num  模块号
 *
 *    @return  1     成功
 *    @return  0     失败
 *
 *    @note   
 */
uint8_t adc_init(int mod_num);

/**
 *    @brief 采集一次一路模拟量的AD值    
 *
 *    @param   mod_num  模块号
 *    @param   channel  通道号
 *     
 *    @return  result   16位无符号的AD值    
 *
 *    @note   在ADC_ACCURACY中选择转换精度，在ADC_CLOCK，ADC_PRESCALE中分别选择
 *           时钟与分频因子，在ADC_HARDWARE_AVG_MODE中选择硬件平均方式  
 */
uint16_t ad_once(int mod_num,int channel);

/**
 *    @brief 开始adc转换   
 *
 *    @param   mod_num  模块号
 *    @param   channel  通道号
 *             
 *    @return  1 成功
 *    @return  0 失败   
 */
uint8_t adc_convertstart(int mod_num,int channel);

/**
 *    @brief 停止ADC转换   
 *
 *    @param  mod_num  模块号
 *    @param  channel  通道号
 *             
 *    @return  1 成功
 *    @return  0 失败   
 */
uint8_t adc_convertstop(int mod_num,int channel);


#endif /* __ADC_H__ */
