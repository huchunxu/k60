/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     adc.c
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/4/7 
 *
 *        @author   zhang yue
 *//* ==================================================================================
 *  @0.1    zhang yue  2012/4/7  create orignal file
 * =====================================================================================
 */
#include "adc.h"

/** 
 * ADCSC1A寄存器相关配置
 */

/* ADC 中断: 使能或者禁止 */
#define AIEN_ON           ADC_SC1_AIEN_MASK
#define AIEN_OFF          0x00

/*差分或者单端ADC输入 */
#define DIFF_SINGLE       0x00
#define DIFF_DIFFERENTIAL ADC_SC1_DIFF_MASK


/**
 * ADCCFG1寄存器相关配置
 **/

/* ADC电源设置 */ 
#define ADLPC_LOW         ADC_CFG1_ADLPC_MASK
#define ADLPC_NORMAL      0x00

/* 时钟分频 */
#define ADIV_1            0x00
#define ADIV_2            0x01
#define ADIV_4            0x02
#define ADIV_8            0x03

/* 选择时钟分频系数 */
#define ADC_PRESCALE      ADIV_4 

/* 长采样时间或者短采样时间 */
#define ADLSMP_LONG       ADC_CFG1_ADLSMP_MASK
#define ADLSMP_SHORT      0x00

/* 转换精度 8, 12, 10, 或者 16 (单端) */
#define ACCURACY_MODE_8            0x00
#define ACCURACY_MODE_12           0x01
#define ACCURACY_MODE_10           0x02
#define ACCURACY_MODE_16           0x03

/* 选择AD转换精度 */
#define ADC_ACCURACY               ACCURACY_MODE_16

/* ADC输入时钟源选择 总线，总线/2，”altclk“或者ADC自身异步时钟以减少噪声 */
#define ADICLK_BUS        0x00
#define ADICLK_BUS_2      0x01
#define ADICLK_ALTCLK     0x02
#define ADICLK_ADACK      0x03

/* 选择AD时钟源 */
#define ADC_CLOCK ADICLK_BUS


/** 
 * ADCCFG2寄存器相关配置
 **/

/* 选择通道A，通道B */
#define MUXSEL_ADCB       ADC_CFG2_MUXSEL_MASK
#define MUXSEL_ADCA       0x00

/* 异步时钟输出使能：使能，或者禁止输出 */
#define ADACKEN_ENABLED   ADC_CFG2_ADACKEN_MASK
#define ADACKEN_DISABLED  0x00

/* 高速低速转换时间 */
#define ADHSC_HISPEED     ADC_CFG2_ADHSC_MASK
#define ADHSC_NORMAL      0x00

/* 长采样时间选择：20,12,6或者2个额外的时钟对于长采样时间 */
#define ADLSTS_20          0x00
#define ADLSTS_12          0x01
#define ADLSTS_6           0x02
#define ADLSTS_2           0x03



/** 
 * ADCSC3寄存器相关配置
 **/

/* 平均采样使能或者禁止 */
#define AVGE_ENABLED       ADC_SC3_AVGE_MASK
#define AVGE_DISABLED      0x00

/* MCU产生中断前的平均次数4,8,16，或者32 */
#define AVGS_4             0x00
#define AVGS_8             0x01
#define AVGS_16            0x02
#define AVGS_32            0x03

/* 选择是否使用硬件平均以及硬件平均次数 */
#define ADC_HARDWARE_AVG_MODE (AVGE_ENABLED|AVGS_32)


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
uint8_t adc_init(int mod_num)
{
    if(ADC_ID_SET(mod_num) == ADC0)
    {
        /* 使能ADC0的时钟 */
        SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );
    }
    else if(ADC_ID_SET(mod_num) == ADC1)
    {      
        /* 使能ADC1的时钟 */
        SIM_SCGC3 |= (SIM_SCGC3_ADC1_MASK );
    }
    else
    {
        return 0;
    }
    return 1;
}

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
uint16_t ad_once(int mod_num,int channel)
{
    uint16_t result = 0;
    
    /* 配置相关寄存器 */
    adc_convertstart(mod_num, channel);
    
    /* 得到ADC0模块的转换结果 */
    if(ADC_ID_SET(mod_num) == ADC0)
    {
        while (( ADC0_SC1A & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK)
        {
        }
        result = ADC0_RA;        
        ADC0_SC1A &= ~ADC_SC1_COCO_MASK;
    }
    
    /* 得到ADC1模块的转换结果 */
    else
    {
        while (( ADC1_SC1A & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK)
        {
        }
        result = ADC1_RA;        
        ADC1_SC1A &= ~ADC_SC1_COCO_MASK;
    }
    return result;
}


/**
 *    @brief 开始adc转换   
 *
 *    @param   mod_num  模块号
 *    @param   channel  通道号
 *             
 *    @return  1 成功
 *    @return  0 失败   
 */
uint8_t adc_convertstart(int mod_num,int channel)
{
   if(mod_num == 0)
    {
        if((channel >= 0) && (channel < 24))                            
        {
            ADC0_CFG1 = ADLPC_NORMAL
                       | ADC_CFG1_ADIV(ADC_PRESCALE)
                       | ADLSMP_LONG
                       | ADC_CFG1_MODE(ADC_ACCURACY)
                       | ADC_CFG1_ADICLK(ADC_CLOCK);
            ADC0_CFG2 =  MUXSEL_ADCA
                       | ADACKEN_DISABLED
                       | ADHSC_HISPEED
                       | ADC_CFG2_ADLSTS(ADLSTS_20);
            ADC0_SC3  = ADC_HARDWARE_AVG_MODE;
            ADC0_SC1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(channel);       
         }
        else
        {
            return 0;
        }
    }
    else
    {
        if((channel >= 0) && (channel < 24))                             
        {
            ADC1_CFG1 = ADLPC_NORMAL
                      | ADC_CFG1_ADIV(ADC_PRESCALE)
                      | ADLSMP_LONG
                      | ADC_CFG1_MODE(ADC_ACCURACY)
                      | ADC_CFG1_ADICLK(ADC_CLOCK);
            ADC1_CFG2 =  MUXSEL_ADCA
                      | ADACKEN_DISABLED
                      | ADHSC_HISPEED
                      | ADC_CFG2_ADLSTS(ADLSTS_20);
            ADC1_SC3 = ADC_HARDWARE_AVG_MODE;
            ADC1_SC1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(channel);  
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

/**
 *    @brief 停止ADC转换   
 *
 *    @param   mod_num  模块号
 *    @param  channel  通道号
 *             
 *    @return  1 成功
 *    @return  0 失败   
 */
uint8_t adc_convertstop(int mod_num,int channel)
{
    if(ADC_ID_SET(mod_num) == ADC0)
    {
        if((channel >= 0) && (channel < 24))                             
        {
            ADC0_SC1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(0x1F);
        }
        else
        {
            return 0;
        }
    }
    else if(ADC_ID_SET(mod_num) == ADC1)
    {
        if((channel >= 0) && (channel < 24))                            
        {
            ADC1_SC1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(0x1F);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
