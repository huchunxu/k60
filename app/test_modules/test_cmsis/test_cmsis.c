/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_cmsis.c
 *
 *        @brief    测试cmsis库
 *
 *        @version  0.1
 *        @date     2012/4/6  18:53
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/6    create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>

#include "common.h"
#include "arm_math.h"
#include "light.h"
#include "sysinit.h"
#include "target_serial.h"
#include "serial.h"
#include "exception.h"
#include "sys_timer.h"


#define DELTA           (0.000001f)             //浮点数精度

float32_t a = 0.45454;                          //乱来的数据
float32_t cosa, sina, cos2a, sin2a;             //a 的余弦值、正弦值、余弦值平方、正弦值平方、
float32_t test;                                 //测试结果

int main(void)
{
    float32_t diff;                             //差值
    uint32_t time_start = 0;
    uint32_t time_end = 0;
    uint32_t time_cost = 0;
    q7_t  as = 85;
    q7_t  bs = 42;
    q7_t  cd = 0;
    q7_t  as_v[2] = {1,2};
    q7_t  bs_v[2] = {3,4};
    q7_t  cd_v[2] = {0,0};
    q7_t  as_v10[10] = {1,2,1,2,1,2,1,2,1,2};
    q7_t  bs_v10[10] = {1,2,1,2,1,2,1,2,1,2};
    q7_t  cd_v10[10] = {0,0};
    q31_t result;
    
    light_init();              
    sys_timer_init();    
    gpio_init(1, 4, OUT_PUT, LIGHT_ON);
    
    /* 初始化串口 */
    serial_initialize((intptr_t)(NULL));
    
    printf("%s\n", "CMSIS test!");

    cosa = arm_cos_f32(a);                      //求cos值，cosa = cos(a);
    sina = arm_sin_f32(a);                      //求sin值，sina = sin(a);

    arm_mult_f32(&cosa, &cosa, &cos2a, 1);      //乘法，cos2a = cosa * cosa ，即平方
    arm_mult_f32(&sina, &sina, &sin2a, 1);      //乘法，sin2a = sina * sina ，即平方

    arm_add_f32(&cos2a, &sin2a, &test, 1);      //加法，test = cos2a + sin2a = cosa * cosa  + sina * sina = 1

    diff = fabsf(1.000000000 - test);           //求绝对值
    
    /* 求点积 */
    sys_timer_read(&time_start);
    arm_dot_prod_q7(as_v, bs_v, 2, &result);
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
    
    sys_timer_read(&time_start);
    cd = as_v[0] * bs_v[0] + as_v[1] * bs_v[1];
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;

    /* 求反 */
    sys_timer_read(&time_start);
    arm_negate_q7(&as, &cd, 1);
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
    
    sys_timer_read(&time_start);
    cd = 0- as;
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
    
    /* 向量加法 */
    sys_timer_read(&time_start);
    arm_add_q7(as_v10, bs_v10, cd_v10, 10);
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
            
    sys_timer_read(&time_start);
    cd_v10[0] = as_v10[0] + bs_v10[0];
    cd_v10[1] = as_v10[1] + bs_v10[1];
    cd_v10[2] = as_v10[2] + bs_v10[2];
    cd_v10[3] = as_v10[3] + bs_v10[3];
    cd_v10[4] = as_v10[4] + bs_v10[4];
    cd_v10[5] = as_v10[5] + bs_v10[5];
    cd_v10[6] = as_v10[6] + bs_v10[6];
    cd_v10[7] = as_v10[7] + bs_v10[7];
    cd_v10[8] = as_v10[8] + bs_v10[8];
    cd_v10[9] = as_v10[9] + bs_v10[9];
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;

    /* 加法 */
    sys_timer_read(&time_start);
    arm_add_q7(&as, &bs, &cd, 1);
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
            
    sys_timer_read(&time_start);
    cd =as+bs;
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;

    /* 减法 */
    sys_timer_read(&time_start);
    arm_sub_q7(&as, &bs, &cd, 1);
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
            
    sys_timer_read(&time_start);
    cd =as-bs;
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
    
    /* 乘法 */
    sys_timer_read(&time_start);
    arm_mult_q7(&as, &bs, &cd, 1);
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
            
    sys_timer_read(&time_start);
    cd =as*bs;
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;

    /* 移位 */
    sys_timer_read(&time_start);
    arm_shift_q7(as, -2, cd, 1);
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
    
    sys_timer_read(&time_start);
    cd = as >> 2;
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
    
    sys_timer_read(&time_start);
    cd = as / 4;
    sys_timer_read(&time_end);
    time_cost = time_start - time_end;
    
    if( diff <= DELTA)                          //如果测试结果在精度范围之内
    {
        while(1)
        {
            printf("%s\n", "CMSIS is OK!");
        }
    }
    
    return 1;
}
