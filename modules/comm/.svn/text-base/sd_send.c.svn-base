/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sd_send.c
 *
 *        @brief    SD发送数据
 *
 *        @version  0.1
 *        @date     2011/2/6 16:23
 *
 *        @author   Sun Jiajiang
 *                  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Sun Jiajiang   2011/2/6     create orignal file
 *  @0.2    Hu Chunxu      2012/5/6     移植到K60   
 * =====================================================================================
 */
#include "sd_send.h"
#include "sd_rw.h"
/*  global parameter declare  */
typedef struct
{
    unsigned char sign;
    unsigned char data[5];
    unsigned char tab[2];
}SINGLE_DATA;

typedef struct
{
    unsigned char data[3];
    unsigned char tab;
}ROAD_DATA;

typedef struct
{
    unsigned char pointYlow;
    unsigned char pointYhigh;
    unsigned char pointXlow;
    unsigned char pointXhigh;
}COMPRESS_POINT;
#define FIRST_SECTOR                 520//100//300//400//450//500//550//600//657
/*128M   520*/
/*256M   621*/
/*2G     641*/
volatile unsigned long gl_sector = 520;
const unsigned char CRLF_DATA[8] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0d, 0x0a};
const unsigned char CRLF_COMPRESS[2] = {0x0d, 0x0a};
static unsigned char s_dataBuffer[64][8];
static unsigned int  s_dataBufferCount = 0;
static SINGLE_DATA *p_buffer = (SINGLE_DATA *)(&s_dataBuffer[0][0]);

/**
 *    @brief   SD卡发送数据
 * 
 *    @param   data   发送的数据
 */
void SD_SendData(int data)
{
    unsigned char dataString[8] = {0};
    int dataTemp = 0;
    //int retry = 0;
    unsigned char response = 0;
    
    dataTemp = data;
    s_dataBufferCount++;
    if(s_dataBufferCount>64)
    {
        s_dataBufferCount = 1;
        
        if(gl_sector < FIRST_SECTOR)
        {
            gl_sector = FIRST_SECTOR;
        }
        response = SD_WriteSignleBlock(gl_sector, &s_dataBuffer[0][0]);
        //if((response!=0) && (retry < 1))
        //{
        //    response = SD_WriteSignleBlock(gl_sector, &s_dataBuffer[0][0]);
        //    retry++;
        //}
        p_buffer = (SINGLE_DATA *)(&s_dataBuffer[0][0]);
        if(response == 0)
        {
            gl_sector++;
        }
    }
    if(dataTemp != CRLF)
    {
        Convert(dataTemp, dataString);
        Strcpy(p_buffer, dataString, 8);
        p_buffer++;
    }
    else
    {
        Strcpy(p_buffer, (void *)CRLF_DATA, 8);
        p_buffer++;
    }
}

/**
 *    @brief   SD卡发送数据
 * 
 *    @param   dataTemp     发送的数据
 *    @param   dataString   位置指针
 */
void Convert(int dataTemp, unsigned char *dataString)
{
    int valueTemp = 0;
    int bufferNum = 0;
    int divisor = 10000;
    unsigned char *p_dataString = NULL;
    
    valueTemp = dataTemp;
    p_dataString = dataString;
    if(valueTemp >= 0)
    {
        p_dataString[0] = 0x20;
        bufferNum++;
    }
    else
    {
        p_dataString[0] = '-';
        valueTemp = 0 - valueTemp;
        bufferNum++;
    }
    p_dataString++;
    while(((valueTemp/divisor) == 0) && (valueTemp != 0))
    {
        divisor = divisor / 10;
    }
    while((divisor > 1) && (dataTemp != 0))
    {
        *p_dataString = (valueTemp/divisor) + '0';
        bufferNum++;
        p_dataString++;
        valueTemp -= (valueTemp/divisor) * divisor;
        divisor = divisor / 10;
    }
    *p_dataString = (valueTemp%10) + '0';
    bufferNum++;
    
    while(bufferNum<7)
    {
        p_dataString++;
        *p_dataString = 0x20;
        bufferNum++;
    }
    p_dataString++;
    *p_dataString = 0x09;
}

/**
 *    @brief   SD卡发送数据
 * 
 *    @param   dataTemp     发送的数据
 *    @param   dataString   位置指针
 */
void ConvertRoad(int dataTemp, unsigned char *dataString)
{
    int valueTemp = 0;
    int bufferNum = 0;
    int divisor = 100;
    unsigned char *p_roadString = NULL;
    
    valueTemp = dataTemp;
    p_roadString = dataString;
    
    while(bufferNum < 3)
    {
        *p_roadString = (valueTemp/divisor) + '0';
        bufferNum++;
        p_roadString++;
        valueTemp -= (valueTemp/divisor) * divisor;
        divisor = divisor / 10;
    }
    *p_roadString = 0x20;
}

/**
 *    @brief   字符串复制
 * 
 *    @param   A        目的字符串
 *    @param   B        源字符串
 *    @param   length   长度
 */
void Strcpy(void *A, void *B, int length)
{
    int i = 0;
    unsigned char *dest = NULL, *source = NULL;
    
    dest   = (unsigned char *)A;
    source = (unsigned char *)B;
    
    for(i=0; i<length; i++)
    {
        *dest = *source;
        dest++;
        source++;
    }
}
