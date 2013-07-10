/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sysinit.h
 *
 *        @brief  
 *
 *        @version  0.1
 *        @date     2012/3/9 11:50:06
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2012/3/9    create orignal file
 * =====================================================================================
 */
#ifndef _SYSINIT_H_
#define _SYSINIT_H_

/*-----------------------------------------------------------
 * Header Files
 *----------------------------------------------------------*/
#include "common.h"
#include <stdint.h>
#include "wdog.h"


/*-----------------------------------------------------------
 * Macro Definitions
 *----------------------------------------------------------*/
#define PLL_48MHZ   0
#define PLL_50MHZ   1
#define PLL_96MHZ   2
#define PLL_100MHZ  3

#define CORE_CLK_48000    48000    /**< 单位 ：khz */
#define CORE_CLK_50000    50000
#define CORE_CLK_96000    96000
#define CORE_CLK_100000   100000

#define BUS_CLK_48000     48000    /**< 单位 ：khz */
#define BUS_CLK_50000     50000

#define XTAL_2MHZ   0
#define XTAL_4MHZ   1
#define XTAL_6MHZ   2
#define XTAL_8MHZ   3
#define XTAL_10MHZ  4
#define XTAL_12MHZ  5
#define XTAL_14MHZ  6
#define XTAL_16MHZ  7
#define XTAL_18MHZ  8
#define XTAL_20MHZ  9
#define XTAL_22MHZ  10
#define XTAL_24MHZ  11
#define XTAL_26MHZ  12
#define XTAL_28MHZ  13
#define XTAL_30MHZ  14
#define XTAL_32MHZ  15

/*-----------------------------------------------------------
 * Function Declarations
 *----------------------------------------------------------*/
extern void hardware_init_hook(void);

#endif  /* _SYSINIT_H */    
