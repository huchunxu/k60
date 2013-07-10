/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     ftm_pwm.h
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/3/18 14:14:45
 *
 *        @author   Zhang Yue 
 *//* ==================================================================================
 *  @0.1    Zhang Yue 2012/3/26  create orignal file
 * =====================================================================================
 */

#ifndef PWM_H_
#define PWM_H_

#include"common.h"

/*
 *  各通道可供选择引脚如下：
 *  FTM0CH5~FTM0CH7:  PTA0~PTA2
 *  FTM0CH0~FTM0CH4  PTA3~PTA7
 *  FTM0CH3:  PTC1~PTC4
 *  FTM0CH4~FTM0CH7:  PTD4~PTD7
 *
 *  FTM1CH0: PTA8  PTA12  PTB0
 *  FTM1CH1: PTA9  PTA13  PTB1
 *  
 *  FTM2CH0: PTA10  PTB18
 *  FTM2CH1: PTA11  PTB19
*/
/*定义通道所选引脚*/
#define  FTM0CH0_PIN   PTC1
#define  FTM0CH1_PIN   PTC2   /* 方向 */
#define  FTM0CH2_PIN   PTC3
#define  FTM0CH3_PIN   PTC4
#define  FTM0CH4_PIN   PTD4   /* 方向 */
#define  FTM0CH5_PIN   PTD5  
#define  FTM0CH6_PIN   PTD6   /* 没有用到 */
#define  FTM0CH7_PIN   PTD7   /* 没有用到 */
#define  FTM1CH0_PIN   PTB0
#define  FTM1CH1_PIN   PTB1
#define  FTM2CH0_PIN   PTA10
#define  FTM2CH1_PIN   PTB19

/*各模块周期相关计数次数定义*/
//#define FTM0_PWM_CYCLE 62500      /* 50M时钟 八分频 10ms周期 */
//#define FTM0_PWM_CYCLE 12500      /* 50M时钟 四分频 1ms周期 */
#define FTM0_PWM_CYCLE 12500//50000      /* 50M时钟 四分频 4ms周期 */
#define FTM1_PWM_CYCLE 12500      /* 50M时钟 四分频 1ms周期 */
#define FTM2_PWM_CYCLE 62500

/**
 *    @brief 初始化所选通道为PWM输出
 *
 *    @param   module    所选模块（可取 MODULE0,MODULE1,MODULE2）
 *    @param   channel   所选通道(当module==MODULE1,可取0~7，module为其余值，可取0~1)
 *
 *    @return  错误类型
 *
 *    @note   可在头文件中修改每个模块的工作方式，初始化周期，每个通道所选引脚。
 */
extern ER ftm_pwm_init(ID module, ID channel);

/**
 *    @brief 输出所选通道的PWM波形
 *
 *    @param  module      所选模块（可取 MODULE0,MODULE1,MODULE2）
 *    @param  channel     所选通道(当module==MODULE1,可取0~7，module为其余值，可取0~1)
 *    @param  duty_count  占空比相关计数次数
 *
 *    @return  错误类型
 *
 *    @note   
 */
extern ER ftm_pwm_output(ID module, ID channel, uint32_t duty);

#endif /* PWM_H_ */
