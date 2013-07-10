/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     accelerometer.c
 *
 *        @brief    加速度传感器硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/4/21  21：26
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/21    create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "accelerometer.h" 
#include "adc.h" 

/**
 * 文件内部宏定义
 */
#define   ACC_NUM    1        /**< 加速度传感器的数量 */

/**
 *  陀螺仪控制块
 */
typedef struct accelerometer_control_block {
    bool_t    openflag;           /**< 打开标志 */
    bool_t    errorflag;          /**< 错误标志 */
    vuint16_t value;              /**< AD值 */
}ACCB;

static ACCB accb_table[ACC_NUM];

/**
 *  陀螺仪控制块和io口ID之间的转换
 */
#define  INDEX_ACC(acc_no)    ((uint_t)(acc_no))
#define  get_accb(acc_no)      (&(accb_table[INDEX_ACC(acc_no)]))


/** 
 * 陀螺仪的ID方法定义
 */
#define   ACC_NO_GET(accid)     (accid & 0x0000ffff)
#define   ACC_MOD_GET(accid)    (ADC_NO_GET(accid >> 16))
#define   ACC_CH_GET(accid)     (ADC_CH_GET(accid >> 16))


static ER acc_open_port(ID accid);

/**
 *    @brief   陀螺仪初始化
 */
void acc_init(void)
{
    uint_t i;
    ACCB *p_accb;

    for (p_accb = accb_table, i = 0; i < ACC_NUM; p_accb++, i++)
    {
        p_accb->openflag  = FALSE;
        p_accb->errorflag = E_SYS;
        p_accb->value     = 0;
    }
    
    /* 打开IO口 */
    if(acc_open_port(ACC0))
        printf("The accelerometer initialize failed!\n");
}


/**
 *    @brief   打开acc端口
 *
 *    @param   accid  加速度传感器的ID号
 *
 *    @return  ercd 错误码
 */
static ER acc_open_port(ID accid)
{
    ACCB *p_accb;
    ER ercd = 0;
    ID acc_no;

    acc_no = ACC_NO_GET(accid);

    if (!((0 <= acc_no) && (acc_no < ACC_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    p_accb = get_accb(acc_no);

    if (p_accb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        adc_init(ACC_MOD_GET(accid));    /* 初始化ADC */
        
        p_accb->openflag = TRUE;
        
        ercd = E_OK;
    }

    return (ercd);
}


/**
 *    @brief   读取加速度传感器的值
 *
 *    @param   accid  加速度传感器的ID号
 *
 *    @return  acc_value  加速度传感器的寄存器值
 */
vuint16_t acc_read(ID accid)
{
    ACCB *p_accb;
    ID acc_no;
    vuint16_t acc_value = 0;

    acc_no = ACC_NO_GET(accid);

    if (!((0 <= acc_no) && (acc_no < ACC_NUM)))
    {
        return ((vuint16_t)E_ID); /* ID号错误 */
    }
    p_accb = get_accb(acc_no);

    if (p_accb->openflag)
    { /* 检查是否已经打开 */
        acc_value = ad_once(ACC_MOD_GET(accid), ACC_CH_GET(accid));
        p_accb->value = acc_value; 
    }
    else
    {
        return ((vuint16_t)E_ILUSE);
    }

    return (acc_value);
}
