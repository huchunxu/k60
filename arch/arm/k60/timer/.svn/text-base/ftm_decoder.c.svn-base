/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     ftm_decoder.c
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/3/24 19:18
 *
 *        @author   Cheng Peng ,312770398@qq.com
 *//* ==================================================================================
 *  @0.1    Cheng Peng 2012/3/24  create orignal file
 *  @0.2    Hu Chunxu  2012/4/4   修改了代码规范
 * =====================================================================================
 */

#include "ftm_decoder.h"

/**
 *  分频系数DIVIDE的宏定义 
 */
#define FTM_DEC_DEV1    0
#define FTM_DEC_DEV2    1
#define FTM_DEC_DEV4    2
#define FTM_DEC_DEV8    3
#define FTM_DEC_DEV16   4
#define FTM_DEC_DEV32   5
#define FTM_DEC_DEV64   6 
#define FTM_DEC_DEV128  7

/**   
 *    @brief    编码器初始化函数
 *    
 *    @param    port     端口号，由宏定义声明
 *    
 *    @return   ER       错误码
 *      
 *    @note    系统时钟频率最好是大于输入信号频率，可同过分频系数DIVIDE对系统进行1~128分频（寄存器FTMx_SC的后三位）
*/
ER ftm_decoder_init(PORT port)
{
    switch (port)
    {
        case PTA8_9:                            
            SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK; /* 使能FTM时钟 */

            /* 选择引脚复用功能 */
            PORTA_PCR8 = PORT_PCR_MUX(6);
            PORTA_PCR9 = PORT_PCR_MUX(6);

            /* 配置成正交编码功能  */
            FTM_CNTIN_REG(FTM1_BASE_PTR) = 0x0000; /* 初始值 */
            FTM_MOD_REG(FTM1_BASE_PTR)   = 0xffff; /* 可根据需要设定 */

            FTM_FMS_REG(FTM1_BASE_PTR)   = 0x00;   /* write protect disable */
            FTM_MODE_REG(FTM1_BASE_PTR)  = 0x05;   /* 不使能write protect 功能，缺省值;FTMEN=1; */

            /* 0001,1000  CLKS=11：extern Clock;PS=000|DIVIDE：system clock divided by 1or2or4or8or16or32or64or128； */
            FTM_SC_REG(FTM1_BASE_PTR)     = 0x18 | FTM_DEC_DEV1; 
            /* 0000,1101 不是能过滤，QUADMODE=1：count and direction mode；QUADIR=1:increasing;QUADEN=1 */
            FTM_QDCTRL_REG(FTM1_BASE_PTR) = 0x0d; 
            break;
            
        case PTA10_11:
            SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK; /* 使能FTM时钟 */

            /* 选择引脚复用功能 */
            PORTA_PCR10 = PORT_PCR_MUX(6);
            PORTA_PCR11 = PORT_PCR_MUX(6);

            /* 配置成正交编码功能  */
            FTM_CNTIN_REG(FTM2_BASE_PTR) = 0x0000; /* 初始值 */
            FTM_MOD_REG(FTM2_BASE_PTR)   = 0xffff; /* 可根据需要设定 */

            FTM_FMS_REG(FTM2_BASE_PTR)   = 0x00;   /* write protect disable */
            FTM_MODE_REG(FTM2_BASE_PTR)  = 0x05;   /* 不使能write protect 功能，缺省值;FTMEN=1; */

            /* 0001,1000   CLKS=11：extern Clock;PS=000|DIVIDE：system clock divided by 1or2or4or8or16or32or64or128； */
            FTM_SC_REG(FTM2_BASE_PTR)     = 0x18 | FTM_DEC_DEV1;
            /* 0000,1101 不是能过滤，QUADMODE=1：count and direction mode；QUADIR=1:increasing;QUADEN=1 */
            FTM_QDCTRL_REG(FTM2_BASE_PTR) = 0x0d;
            break;
            
        case PTA12_13: 
            SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK; /* 使能FTM时钟 */

            /* 选择引脚复用功能 */
            PORTA_PCR12 = PORT_PCR_MUX(7);
            PORTA_PCR13 = PORT_PCR_MUX(7);

            /* 配置成正交编码功能  */
            FTM_CNTIN_REG(FTM1_BASE_PTR) = 0x0000; /* 初始值 */
            FTM_MOD_REG(FTM1_BASE_PTR)   = 0xffff; /* 可根据需要设定 */

            FTM_FMS_REG(FTM1_BASE_PTR)   = 0x00;   /* write protect disable */
            FTM_MODE_REG(FTM1_BASE_PTR)  = 0x05;   /* 不使能write protect 功能，缺省值;FTMEN=1; */

            /* 0001,1000   CLKS=11：extern Clock;PS=000|DIVIDE：system clock divided by 1or2or4or8or16or32or64or128； */
            FTM_SC_REG(FTM1_BASE_PTR)     = 0x18 | FTM_DEC_DEV1; 
            /* 0000,1101 不是能过滤，QUADMODE=1：count and direction mode；QUADIR=1:increasing;QUADEN=1 */
            FTM_QDCTRL_REG(FTM1_BASE_PTR) = 0x0d; 
            break;
            
        case PTB0_1:
            SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK; /* 使能FTM时钟 */

            /* 选择引脚复用功能 */
            PORTB_PCR0 = PORT_PCR_MUX(6);
            PORTB_PCR1 = PORT_PCR_MUX(6);

            /* 配置成正交编码功能  */
            FTM_CNTIN_REG(FTM1_BASE_PTR) = 0x0000; /* 初始值 */
            FTM_MOD_REG(FTM1_BASE_PTR)   = 0xffff; /* 可根据需要设定 */

            FTM_FMS_REG(FTM1_BASE_PTR)   = 0x00;   /* write protect disable */
            FTM_MODE_REG(FTM1_BASE_PTR)  = 0x05;   /* 不使能write protect 功能，缺省值;FTMEN=1; */

            /* 0001,1000   CLKS=11：extern Clock;PS=000|DIVIDE：system clock divided by 1or2or4or8or16or32or64or128； */
            FTM_SC_REG(FTM1_BASE_PTR)     = 0x18 | FTM_DEC_DEV1; 
            /* 0000,1101 不是能过滤，QUADMODE=1：count and direction mode；QUADIR=1:increasing;QUADEN=1 */
            FTM_QDCTRL_REG(FTM1_BASE_PTR) = 0x0d; 
            break;
            
        case PTB18_19:
            SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK; /* 使能FTM时钟 */

            /* 选择引脚复用功能 */
            PORTB_PCR18 = PORT_PCR_MUX(6);
            PORTB_PCR19 = PORT_PCR_MUX(6);

            /* 配置成正交编码功能  */
            FTM_CNTIN_REG(FTM2_BASE_PTR) = 0x0000; /* 初始值 */
            FTM_MOD_REG(FTM2_BASE_PTR) = 0xffff; /* 可根据需要设定 */

            FTM_FMS_REG(FTM2_BASE_PTR) = 0x00; /* write protect disable */
            FTM_MODE_REG(FTM2_BASE_PTR) = 0x05; /* 不使能write protect 功能，缺省值;FTMEN=1; */

            /* 0001,1000   CLKS=11：extern Clock;PS=000|DIVIDE：system clock divided by 1or2or4or8or16or32or64or128； */
            FTM_SC_REG(FTM2_BASE_PTR) = 0x18 | FTM_DEC_DEV1;
            /* 0000,1101 不是能过滤，QUADMODE=1：count and direction mode；QUADIR=1:increasing;QUADEN=1 */
            FTM_QDCTRL_REG(FTM2_BASE_PTR) = 0x0d;
            break;
            
        default:
            return E_PIN;
    }
    
    return E_OK;
}



