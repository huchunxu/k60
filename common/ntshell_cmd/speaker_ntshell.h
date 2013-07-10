/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     speaker_ntshell.c
 *
 *        @brief    speaker ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/4/17 18:26
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/17   create orignal file
 * =====================================================================================
 */

#ifndef SPEAKER_NTSHELL_H_
#define SPEAKER_NTSHELL_H_

#include "common.h"

/**
 *    @brief   speaker命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void speaker_cmd_initialize(intptr_t exinf);

#endif /* SPEAKER_NTSHELL_H_ */
