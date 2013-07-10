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
#ifndef __WDOG_H__
#define __WDOG_H__

extern void wdog_disable(void);
extern void wdog_enable(void);
extern void wdog_lock(void);
extern void wdog_unlock(void);

#endif /* __WDOG_H__*/
