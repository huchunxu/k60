/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     common.c
 *
 *        @brief    common functions for k60
 *
 *        @version  0.1
 *        @date     2011/12/30 16:39:45
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2011/12/30  create orignal file
 * =====================================================================================
 */
#include "common.h"

/**
 * @brief set the cpu into stop mode
 */
void stop (void)
{
	/* set SLEEPPDEEP */
	SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK;	
	Asm("WFI");
}


/**
 * @brief set the cpu into wait mode
 */
void wait (void)
{
	/* clear SLEEPDEEP */
	SCB_SCR &= ~SCB_SCR_SLEEPDEEP_MASK;	
	Asm("WFI");
}
