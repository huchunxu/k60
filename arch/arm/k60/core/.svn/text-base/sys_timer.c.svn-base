/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sys_timer.c
 *
 *        @brief    
 *
 *        @version  0.1
 *        @date     2012/3/9 17:26:12
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2012/3/9    create orignal file
 * =====================================================================================
 */

#include "sys_timer.h"
#include "common.h"
#include "exception.h"
#include "decoder.h"

volatile uint32_t sys_timer_count;


/**
 * @brief cortex-m3/m4 system timer initialize
 */
void sys_timer_init(void) 
{
	uint32_t cyc;
	
	cyc = 1000000;               /* 10ms (100M核心时钟) */
	sys_timer_count = 0;

	/* stop system timer */
	SYST_CSR = 0;
	SYST_RVR = cyc;
	SYST_CVR = cyc;
	
	/* install exception handler */
	exc_install(INT_SysTick,sys_timer_handler);
	exc_set_pri(INT_SysTick, 0);

	/* enable system timer, use FCLK（内核时钟）,enable int */
	//SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_CLKSOURCE_MASK;
	SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_TICKINT_MASK;
}

/**
 * @brief system timer terminate
 */
void sys_timer_terminate(void)
{
	SYST_CSR = 0x0;
}


/**
 * @brief system timer stop
 */
void sys_timer_stop(void)
{
	SYST_CSR  &= ~SysTick_CSR_ENABLE_MASK;
}



/**
 * @brief system timer start
 */
void sys_timer_start(void)
{
	SYST_CSR |= SysTick_CSR_ENABLE_MASK;
}

/**
 * @brief system timer read
 */
void sys_timer_read(uint32_t *ptime)
{
    *ptime = SYST_CVR;
}

/**
 * @brief system timer interrup handler
 */
void sys_timer_handler(void)
{
	volatile uint32_t temp;

	/* clear COUNTFLAG */
	temp = 	SYST_CSR;

	calculateCurSpeed();

	sys_timer_count++;
}
