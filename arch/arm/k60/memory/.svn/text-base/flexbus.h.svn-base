/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     flexbus.h
 *
 *        @brief    SRAM initial
 *
 *        @version  0.1
 *        @date     2012/2/15 15:46:40
 *
 *        @author  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/2/15   create orignal file
 * =====================================================================================
 */

#ifndef _FLEXBUS_H
#define _FLEXBUS_H

#include "common.h"


#define MRAM_START_ADDRESS	      (*(vuint16_t*)(0x60000000))
#define MRAM_MAX_SHIFT_ADDRESS    0x3fffe

/**
 *    @brief   FlexBus初始化
 *    @note   Configure the FlexBus Registers for 16-bit port size 
 *            with separate address and data using chip select 0
 *            Configure the pins needed to FlexBus Function (Alt 5 or 6)
 */
void flexbus_init(void);


#endif
