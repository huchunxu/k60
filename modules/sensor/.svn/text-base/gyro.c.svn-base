/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     gyro.c
 *
 *        @brief    陀螺仪硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/4/21  18：36
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/21    create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "gyro.h" 
#include "adc.h" 

/**
 * 文件内部宏定义
 */
#define   GYRO_NUM    1        /**< 编码器的数量 */

/**
 *  陀螺仪控制块
 */
typedef struct gyro_control_block {
    bool_t  openflag;           /**< 打开标志 */
    bool_t  errorflag;          /**< 错误标志 */
    vuint16_t value;
}GYCB;

static GYCB gycb_table[GYRO_NUM];

/**
 *  陀螺仪控制块和io口ID之间的转换
 */
#define  INDEX_GYRO(gyro_no)    ((uint_t)(gyro_no))
#define  get_gycb(gyro_no)      (&(gycb_table[INDEX_GYRO(gyro_no)]))


/** 
 * 陀螺仪的ID方法定义
 */
#define   GYRO_NO_GET(gyroid)     (gyroid & 0x0000ffff)
#define   GYRO_MOD_GET(gyroid)    (ADC_NO_GET(gyroid >> 16))
#define   GYRO_CH_GET(gyroid)     (ADC_CH_GET(gyroid >> 16))


static ER gyro_open_port(ID gyroid);

/**
 *    @brief   陀螺仪初始化
 */
void gyro_init(void)
{
    uint_t i;
    GYCB *p_gycb;

    for (p_gycb = gycb_table, i = 0; i < GYRO_NUM; p_gycb++, i++)
    {
        p_gycb->openflag  = FALSE;
        p_gycb->errorflag = E_SYS;
        p_gycb->value     = 0;
    }
    
    /* 打开IO口 */
    if(gyro_open_port(GYRO0))
        printf("The gyro initialize failed!\n");
}


/**
 *    @brief   打开gyro端口
 *
 *    @param   gyroid  电机的ID号
 *
 *    @return  ercd 错误码
 */
static ER gyro_open_port(ID gyroid)
{
    GYCB *p_gycb;
    ER ercd;
    ID gyro_no;

    gyro_no = GYRO_NO_GET(gyroid);

    if (!((0 <= gyro_no) && (gyro_no < GYRO_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    p_gycb = get_gycb(gyro_no);

    if (p_gycb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        adc_init(GYRO_MOD_GET(gyroid));    /* 初始化ADC */
        
        p_gycb->openflag = TRUE;
        ercd = E_OK;
    }

    return (ercd);
}


/**
 *    @brief   读取陀螺仪的值
 *
 *    @param   gyroid  陀螺仪的ID号
 *
 *    @return  gyro_value  编码器的寄存器值
 */
vuint16_t gyro_read(ID gyroid)
{
    GYCB *p_gycb;
    ID gyro_no;
    vuint16_t gyro_value = 0;

    gyro_no = GYRO_NO_GET(gyroid);

    if (!((0 <= gyro_no) && (gyro_no < GYRO_NUM)))
    {
        return ((vuint16_t)E_ID); /* ID号错误 */
    }
    p_gycb = get_gycb(gyro_no);

    if (p_gycb->openflag)
    { /* 检查是否已经打开 */
        gyro_value = ad_once(GYRO_MOD_GET(gyroid), GYRO_CH_GET(gyroid));
        p_gycb->value  = gyro_value;
    }
    else
    {
        return ((vuint16_t)E_ILUSE);
    }

    return (gyro_value);
}
