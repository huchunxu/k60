/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sd_rw.h
 *
 *        @brief    SD卡直接读写的驱动函数头文件
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
#ifndef _SD_SUN_H_
#define _SD_SUN_H_
#include "common.h"

#define CRLF                       0x0d0a
#define CRLF_ROAD                  0xfe


#define SD_TYPE_V2HC               3
#define SD_TYPE_V2                 2
/********************************SD CMD*****************************************/
#define CMD_GO_IDLE_STATE 0x00         /* CMD0: response R1 */
#define CMD_SEND_OP_COND 0x01          /* CMD1: response R1 */
#define CMD_SEND_CSD 0x09              /* CMD9: response R1 */
#define CMD_SEND_CID 0x0a              /* CMD10: response R1 */
#define CMD_STOP_TRANSMISSION 0x0c     /* CMD12: response R1 */
#define CMD_SEND_STATUS 0x0d           /* CMD13: response R2 */
#define CMD_SET_BLOCKLEN 0x10          /* CMD16: arg0[31:0]: block length, response R1 */
#define CMD_READ_SINGLE_BLOCK 0x11     /* CMD17: arg0[31:0]: data address, response R1 */
#define CMD_READ_MULTIPLE_BLOCK 0x12   /* CMD18: arg0[31:0]: data address, response R1 */
#define CMD_WRITE_SINGLE_BLOCK 0x18    /* CMD24: arg0[31:0]: data address, response R1 */
#define CMD_WRITE_MULTIPLE_BLOCK 0x19  /* CMD25: arg0[31:0]: data address, response R1 */
#define CMD_PROGRAM_CSD 0x1b           /* CMD27: response R1 */
#define CMD_SET_WRITE_PROT 0x1c        /* CMD28: arg0[31:0]: data address, response R1b */
#define CMD_CLR_WRITE_PROT 0x1d        /* CMD29: arg0[31:0]: data address, response R1b */
#define CMD_SEND_WRITE_PROT 0x1e       /* CMD30: arg0[31:0]: write protect data address, response R1 */
#define CMD_TAG_SECTOR_START 0x20      /* CMD32: arg0[31:0]: data address, response R1 */
#define CMD_TAG_SECTOR_END 0x21        /* CMD33: arg0[31:0]: data address, response R1 */
#define CMD_UNTAG_SECTOR 0x22          /* CMD34: arg0[31:0]: data address, response R1 */
#define CMD_TAG_ERASE_GROUP_START 0x23 /* CMD35: arg0[31:0]: data address, response R1 */
#define CMD_TAG_ERASE_GROUP_END 0x24   /* CMD36: arg0[31:0]: data address, response R1 */
#define CMD_UNTAG_ERASE_GROUP 0x25     /* CMD37: arg0[31:0]: data address, response R1 */
#define CMD_ERASE 0x26                 /* CMD38: arg0[31:0]: stuff bits, response R1b */
#define CMD_LOCK_UNLOCK 0x2a           /* CMD42: arg0[31:0]: stuff bits, response R1b */
#define CMD_READ_OCR 0x3a              /* CMD58: response R3 */
#define CMD_CRC_ON_OFF 0x3b            /* CMD59: arg0[31:1]: stuff bits, arg0[0:0]: crc option, response R1 */

#define CMD55                 0x37
#define ACMD41                (0xC0|41)
/* command responses */
/* R1: size 1 byte */
#define R1_IDLE_STATE         0
#define R1_ERASE_RESET        1
#define R1_ILL_COMMAND        2
#define R1_COM_CRC_ERR        3
#define R1_ERASE_SEQ_ERR      4
#define R1_ADDR_ERR           5
#define R1_PARAM_ERR          6
/* R1b: equals R1, additional busy bytes */
/* R2: size 2 bytes */
#define R2_CARD_LOCKED        0
#define R2_WP_ERASE_SKIP      1
#define R2_ERR                2
#define R2_CARD_ERR           3
#define R2_CARD_ECC_FAIL      4
#define R2_WP_VIOLATION       5
#define R2_INVAL_ERASE        6
#define R2_OUT_OF_RANGE       7
#define R2_CSD_OVERWRITE      7
#define R2_IDLE_STATE         (R1_IDLE_STATE + 8)
#define R2_ERASE_RESET        (R1_ERASE_RESET + 8)
#define R2_ILL_COMMAND        (R1_ILL_COMMAND + 8)
#define R2_COM_CRC_ERR        (R1_COM_CRC_ERR + 8)
#define R2_ERASE_SEQ_ERR      (R1_ERASE_SEQ_ERR + 8)
#define R2_ADDR_ERR           (R1_ADDR_ERR + 8)
#define R2_PARAM_ERR          (R1_PARAM_ERR + 8)
/* R3: size 5 bytes */
#define R3_OCR_MASK           (0xffffffffUL)
#define R3_IDLE_STATE         (R1_IDLE_STATE + 32)
#define R3_ERASE_RESET        (R1_ERASE_RESET + 32)
#define R3_ILL_COMMAND        (R1_ILL_COMMAND + 32)
#define R3_COM_CRC_ERR        (R1_COM_CRC_ERR + 32)
#define R3_ERASE_SEQ_ERR      (R1_ERASE_SEQ_ERR + 32)
#define R3_ADDR_ERR           (R1_ADDR_ERR + 32)
#define R3_PARAM_ERR          (R1_PARAM_ERR + 32)
/* Data Response: size 1 byte */
#define DR_STATUS_MASK        0x0e
#define DR_STATUS_ACCEPTED    0x05
#define DR_STATUS_CRC_ERR     0x0a
#define DR_STATUS_WRITE_ERR   0x0c

/*   Function Declaration   */
unsigned char ReadWrite_Byte(unsigned char writeChar);
unsigned char SD_SPI_SendCommand(unsigned char cmd, unsigned long arg);
unsigned char SD_SPI_SendCommand_NoDeassert(unsigned char cmd, unsigned long arg, char crc);

unsigned char SD_ReadSingleBlock(unsigned long sector, unsigned char *buffer);
unsigned char SD_WriteSignleBlock(unsigned long sector, unsigned char *buffer);

#endif   //End of _SD_H_
