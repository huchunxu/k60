/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**         
 *        @file     sram_ntshell.c
 *
 *        @brief    sram ntshell cmd
 *
 *        @version  0.1
 *        @date     2012/4/15 15:10
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/15   create orignal file
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sram_ntshell.h"
#include "task_ntshell.h"
#include "flexbus.h"

static void mww(int argc, char **argv);
static void mdw(int argc, char **argv);

/**
 *    @brief   mww命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void mww_initialize(intptr_t exinf)
{
    ntshell_register("mww", mww);
}

/**
 *    @brief   mww命令注册
 *
 *    @param   exinf  扩展信息
 *
 *    @return  无
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
void mdw_initialize(intptr_t exinf)
{
    ntshell_register("mdw", mdw);
}


/**
 *    @brief   mww命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void mww(int argc, char **argv)
{
    uint32_t addr = 0;
    int data16  = 0;
    
    addr   = atoi(*(argv + 1));
    data16 = atoi(*(argv + 2));
    
    if(data16 > UINT16_MAX)
    {
        printf("The data is too large!\n");
    }
    else if(addr > MRAM_MAX_SHIFT_ADDRESS)
    {
        printf("The address is wrong!\n");
    }
    else
    {
        *(vuint16_t*)(&MRAM_START_ADDRESS + addr) = data16;  /* write */
    }
}

/**
 *    @brief   mdw命令
 *
 *    @param   argc  参数数量
 *    @param   argv  参数指针
 *    
 *    @note    若扩展信息无，传入(intptr_t)(NULL)
 */
static void mdw(int argc, char **argv)
{
    uint32_t addr = 0;
    int data16 = 0;
    
    addr = atoi(*(argv + 1));
    
    if(addr > MRAM_MAX_SHIFT_ADDRESS)
    {
        printf("The address is wrong!\n");
    }
    else
    {
        data16=(*(vuint16_t*)(&MRAM_START_ADDRESS + addr));    /* read */
        printf("ADDR: 0x%08x READ: %d\n", &MRAM_START_ADDRESS + addr, data16);
    }
}



