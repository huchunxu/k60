/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     common.h
 *
 *        @brief    common functions for k60
 *
 *        @version  0.1
 *        @date     2011/12/30 16:39:45
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2011/12/30  create orignal file
 * =====================================================================================
 */

#ifndef  COMMON_H
#define  COMMON_H

#include "MK60N512VMD100.h"   /* 寄存器映像头文件 */
#include "t_stddef.h"
#include "t_soudef.h"
#include "t_devdef.h"

#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    /**< 设置寄存器中某一位为1 */
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  /**< 设置寄存器中某一位为0 */
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  /**< 得到寄存器中某一位状态 */

#define EnableInterrupts  asm(" CPSIE i");    /**< 开总中断 */
#define DisableInterrupts asm(" CPSID i");    /**< 关总中断 */


#define Inline static __inline__
#define Asm asm __volatile__

/**
 * @brief set control register
 *
 * @param val value of control register
 *
 * @return 
 */
//Inline void
//set_control(uint32_t val){
//	Asm("msr control, %0 \n"
//		" isb"
//		: : "r"(val) : "memory");
//}



/**
 * @brief get the value of control register
 *
 * @return value of control register
 */
//Inline uint32_t
//get_control(void){
//	uint32_t val;
//	Asm("mrs  %0, CONTROL" : "=r"(val));
//	return(val);
//}



/**
 * @brief get current value of ipsr
 *
 * @return value of ipsr
 */
//Inline uint32_t
//get_ipsr(void)
//{
//    uint32_t sr;
//    Asm("mrs  %0, ipsr" : "=r"(sr));
//    return(sr);
//}

extern void stop(void);
extern void wait(void);
#endif   /* ----- #ifndef COMMON_H  ----- */


