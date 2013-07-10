/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     target_libc.c
 *
 *        @brief    libc库依赖
 *
 *        @version  0.1
 *        @date     2011/3/21 21:32:45
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2011/3/21   create orignal file
 * =====================================================================================
 */

#include <t_stddef.h>
#include "serial.h"
#include "target_serial.h"
#include "target_libc.h"

/**
 *    @brief   printf依赖读函数
 *
 *    @param   file
 *    @param   ptr   缓存指针
 *    @param   len   数据长度
 *
 *    @return  res   读状态
 */
int _read(int file ,char *ptr, int len)
{
	int res = 0;

	if (file < 3)
	{
		/* read from serial port */
		res = serial_rea_dat(SIOPORT, (char_t *)ptr, (uint_t)len);
	}
	return res;
}

/**
 *    @brief   printf依赖写函数
 *
 *    @param   file
 *    @param   ptr   缓存指针
 *    @param   len   数据长度
 *
 *    @return  res   写状态
 */
int _write(int file, char *ptr, int len)
{

	int res = 0;

	if (file < 3)
	{
		res = serial_wri_dat(SIOPORT, (const char_t *)ptr, (uint_t)len);
	}
	return res;
}

