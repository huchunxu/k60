/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     test_sram.c
 *
 *        @brief    测试外部SRAM
 *
 *        @version  0.1
 *        @date     2012/3/24  21:03:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/3/24   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include "common.h"
#include "light.h"
#include "flexbus.h"
#include "exception.h"
#include "target_serial.h"
#include "serial.h"

int main(void)
{
    uint16_t wdata16 = 0x00;
    uint16_t rdata16 = 0xFFFF;
    uint32_t n = 0;
    
    /* 模块初始化 */
    exc_init();           /* 中断初始化 */
    flexbus_init();       /* flexbus初始化 */
    
    /* 初始化串口 */
    serial_initialize((intptr_t)(NULL));
    
    printf("\n****SRAM Test****\n");
    printf("\nTesting 16-bit write/reads\n");
    
    wdata16=0x1234;   /* data to write to mram */

    while(1)
    {
        for(n=0x00000;n<0x80000;n+=0x2)  /* address offset */
        {
            *(vuint16_t*)(&MRAM_START_ADDRESS + n) = wdata16;  /* write */
            rdata16=(*(vuint16_t*)(&MRAM_START_ADDRESS + n));  /* read */
            printf("ADDR: 0x%08x WRITE: 0x%04x READ: 0x%04x\n",&MRAM_START_ADDRESS + n,wdata16,rdata16);
        }
    }
}

