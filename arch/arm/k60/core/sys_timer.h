/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sys_timer.c
 *
 *        @brief    system timer driver head file
 *
 *        @version  0.1
 *        @date     2012/3/9 17:26:12
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2012/3/9    create orignal file
 * =====================================================================================
 */
#ifndef SYS_TIMER_H
#define SYS_TIMER_H

#include "common.h"
extern  volatile uint32_t sys_timer_count;

extern void sys_timer_init(void);
extern void sys_timer_terminate(void);
extern void sys_timer_stop(void);
extern void sys_timer_start(void);
extern void sys_timer_handler(void);
extern void sys_timer_read(uint32_t *ptime);

#endif /* SYS_TIMER_H */
