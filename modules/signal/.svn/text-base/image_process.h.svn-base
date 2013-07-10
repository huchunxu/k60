/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     image_process.h
 *
 *        @brief    图像处理头文件
 *
 *        @version  0.1
 *        @date     2012/5/15  19：58
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/15    create orignal file
 * =====================================================================================
 */
#ifndef IMAGE_PROCESS_H_
#define IMAGE_PROCESS_H_

#include "common.h"

#define   STR_ROAD_MAX_NUM  300   
#define   END_LINE          80
#define   START_LINE        10
#define   CONTINUE_VALUE    5
#define   CONTINUE_LINE     10
#define   MAX_LINE          10
#define   SKIP_LINE         3
#define   MAX_K             5
#define   MAX_Y             100
#define   MAX_X             128
#define   MAX_LIN_STR_Y     60
#define   MAX_LINE_POINT    200
#define   K_STEP_Y          9
#define   K_STEP_E          5
#define   IMAGECENTER       60

typedef struct
{
      uint8_t CenterX;
      uint8_t CenterY;
}image_road;

typedef struct 
{
      unsigned char CenterX;
      unsigned char Width;
      unsigned char CenterY;
}image_road_startline;

extern volatile uint8_t gl_road[MAX_Y];         /*最后找到的路*/
extern volatile uint8_t gl_roadStartY;          /*路的起点*/
extern volatile uint8_t gl_roadEndY;            /*路的终点*/
extern volatile uint32_t gl_motherRoadLen;      /*母路的长度*/
extern volatile image_road_startline StrRoadFind[STR_ROAD_MAX_NUM+1];
extern volatile int gl_SRNum;   /*  active point */
extern  char_t buffer[12800];        /* file copy buffer, 1k bytes */
/**
 *    @brief   压缩图像
 */
void compress_image(void);

/**
 *    @brief   美化路径
 */
void BeautifyRoad(void);

/**
 *    @brief   找路
 */
ER find_road(void);


#endif /* IMAGE_PROCESS_H_ */
