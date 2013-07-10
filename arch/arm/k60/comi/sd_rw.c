/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sd_rw.c
 *
 *        @brief    SD卡直接读写的驱动函数
 *
 *        @version  0.1
 *        @date     2011/2/6 16:23
 *
 *        @author   Sun Jiajiang
 *                  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Sun Jiajiang   2011/2/6     create orignal file
 *  @0.2    Hu Chunxu      2012/7/2     移植到K60   
 * =====================================================================================
 */
#include "sd_rw.h"
#include "spi.h"
#include "sd.h"

/**
 *    @brief   使用SPI向SD卡发送接受数据
 * 
 *    @param   writeChar   发送的命令
 *    
 *    @return  rcv_data  SD卡返回的信息 
 */
unsigned char ReadWrite_Byte(unsigned char writeChar)
{
    uint8_t rcv_data = 0;
    
    spi_snd(SPI_NO_GET(SD_SPI_NO), &writeChar, 1);
    spi_rcv(SPI_NO_GET(SD_SPI_NO), &rcv_data);
    
    return (BYTE)rcv_data;
}

/**
 *    @brief   使用SPI向SD卡发送命令
 * 
 *    @param   cmd   发送的命令
 *    @param   arg   命令参数
 *    
 *    @return  response  SD卡返回的信息 
 */
unsigned char SD_SPI_SendCommand(unsigned char cmd, unsigned long arg)
{
    unsigned char response = 0;
    unsigned char retry = 0;
    
    
    (void)ReadWrite_Byte(0xff);
    
    SD_SPI_SELECT();
    
    (void)ReadWrite_Byte(cmd | 0x40);
    (void)ReadWrite_Byte((unsigned char)(arg >> 24));
    (void)ReadWrite_Byte((unsigned char)(arg >> 16));
    (void)ReadWrite_Byte((unsigned char)(arg >> 8));
    (void)ReadWrite_Byte((unsigned char)arg);
    //(void)ReadWrite_Byte((cmd == CMD_GO_IDLE_STATE) ? 0x95 : 0xff);
    if((cmd == CMD_GO_IDLE_STATE) || (cmd == CMD_SET_BLOCKLEN))
    {
        (void)ReadWrite_Byte(0x95);
    }
    else
    {
        (void)ReadWrite_Byte(0xff);
    }
    
    retry = 200;
    do
    {
        response = ReadWrite_Byte(0xff);
        retry--;
    }while( ((response&0x80)!=0) && (retry > 0));

    SD_SPI_DESELECT();
    
    return response;
}

/**
 *    @brief   使用SPI向SD卡发送命令
 * 
 *    @param   cmd   发送的命令
 *    @param   arg   命令参数
 *    @param   crc   校验位
 *    
 *    @return  response  SD卡返回的信息 
 */
unsigned char SD_SPI_SendCommand_NoDeassert(unsigned char cmd, unsigned long arg, char crc)
{
    unsigned char response = 0;
    unsigned char retry = 0;
    
    
    (void)ReadWrite_Byte(0xff);
    
    SD_SPI_SELECT();
    
    (void)ReadWrite_Byte(cmd | 0x40);
    (void)ReadWrite_Byte((unsigned char)(arg >> 24));
    (void)ReadWrite_Byte((unsigned char)(arg >> 16));
    (void)ReadWrite_Byte((unsigned char)(arg >> 8));
    (void)ReadWrite_Byte((unsigned char)arg);
    (void)ReadWrite_Byte(crc);
    
    
    retry = 200;
    do
    {
        response = ReadWrite_Byte(0xff);
        retry--;
    }while( ((response&0x80)!=0) && (retry > 0));

    return response;
}

/**
 *    @brief   读取SD卡一个扇区
 * 
 *    @param   sector   扇区号
 *    @param   buffer   缓存数据
 *    
 *    @return  
 */
unsigned char SD_ReadSingleBlock(unsigned long sector, unsigned char *buffer)
{
    unsigned char response = 0;
    unsigned int i = 0;
    unsigned long retry = 0;
    
    response = SD_SPI_SendCommand(CMD_READ_SINGLE_BLOCK, sector<<9);
    
    if (response != 0x00)
    {
        return response;
    }
    
    SD_SPI_SELECT();
    
    while (0xfe != ReadWrite_Byte(0xff))
    {
        if (++retry > 0xffffffe)
        {
            SD_SPI_DESELECT();
            return 1;
        }
    }
    
    for(i=0; i<512; ++i)
    {
        *buffer++ = ReadWrite_Byte(0xff);
    }
    
    (void)ReadWrite_Byte(0xff);
    (void)ReadWrite_Byte(0xff);
    
    

    SD_SPI_DESELECT();
    (void)ReadWrite_Byte(0xff);

    return 0;
}


/**
 *    @brief   写SD卡一个扇区
 * 
 *    @param   sector   扇区号
 *    @param   buffer   缓存数据
 *    
 *    @return  
 */
unsigned char SD_WriteSignleBlock(unsigned long sector, unsigned char *buffer)
{
    unsigned char response = 0;
    unsigned int i = 0;
    unsigned long retry = 0;
        
    response = SD_SPI_SendCommand(CMD_WRITE_SINGLE_BLOCK, sector<<9);
    
    if (response != 0x00)
    {
        return response;
    }

    SD_SPI_SELECT();    
    
    
    (void)ReadWrite_Byte(0xff);
    (void)ReadWrite_Byte(0xff);
    (void)ReadWrite_Byte(0xff);
    

    (void)ReadWrite_Byte(0xfe);

    
    for(i=0; i<512; i++)
    {
        (void)ReadWrite_Byte(*buffer++);
    }
    
    (void)ReadWrite_Byte(0xff);
    (void)ReadWrite_Byte(0xff);
    
    response = ReadWrite_Byte(0xff);

    if ( (response & 0x1f) != 0x05)
    {
        SD_SPI_DESELECT();

        return response;
    }
    
    while (0x00 != ReadWrite_Byte(0xff))
    {
        if (retry++ > 0xfffe)
        {
            SD_SPI_DESELECT();

            return 1;
        }
    }
    SD_SPI_DESELECT();
    
    (void)ReadWrite_Byte(0xff);
        
    return 0;
}
