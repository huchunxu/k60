/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     sram_ntshell.h
 *
 *        @brief    sram ntshell cmd header
 *
 *        @version  0.1
 *        @date     2012/4/15 15:10
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/15   create orignal file
 * =====================================================================================
 */


#ifndef SRAM_NTSHELL_H_
#define SRAM_NTSHELL_H_

#include "common.h"


/**
 *    @brief   mww命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void mww_initialize(intptr_t exinf);

/**
 *    @brief   mww命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void mdw_initialize(intptr_t exinf);


#endif /* SRAM_NTSHELL_H_ */
