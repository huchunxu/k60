/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     mid_fil.h
 *
 *        @brief    图像中值滤波函数头文件
 *
 *        @version  0.1
 *        @date     2012/7/23 16:46
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/7/23   create orignal file
 * =====================================================================================
 */
#ifndef MID_FIL_H_
#define MID_FIL_H_

#include "common.h"

#define  WINDOW_SIZE   3     /* 窗的大小 */
#define  IMAGE_HEIGHT  100   /* 图像高度 */
#define  IMAGE_WIDTH   128   /* 图像宽度 */

extern unsigned char image_mid_fil_val[IMAGE_HEIGHT][IMAGE_WIDTH];

void mid_fil(void);
void bubble_sort(unsigned char *data, int data_length);

#endif
