/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     gpio.h
 *
 *        @brief    gpio header file
 *
 *        @version  0.1
 *        @date     2012/2/14 15:35:40
 *
 *        @author   Hu Chunxu, hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/2/14   create orignal file
 * =====================================================================================
 */

#ifndef _GPIO_H
#define _GPIO_H

/**
 * 头文件包含
 */
#include "common.h"
	
/**
 * 宏定义
 */
#define PORT_MAX_NUM 5  

/**
 * 函数声明
 */
PORT_MemMapPtr gpio_get_port_addr (PORT port);
GPIO_MemMapPtr gpio_get_pt_addr(PORT port);
ER             gpio_init(PORT port, PIN pin, uint8_t dir, uint8_t state);
bool_t         gpio_get(PORT port, PIN pin);
void           gpio_set(PORT port, PIN pin, uint8_t state);
void           gpio_reverse(PORT port, PIN pin);

#endif
