/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     mid_fil.c
 *
 *        @brief    图像中值滤波函数
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

/* 图像灰度值 */
unsigned char image_mid_fil_val[IMAGE_HEIGHT][IMAGE_WIDTH];

/**
 *    @brief   图像中值滤波
 */
void mid_fil(void)
{
	int i, j, k, l, m;
	unsigned char image_temp[WINDOW_SIZE * WINDOW_SIZE];
	int temp = 0;

	for(i=(WINDOW_SIZE-1)/2; i<(IMAGE_HEIGHT-(WINDOW_SIZE-1)/2); i++)
	{
	    for(j=(WINDOW_SIZE-1)/2; j<(IMAGE_WIDTH-(WINDOW_SIZE-1)/2); j++)
		{
			/* 将窗内的灰度值赋予排序的缓存 */
			k = 0;
			for(l=0;l<WINDOW_SIZE;l++)
			{
				for(m=0;m<WINDOW_SIZE;m++)
				{
					image_temp[k] = image_mid_fil_val[i-(WINDOW_SIZE-1)/2+l][j-(WINDOW_SIZE-1)/2+m];
					k++;
				}
			}

			/* 冒泡排序 */
			bubble_sort(image_temp, WINDOW_SIZE*WINDOW_SIZE);

			/* 赋予中值 */
			temp = WINDOW_SIZE*WINDOW_SIZE/2;
			image_mid_fil_val[i][j] = image_temp[temp];
		}
	}
}

/**
 *    @brief   冒泡排序
 *
 *    @param   data         需要排序的数据
 *    @param   data_length  数据的长度
 *
 *    @return  无
 */
void bubble_sort(unsigned char *data, int data_length)
{
	unsigned char temp = 0;
	int i, j;

    for(i=0;i<data_length-1;i++)
    {
        for(j=0;j<data_length-i-1;j++) 
        {
            if(data[j+1]<data[j])
            {
                temp=data[j];
                data[j]=data[j+1];
                data[j+1]=temp;  
            }
        }
    }
}
