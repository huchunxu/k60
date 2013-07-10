/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sd.h
 *
 *        @brief    SDCARD抽象层函数头函数
 *
 *        @version  0.1
 *        @date     2012/4/25  10:31
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/25    create orignal file
 * =====================================================================================
 */
#ifndef SD_H_
#define SD_H_

#include "common.h"
#include "ff.h"
#include "gpio.h"
#include "spi.h"

/* 设置SD的SPI速度 */
#define SD_SPI_VERY_HIGH_SPEED()   SPI_CTAR_REG(SPI0_BASE_PTR,0) |= 0x00
#define SD_SPI_HIGH_SPEED()        SPI_CTAR_REG(SPI0_BASE_PTR,0) |= 0x01
#define SD_SPI_LOW_SPEED()         SPI_CTAR_REG(SPI0_BASE_PTR,0) |= 0x08

/* 设置SD卡片选 */
#define SD_SPI_SELECT()            gpio_set(PORT_NO_GET(SD_CS), PIN_NO_GET(SD_CS), LOW_POWER)
#define SD_SPI_DESELECT()          gpio_set(PORT_NO_GET(SD_CS), PIN_NO_GET(SD_CS), HIGH_POWER)


#define  FILE_NAME_LENGHT    12  /*文件名长度 */
/* 全局变量 */
extern FATFS Fatfs;         /* File system object for each logical drive */

/**
 *    @brief   在SD卡中创建一个新的文件
 * 
 *    @param   fp   文件对象
 *    @param   fln  文件名 
 */
void sd_create_file(FIL *fp, char *fln);

/**
 *    @brief   初始化SD卡
 * 
 *    @param   fs   文件系统
 */
void sd_init(FATFS *fs);

/**
 *    @brief   关闭SD卡文件
 * 
 *    @param   fp   文件对象
 */
void sd_close_file(FIL *fp);

/**
 *    @brief   write external message to sd card files
 * 
 *    @param   fp   文件对象
 *    @param   msg  消息
 */
void sd_write_externmsg(FIL *fp, char *msg);


#endif /* SD_H_ */
