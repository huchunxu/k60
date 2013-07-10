/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     gpio.c
 *
 *        @brief    gpio驱动函数
 *
 *        @version  0.1
 *        @date     2012/2/14 15:35:40
 *
 *        @author   Hu Chunxu, hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/2/14   create orignal file
 * =====================================================================================
 */
#include "gpio.h"
#include "common.h"

/**
 *    @brief   获得端口地址
 *
 *    @param   port 端口号
 *
 *    @return  端口号对应的端口寄存器组指针
 *
 *    @note    将端口号转换成端口寄存器组指针。内部调用。
 */
PORT_MemMapPtr gpio_get_port_addr (PORT port)
{
	PORT_MemMapPtr p;
    
    switch(PORT_ID_SET(port))
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
		case PTE:
			p = PORTE_BASE_PTR;
			break;
		default:
			return NULL; /* 输入参数无效返回 */
    }
    
    return p;
}


/**
 *    @brief   获得端口地址
 *
 *    @param   port 端口号
 *
 *    @return  端口号对应的端口寄存器组指针
 *
 *    @note    将端口号转换成端口寄存器组指针。内部调用。
 */
GPIO_MemMapPtr gpio_get_pt_addr(PORT port)
{
	GPIO_MemMapPtr p;
    
    switch(PORT_ID_SET(port))
    {
		case PTA:
			p = PTA_BASE_PTR;
			break;
		case PTB:
			p = PTB_BASE_PTR;
			break;
		case PTC:
			p = PTC_BASE_PTR;
			break;
		case PTD:
			p = PTD_BASE_PTR;
			break;
		case PTE:
			p = PTE_BASE_PTR;
			break;
		default:
			return NULL;  /* 输入参数无效返回 */
    }
    
    return p;
}

/**
 *    @brief   io口初始化
 *
 *    @param   port  端口号。由宏定义。
 *    @param   pin   引脚号。0～31。
 *    @param   dir   引脚方向。 1=输出，0=输入。
 *    @param   state 引脚初始状态。1=高电平，0=低电平
 *
 *    @return  0    成功
 *    @return  其他  异常
 *
 *    @note    初始化端口作为GPIO引脚的功能。
 */
ER gpio_init(PORT port, PIN pin, uint8_t dir, uint8_t state)
{
    /* 将GPIO端口号转换成端口寄存器组指针 */
    /* enable clock */
	GPIO_MemMapPtr pt = gpio_get_pt_addr(port);
    PORT_MemMapPtr p  = gpio_get_port_addr(port);
    
    if (!p) return E_INIT;  /* 初始化失败，参数错误 */
     
    /* 设定通用端口引脚控制寄存器的值，设定为GPIO功能 */
    PORT_PCR_REG(p, pin) = (0|PORT_PCR_MUX(1));

    if(dir == OUT_PUT) /* 若引脚被定义为输出 */
    {
        GPIO_PDDR_REG(pt) |= (1<<pin);
    	 
    	/* 设定引脚初始化状态 */
        if(state == HIGH_POWER)
		    BSET(pin, GPIO_PDOR_REG(pt));
        else
        	BCLR(pin, GPIO_PDOR_REG(pt));
    }
    else /* 若引脚被定义为输入 */
    {
    	BCLR(pin, GPIO_PDDR_REG(pt));
    }

    return E_OK;  /* 成功返回 */
}

/**
 *    @brief   获取指定引脚状态
 *
 *    @param   port  端口号。由宏定义。
 *    @param   pin   引脚号。0～31。
 *
 *    @return  0    低电平
 *    @return  1    高电平
 */
bool_t gpio_get(PORT port, PIN pin)
{
    /* 将GPIO端口号转换成端口寄存器组指针 */
	GPIO_MemMapPtr pt = gpio_get_pt_addr(port);
    
    /* 查看引脚状态 */
    if (BGET(pin, GPIO_PDIR_REG(pt)) == 0)
	{
        return LOW_POWER;  /* 低电平 */
    }
    else
    {
        return HIGH_POWER;  /* 高电平 */
    }
}

/**
 *    @brief   设置指定引脚状态
 *
 *    @param   port  端口号。由宏定义。
 *    @param   pin   引脚号。0～31。
 *    @param   state 引脚初始状态。1=高电平，0=低电平
 *
 *    @return  无
 */
void gpio_set(PORT port, PIN pin, uint8_t state)
{
    /* 将GPIO端口号转换成端口寄存器组指针 */
    GPIO_MemMapPtr pt = gpio_get_pt_addr(port);
	  
	  if (state == LOW_POWER) /* 控制为低电平 */
	      BCLR(pin, GPIO_PDOR_REG(pt));
	  else            /* 控制为高电平 */
	      BSET(pin, GPIO_PDOR_REG(pt));
}

/**
 *    @brief   反转指定引脚状态
 *
 *    @param   port  端口号。由宏定义。
 *    @param   pin   引脚号。0～31。
 *
 *    @return  无
 */
void gpio_reverse(PORT port, PIN pin)
{
    /* 将GPIO端口号转换成端口寄存器组指针 */
    GPIO_MemMapPtr pt = gpio_get_pt_addr(port);
	  
    BSET(pin, GPIO_PTOR_REG(pt));
}
