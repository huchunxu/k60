/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     otsu.h
 *
 *        @brief    迭代法求自动阈值
 *
 *        @version  0.1
 *        @date     2012/12/29 21:29
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/12/29   create orignal file
 * =====================================================================================
 */
#ifndef ITERATION_H_
#define ITERATION_H_

#include "common.h"

int iteration(unsigned char *image, int rows, int cols, int x0, int y0, int dx, int dy);

#endif
