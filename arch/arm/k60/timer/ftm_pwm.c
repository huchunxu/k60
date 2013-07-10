/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     ftm_pwm.c
 *
 *        @brief    ftm模块pwm驱动底层
 *
 *        @version  0.1
 *        @date     2012/3/18 14:14:45
 *
 *        @author   Zhang Yue 
 *//* ==================================================================================
 *  @0.1    Zhang Yue 2012/3/26  create orignal file
 * =====================================================================================
 */
#include"ftm_pwm.h"


#define  FTM0_INIT_VALUE     0
#define  FTM1_INIT_VALUE     0
#define  FTM2_INIT_VALUE     0

#define  PWM_INIT_VALUE 0
#define  CNTIN_VALUE 0

/*----------------------------------------------------------------
 * PWMx_PRESCALE的值与对应的分频因子如下：
 * 0 prescale factor = 1
 * 1 prescale factor = 2
 * 2 prescale factor =  4
 * 3 prescale factor =  8
 * 4 prescale factor =  16
 * 5 prescale factor =  32
 * 6 prescale factor =  64
 * 7 prescale factor =  128
 -----------------------------------------------------------------*/
/*各模块预分频因子定义*/
#define  FTM0_PWM_PRESCALE  2
#define  FTM1_PWM_PRESCALE  2
#define  FTM2_PWM_PRESCALE  3

/*------------------------------------------------------------------
 *  PWMx_CLOCK_SOURCE的值与对应的时钟源如下:
 *  0 No clock selected(this in effect disable the FTM counter)
 *  1 system clock
 *  2 fixed frequency
 *  3 external clock
 * ---------------------------------------------------------------*/
/*各模块时钟源选择定义*/
#define  FTM0_PWM_CLK  1
#define  FTM1_PWM_CLK  1
#define  FTM2_PWM_CLK  1

/*-----------------------------------------------------------------
 *   PWMx_WORK_MODE的值与对应的工作模式如下
 *    0x09 :  edge-aligned low-true PWM
 *    0x0a : edge-aligned high-true PWM
 *    0x12 : center-aligned high-ture PWM
 *    0x11 : center-aligned low-true PWM
 *   FTM_SC_CPWMS_MASK  : Center-aligned PWM 
 -------------------------------------------------------------------*/
/*各模块工作方式定义*/
#define FTM0_PWM_MODE 0x0a
#define FTM1_PWM_MODE 0x0a
#define FTM2_PWM_MODE 0x0a

/**
 *    @brief 得到FTM模块的基指针
 *
 *    @param   module ：FTM模块号
 *
 *    @return  所选模块基地址
 *
 *    @note   
 */
static FTM_MemMapPtr get_ftmptr(ID module)
{
    FTM_MemMapPtr p;
    
    switch(FTM_MOD_SET(module))
	{
		case FTM0:
			p = FTM0_BASE_PTR;
			break;
		case FTM1:
			p = FTM1_BASE_PTR;
			break;
		case FTM2:
			p = FTM2_BASE_PTR;
			break;
		default:
		    return NULL;
	}
    
    return p;
}

/**
 *    @brief 得到PORT模块基地址
 *
 *    @param   port PORT号
 *
 *    @return  所选PORT模块基地址
 *
 *    @note   
 */
static PORT_MemMapPtr get_portptr(ID port)
{
    PORT_MemMapPtr p;
    
    switch (PORT_ID_SET(port))
    {
        case PTA:
            p = PORTA_BASE_PTR;
            break;
        case PTB:
            p = PORTB_BASE_PTR;
            break;
        case PTC:
            p = PORTC_BASE_PTR;
            break;
        case PTD:
            p = PORTD_BASE_PTR;
            break;
        default:
            return NULL;
    }
    
    return p;
}

/**
 *    @brief 使能所选引脚时钟，将其配置成PWM功能
 *
 *    @param   port_id： 所选引脚 
 */
static void port_init(uint16_t port_id)
{
	PORT_MemMapPtr portptr;
	ID port,pin;
	
	port    = PORT_NO_GET(port_id);
	pin     = PIN_NO_GET(port_id);
	portptr = get_portptr(port);
	SIM_SCGC5 |= (1 << (port + 9));
	
	if(port>=PORT_NO_GET(PTC))                           
		PORT_PCR_REG(portptr,pin) = PORT_PCR_MUX(4);
	else
		PORT_PCR_REG(portptr,pin) = PORT_PCR_MUX(3);
}

/**
 *    @brief   pwm0模块相关寄存器配置
 *
 *    @param   channel  pwm0所选的通道  
 */
static void pwm_mod0_set(ID channel)
{
	/*使能ftm0模块时钟*/
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
	
	/*选择时钟源，分频系数，以及计数器计数方式*/
	FTM_SC_REG(FTM0_BASE_PTR) = FTM_SC_CLKS(FTM0_PWM_CLK) | FTM_SC_PS(FTM0_PWM_PRESCALE) | ((FTM0_PWM_MODE & 0x10)<<1);
	
	/*设置计数器计数初值*/
	FTM_CNTIN_REG(FTM0_BASE_PTR) = CNTIN_VALUE;
	
	/*初始化计数器*/
	FTM_CNT_REG(FTM0_BASE_PTR) = FTM0_INIT_VALUE;
	
	/*设置计数器最大模值*/
	FTM_MOD_REG(FTM0_BASE_PTR) = FTM0_PWM_CYCLE;
	
	/*设置FTM模块的工作方式*/
	FTM_CnSC_REG(FTM0_BASE_PTR,channel) =((FTM0_PWM_MODE & 0x0f)<<2);
	
	/*设置初始化占空比*/
	FTM_CnV_REG(FTM0_BASE_PTR,channel) = PWM_INIT_VALUE;
}

