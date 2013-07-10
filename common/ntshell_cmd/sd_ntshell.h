/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     sd_ntshell.h
 *
 *        @brief    sd ntshell cmd header
 *
 *        @version  0.1
 *        @date     2012/5/6 20:51
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/6   create orignal file
 * =====================================================================================
 */

#ifndef SD_NTSHELL_H_
#define SD_NTSHELL_H_

#include "common.h"

/**
 *    @brief   sd命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void sd_cmd_initialize(intptr_t exinf);


#endif /* SD_NTSHELL_H_ */
