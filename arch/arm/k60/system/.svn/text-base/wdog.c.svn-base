/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     wdog.c
 *
 *        @brief    watchdog driver
 *
 *        @version  0.1
 *        @date     2012/3/9 19:24:47
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2012/3/9    create orignal file
 * =====================================================================================
 */

#include "common.h"
#include "wdog.h"


/**
 * @brief watchdog disable
 */
void wdog_disable(void)
{
	wdog_unlock();
	WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}


void wdog_enable(void)
{

}


void wdog_lock(void)
{

}

/**
 * @brief watchdog enable
 */
void wdog_unlock(void)
{
	/* 注意: 不要单步调试此程序!!! ，否则会引起CPU复位*/
	/* 写解锁寄存器 */
	WDOG_UNLOCK = 0xC520;	
	/* 完成解锁 */
 	WDOG_UNLOCK = 0xD928;	
	/* 开总中断 */
}
