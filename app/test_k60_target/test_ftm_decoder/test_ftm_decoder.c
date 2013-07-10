/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_ftm_pwm.c
 *
 *        @brief    ftm模块的脉冲累加模块测试
 *
 *        @version  0.1
 *        @date     2012/4/4  15:36:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/4    create orignal file
 * =====================================================================================
 */
#include <stdio.h>

#include "exception.h"
#include"ftm_decoder.h"
#include"common.h"
#include "light.h"
#include "sysinit.h"
#include "target_serial.h"
#include "serial.h"

int main(void)
{
    vuint32_t PulseNum = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    light_init();                                        /* LED灯初始化 */
    
    /* 初始化串口 */
    serial_initialize((intptr_t)(NULL));
    
    ftm_decoder_init(PTA8_9);

    printf("%s\n","FTM - PWM test!");
   
    while(1)
    {
        PulseNum = FTM_CNT_REG(FTM1_BASE_PTR); //读FTM1的CNT寄存器的值
        
        if(PulseNum > 5000)
        {
            light_change(LIGHT1);
        }
    }
    return 0;
}
