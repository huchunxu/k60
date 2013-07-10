/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     spi.h
 *
 *        @brief    spi总线驱动函数头函数
 *
 *        @version  0.1
 *        @date     2012/4/23 21:30
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/23   create orignal file
 * =====================================================================================
 */
#ifndef __SPI_H__
#define __SPI_H__

#include "common.h"

/**
 *   电路连接引脚连接
 */
#define SD_CS         SD_CS_PIN 
#define SD_MISO       SD_MISO_PIN 
#define SD_MOSI       SD_MOSI_PIN 
#define SD_SCK        SD_SCK_PIN 

/** 
 * 定义主从机模式 
 */
enum spimode
{
    MASTER,    /**< 主机模式 */
    SLAVE      /**< 主机模式 */
};

/**
 *    @brief  SPI初始化
 * 
 *    @param   spino   SPI通道号
 *    @param   master  是否是主机  
 *    
 *    @return  E_ID    输入序号错误
 *    @return  E_OK    初始化正常
 */
ER spi_init(uint8_t spino, uint8_t master);
ER spi_init_fast(uint8_t spino, uint8_t master);

/**
 *    @brief  SPI发送数据
 * 
 *    @param   spino   SPI通道号
 *    @param   data[]  需要发送的数据  
 *    @param   len     需要发送的数据 
 */
void spi_snd(uint8_t spino, uint8_t data[], uint32_t len);

/**
 *    @brief   SPI接收数据
 * 
 *    @param   spino   SPI通道号
 *    @param   data[]  需要发送的数据  
 *    
 *    @return  1     成功
 *    @return  0     失败
 */
uint8_t spi_rcv(uint8_t spino, uint8_t data[]);

/**
 *    @brief   开SPI接收中断
 * 
 *    @param   spino   SPI通道号
 */
void spi_enable_rcv_int(uint8_t spino);

/**
 *    @brief   关SPI接收中断
 * 
 *    @param   spino   SPI通道号
 */
void spi_disable_rcv_int(uint8_t spino);

#endif /* __SPI_H__ */
