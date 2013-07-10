/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_image.c
 *
 *        @brief    测试图像处理
 *
 *        @version  0.1
 *        @date     2012/4/16 19:33
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/16   create orignal file
 *  @0.2    Hu Chunxu   2012/5/7    测试SD卡速度最大100KB/s
 * =====================================================================================
 */
#include <stdio.h>

#include "ff.h"
#include "diskio.h"

#include "common.h"
#include "exception.h"
#include "sys_timer.h"
#include "sysinit.h"
#include "spi.h" 

#include "light.h"
#include "serial.h"
#include "sd.h" 
#include "image_process.h"


FIL    image_data;                                     /* File objects */
char  image_data_name[FILE_NAME_LENGHT]="a_image.txt";  /* File name */

int main(int argc, char **argv)
{   
    uint32_t buff_r;
    FRESULT res;
    uint32_t n = 0, j = 0;
    int32_t y_temp = -1;
    int temp = 0;
    uint32_t time[64];
    uint32_t time_temp[4];
    uint32_t time_start = 0;
    uint32_t time_end = 0;
    
    /* 模块初始化 */
    exc_init();                                          /* 中断初始化 */
    sys_timer_init();                                    /* 系统时钟初始化 */
    light_init();                                        /* LED灯初始化 */
    serial_initialize((intptr_t)(NULL));                 /* 初始化串口 */
    sd_init(&Fatfs);                                     /* 初始化SD卡，并创建文件 */
    sd_create_file(&image_data, image_data_name);        /* create a file */
    
    printf("\n Welcome to k60 software platform! \n");
    light_open(LIGHT4); 

    res = f_open(&image_data, "0:DATA.TXT", FA_OPEN_EXISTING | FA_READ);
    res = f_read(&image_data, buffer, sizeof(buffer), &buff_r);  
   
//////    for(n=0; n<64; n++)
//////    {
//////        for(j=0;j<4;j++)
//////        {    
//            sys_timer_read(&time_start);
            compress_image();
//            sys_timer_read(&time_end);     
//////
//////            time_temp[j] = time_start - time_end;         
//////
//////        }
//////        time[n] = (time_temp[0] +time_temp[1]+time_temp[2]+time_temp[3])/4;
//////    }
//    
    res = f_open(&image_data, "0:A_IMAGE.TXT", FA_OPEN_EXISTING | FA_WRITE);
//    /* 取出制表符 */
//    if (image_data.fs)
//    {
//        for (n = 0; n < ((12800*2) +100) ; n++)
//        {
//            if((buffer[n] == '0') || (buffer[n] == '1'))
//            f_printf(&image_data, "%c", buffer[n]);        
//        }
//    }
//    /* 写原始数据 */
////    if (image_data.fs)
////    {
////        for (n = 0; n < 12800 ; n++)
////        {
////            if(n%128 == 0)
////            {
////                y_temp ++;
////            }
////            
////            if(buffer[n]  == '0')
////            {
////                f_printf(&image_data, "%d\t", (n%128));
////                f_printf(&image_data, "%d\n", y_temp);      
////            }
////        }
////    }
    /* 写压缩后图像 */
//    if (image_data.fs)
//    {
//        for (n = gl_SRNum; n >0 ; n--)
//        {
//            f_printf(&image_data, "%d\t%d\n", 
//                    (int)StrRoadFind[n].CenterX, (int)StrRoadFind[n].CenterY);      
//        }
//    }
    for (n = 0; n <12800 ; n++)
    {
       buffer[n] = 0;   
    }
    for (n = gl_SRNum; n >0 ; n--)
    {
        if((int)StrRoadFind[n].Width<12)
        buffer[(int)StrRoadFind[n].CenterY * 128 + (int)StrRoadFind[n].CenterX] = 1;    
    }
    
    if (image_data.fs)
    {
        for (n = 12800; n >0 ; n--)
        {
            if(n%128 == 0)
            {
                f_printf(&image_data, "\n%d\t", (int)buffer[n]);      
            }
            else
            {
                f_printf(&image_data, "%d\t", (int)buffer[n]);      
            }
            
        }
    }

//    for (n = gl_SRNum; n > 0; n--)
//    {
//        printf("%d\t%d\n", (int) StrRoadFind[n].CenterX,
//                (int) StrRoadFind[n].CenterY);
//    }
//    printf("time cost is %d\n", (time_start - time_end)/100);

////    for(n=0;n<64;n++)
////    {
////        f_printf(&image_data, "%d\t%d\n", 
////                            n, time[n]);  
////    }
////
//    f_printf(&image_data, "COMPRESS OVER");
//    sys_timer_read(&time_start);
//    find_road();
//    sys_timer_read(&time_end);
    //printf("time cost is %d\n", (time_start - time_end)/100);
    
    sd_close_file(&image_data); /* 关闭文件 */
    
    while(1)
    {
        light_open(LIGHT6); 
    }
}
