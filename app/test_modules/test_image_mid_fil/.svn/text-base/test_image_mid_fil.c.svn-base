/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_image_mid_fil.c
 *
 *        @brief    测试图像处理
 *
 *        @version  0.1
 *        @date     2012/7/23 16:46
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/7/23   create orignal file
 * =====================================================================================
 */
#include "mid_fil.h"

int main(int argc, char **argv)
{
    int i;
    
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[0][i] = i;
    }
    for(i=9;i>=0;i--)
    {
        image_mid_fil_val[1][i] = i;
    }
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[2][i] = i*2;
    }
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[3][i] = 3;
    }
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[4][i] = 2;
    }
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[5][i] = i;
    }
    for(i=9;i>=0;i--)
    {
        image_mid_fil_val[6][i] = i;
    }
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[7][i] = i+2;
    }
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[8][i] = i;
    }
    for(i=0;i<10;i++)
    {
        image_mid_fil_val[9][i] = 1;
    }

    mid_fil();
}
