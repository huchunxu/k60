#include <string.h>
#include <stdio.h>
#include "iteration.h"

/**
 *    @brief   算法对输入的灰度图像的直方图进行分析，将直方图分成两个部分，
 *             使得两部分之间的平均阈值小于一个阈值,划分点就是求得的阈值
 *
 *    @param   *image     buffer for image 
 *    @param   rows       size of image
 *    @param   cols       size of image
 *    @param   x0, y0     region of vector used for computing threshold 
 *    @param   dx, dy     region of vector used for computing threshold 
 *
 *    @return  thresholdValue  threshold
 */
int iteration(unsigned char *image, int rows, int cols, int x0, int y0, int dx, int dy)
{
    unsigned char *np;      /* 图像指针 */
    int last_threshold = 0; /* 上一次的阈值 */
    int threshold = 0;     /* 当前阈值 */
    int divide_line = 128; /* 阈值分界线 */
    int ihist[256];         /* 图像直方图，256个点 */
    int left_threshold_total = 0;  /* 分界线左侧阈值和 */
    int right_threshold_total = 0; /* 分界线右侧阈值和 */
    int left_point_total = 0;  /* 左侧图像点数 */
    int right_point_total = 0;  /* 右侧图像点数 */
    int iteration_times = 0;  /* 迭代次数 */

    int i, j;            /* various counters */
    int gmin, gmax;

    /* 对直方图置零... */
    memset(ihist, 0, sizeof(ihist));

    gmin = 255;
    gmax = 0;
    /* 生成直方图 */
    for (i = y0 + 1; i < y0 + dy - 1; i++)
    {
        np = &image[i*cols+x0+1];
        for (j = x0 + 1; j < x0 + dx - 1; j++)
        {
            ihist[*np]++;
            if (*np > gmax)
                gmax = *np;
            if (*np < gmin)
                gmin = *np;
            np++; /* next pixel */
        }
    }

    while(1)
    {
        iteration_times++;
        /* 计算分界线左侧平均阈值 */
        for(i=1;i<divide_line;i++)
        {
            left_threshold_total += ihist[i] * i; 
            left_point_total     += ihist[i];
        }

        /* 计算分界线右侧平均阈值 */
        for(i=divide_line;i<256;i++)
        {
            right_threshold_total += ihist[i] * i; 
            right_point_total     += ihist[i];
        }

        last_threshold = threshold;
        threshold = (left_threshold_total / left_point_total + 
                right_threshold_total / right_point_total) >> 1;
        divide_line = threshold;

        if(iteration_times > 1)
        {
            if(((last_threshold - threshold) < 5) && ((last_threshold - threshold) > -5))
            {
                break;
            }
        }
    }

    return threshold;
}