/**
 *    @brief pwm1模块相关寄存器配置
 *
 *    @param   channel  pwm1所选的通道  
 */
static void pwm_mod1_set(ID channel)
{
	/*使能ftm0模块时钟*/
	SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
	
	/*选择时钟源，分频系数，以及计数器计数方式*/
	FTM_SC_REG(FTM1_BASE_PTR) = FTM_SC_CLKS(FTM1_PWM_CLK) | FTM_SC_PS(FTM1_PWM_PRESCALE) | ((FTM1_PWM_MODE & 0x10)<<1);
    
	/*设置计数器计数初值*/
	FTM_CNTIN_REG(FTM1_BASE_PTR) = CNTIN_VALUE;
	
	/*初始化计数器*/
	FTM_CNT_REG(FTM1_BASE_PTR) = FTM1_INIT_VALUE;
	
	/*设置计数器最大模值*/
	FTM_MOD_REG(FTM1_BASE_PTR) = FTM1_PWM_CYCLE;
	
	/*设置FTM模块的工作方式*/
	FTM_CnSC_REG(FTM1_BASE_PTR,channel) = ((FTM1_PWM_MODE & 0x0f)<<2);
	
	/*设置初始化占空比*/
	FTM_CnV_REG(FTM1_BASE_PTR,channel) = PWM_INIT_VALUE;
}

/**
 *    @brief pwm2模块相关寄存器配置
 *
 *    @param   channel  pwm2所选的通道  
 */
static void pwm_mod2_set(ID channel)
{
	/*使能ftm0模块时钟*/
	SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
	
	/*选择时钟源，分频系数，以及计数器计数方式*/
	FTM_SC_REG(FTM2_BASE_PTR) = FTM_SC_CLKS(FTM2_PWM_CLK) | FTM_SC_PS(FTM2_PWM_PRESCALE) | ((FTM2_PWM_MODE & 0x10)<<1); 
	
	/*设置计数器计数初值*/
	FTM_CNTIN_REG(FTM2_BASE_PTR) = CNTIN_VALUE;
	
	/*初始化计数器*/
	FTM_CNT_REG(FTM2_BASE_PTR) = FTM2_INIT_VALUE;
	
	/*设置计数器最大模值*/
	FTM_MOD_REG(FTM2_BASE_PTR) = FTM2_PWM_CYCLE;
	
	/*设置FTM模块的工作方式*/
	FTM_CnSC_REG(FTM2_BASE_PTR,channel) = ((FTM2_PWM_MODE & 0x0f)<<2);
	
	/*设置初始化占空比*/
	FTM_CnV_REG(FTM2_BASE_PTR,channel) = PWM_INIT_VALUE;
}

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
ER ftm_pwm_init(ID module, ID channel)
{   
	FTM_MemMapPtr ftmptr;
	
	ftmptr=get_ftmptr(module);
	
	switch(FTM_MOD_SET(module))
	{
		case FTM0:
			switch( FTM_CH_SET(module,channel) )
			{
				case FTM0_CH0:
					port_init(FTM0CH0_PIN);
					break;
				case FTM0_CH1:
					port_init(FTM0CH1_PIN);
					break;
			    case FTM0_CH2:
			    	port_init(FTM0CH2_PIN);
			    	break;
			    case FTM0_CH3:
			    	port_init(FTM0CH3_PIN);	    	
			    	break;
			    case FTM0_CH4:
			    	port_init(FTM0CH4_PIN);
			    	break;
			    case FTM0_CH5:
			    	port_init(FTM0CH5_PIN);			    	
			    	break;
			    case FTM0_CH6:
			    	port_init(FTM0CH6_PIN);			    	
			    	break;
			    case FTM0_CH7:
			    	port_init(FTM0CH7_PIN);			    	
			    	break;
			    default:
			    	return E_CHN;
			    	break;
			}
			pwm_mod0_set(channel);
			break;
			
		case FTM1:
			switch(FTM_CH_SET(module,channel))
			{
				case FTM1_CH0:
					port_init(FTM1CH0_PIN);
					break;
				case FTM1_CH1:
					port_init(FTM1CH1_PIN);
					break;
				default:
					return E_CHN;
			}
			pwm_mod1_set(channel);
			break;
			
		case FTM2:
			switch(FTM_CH_SET(module,channel))
			{
				case FTM2_CH0:
					port_init(FTM2CH0_PIN);
					break;
				case FTM2_CH1:
					port_init(FTM2CH1_PIN);
					break;
				default:
					return E_CHN;
			}
			pwm_mod2_set(channel);
			break;
			
		default:
			return E_MOD;
			break;
	}
	return E_OK;
}

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
ER ftm_pwm_output(ID module, ID channel, uint32_t duty_count)
{
	FTM_MemMapPtr ftmptr = get_ftmptr(module);
	
	if((module<0) || (module>2))
		return E_MOD;
	else if((module==0) && ((channel<0) || (channel>7)))
		return E_CHN;
	else if((module!=0)&&((channel!=0)&&(channel!=1))) 
		return E_CHN;
	
	FTM_CnV_REG(ftmptr,channel) = duty_count;
	
	return E_OK;
}
