/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_ftm_pwm.c
 *
 *        @brief    ftm模块的pwm模块测试
 *
 *        @version  0.1
 *        @date     2012/4/4  14:33:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/4    create orignal file
 * =====================================================================================
 */

#include <stdio.h>

#include "sysinit.h"
#include "exception.h"
#include "ftm_pwm.h"
#include "common.h"
#include "light.h"
#include "sysinit.h"
#include "target_serial.h"
#include "serial.h"

int main(void)
{
    int counter = 0;
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    light_init();                                        /* LED灯初始化 */

    /* 初始化串口 */
    serial_initialize((intptr_t)(NULL));
    
    ftm_pwm_init(FTM_MOD_GET(FTM0),FTM_CH_GET(FTM0_CH1));
    ftm_pwm_init(FTM_MOD_GET(FTM0),FTM_CH_GET(FTM0_CH2));
    ftm_pwm_init(FTM_MOD_GET(FTM1),FTM_CH_GET(FTM1_CH1));
    ftm_pwm_init(FTM_MOD_GET(FTM2),FTM_CH_GET(FTM2_CH0));
    
    printf("%s\n","FTM - PWM test!");
   
    while(1)
    {
        ftm_pwm_output(FTM_MOD_GET(FTM0),FTM_CH_GET(FTM0_CH1),20000);
        ftm_pwm_output(FTM_MOD_GET(FTM0),FTM_CH_GET(FTM0_CH2),10000);
        ftm_pwm_output(FTM_MOD_GET(FTM1),FTM_CH_GET(FTM1_CH1),10000);
        ftm_pwm_output(FTM_MOD_GET(FTM2),FTM_CH_GET(FTM2_CH0),10000);
    }
    return 0;
}
