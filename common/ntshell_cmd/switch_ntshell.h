/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     switch_ntshell.h
 *
 *        @brief    switch ntshell cmd header
 *
 *        @version  0.1
 *        @date     2012/4/16 22:10
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/16   create orignal file
 * =====================================================================================
 */

#ifndef SWITCH_NTSHELL_H_
#define SWITCH_NTSHELL_H_

#include "common.h"

/**
 *    @brief   switch命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void switch_cmd_initialize(intptr_t exinf);

#endif /* SWITCH_NTSHELL_H_ */
