/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     exception.h
 *
 *        @brief    exception management functions
 *
 *        @version  0.1
 *        @date     2011/12/30 16:00:41
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2011/12/30  create orignal file
 * =====================================================================================
 */

#ifndef  VECTOR_INC
#define  VECTOR_INC

#include "common.h"


#define  ARM_INTERRUPT_LEVEL_BITS  4  //中断等级

/**
 * @brief set faultmask
 *
 * @return 
 */
Inline void set_faultmask(void)
{
	Asm ("cpsid f":::"memory");
}


/**
 * @brief clear faultmask
 *
 * @return 
 */
Inline void clear_faultmask(void)
{
	Asm ("cpsie f":::"memory");
}



/**
 * @brief set interrupt priority mask
 *
 * @return 
 */
Inline void
set_primask(void){
	Asm("cpsid i":::"memory");
}


/**
 * @brief clear interrupt priority mask
 *
 * @return 
 */
Inline void
clear_primask(void){
	Asm("cpsie i":::"memory");
}


/**
 * @brief set base priority
 *
 * @param val base priority
 *
 * @return 
 */
Inline void
set_basepri(uint32_t val){
	Asm("msr BASEPRI, %0" : : "r"(val) : "memory");
}


/**
 * @brief get base priority
 *
 * @return base priority
 */
Inline uint32_t
get_basepri(void){
	uint32_t val;
	Asm("mrs  %0, BASEPRI" : "=r"(val));
	return(val);
}


extern void exc_install(uint32_t excno, FP exchdr);
extern void exc_set_pri(uint32_t excno, uint8_t pri);
extern void exc_enable(uint32_t excno);
extern void exc_disable(uint32_t excno);
extern void exc_set_vector(void * vector);
extern void exc_init(void);

#endif   /* ----- #ifndef VECTOR_INC  ----- */


