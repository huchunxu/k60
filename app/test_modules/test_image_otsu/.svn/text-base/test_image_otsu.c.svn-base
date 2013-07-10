/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_image_otsu.c
 *
 *        @brief    测试图像动态阈值（大津法）
 *
 *        @version  0.1
 *        @date     2012/7/25 09:48
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/7/25   create orignal file
 * =====================================================================================
 */
#include "otsu.h"

int main(int argc, char **argv)
{
    int thresholdValue = 1;
    unsigned char image_value[51] = 
    {88,96 , 88 , 80 , 64 , 40 , 8  , 0 ,  0  , 0  , 16 , 48 , 72,  88 , 96 , 96  ,96,
     96,88 , 96  ,88  ,88  ,80 , 64 , 32 , 0  , 0  , 0  , 0  , 24 , 56 , 80  ,88  ,96,
     96 , 96 , 96 , 88 , 96 , 88,  88,  80,  64,  24,  0 ,  0 ,  0 ,  0 ,  32,  64,  88};

    thresholdValue = otsu(image_value,3,17,0,0,17,3);
    
    while(1);
}
