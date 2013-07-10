/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     telecontrol.c
 *
 *        @brief    红外线硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/5/8    13:31
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/8    create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "telecontrol.h"   
#include "gpio.h"

/**
 * 文件内部宏定义
 */
#define   TELECTRL_NUM       2   /**< 红外接收器的数量 */


/**
 *  遥控器控制块
 */
typedef struct telectrl_control_block {
    bool_t  openflag;           /**< 打开标志 */
    bool_t  errorflag;          /**< 错误标志 */
    bool_t  state;              /**< 当前状态 */
}TCCB;

static TCCB tccb_table[TELECTRL_NUM];


/**
 *  遥控器控制块和io口ID之间的转换
 */
#define  INDEX_TELECTRL(telectrl_no)  ((uint_t)(telectrl_no))
#define  get_tccb(telectrl_no)           (&(tccb_table[INDEX_TELECTRL(telectrl_no)]))


/** 
 * telecontrol的ID方法定义
 */
#define   TELECTRL_NO_GET(telectrl_id)    (telectrl_id & 0x0000ffff)
#define   TELECTRL_PORT_GET(telectrl_id)  (PORT_NO_GET(telectrl_id >> 16))
#define   TELECTRL_PIN_GET(telectrl_id)   (PIN_NO_GET(telectrl_id >> 16))

static ER telectrl_open_port(ID telectrl_id);

/**
 *    @brief   红外接受器初始化
 */
void telectrl_init(void)
{
    uint_t i;
    TCCB *p_tccb;

    for (p_tccb = tccb_table, i = 0; i < TELECTRL_NUM; p_tccb++, i++)
    {
        p_tccb->openflag  = FALSE;
        p_tccb->errorflag = E_SYS;
        p_tccb->state     = TELECTRL_NS;
    }
    
    telectrl_open_port(TELECTRLA);
    telectrl_open_port(TELECTRLB);
}

/**
 *    @brief   打开红外接受器端口
 *
 *    @param   telectrl_id  红外接受器的ID号
 *
 *    @return  ercd 错误码
 */
static ER telectrl_open_port(ID telectrl_id)
{
    TCCB *p_tccb;
    ER ercd;
    ID telectrl_no;

    telectrl_no = TELECTRL_NO_GET(telectrl_id);

    if (!(0 <= telectrl_no && telectrl_no < TELECTRL_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_tccb = get_tccb(telectrl_no);

    if (p_tccb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        gpio_init(TELECTRL_PORT_GET(telectrl_id), 
                  TELECTRL_PIN_GET(telectrl_id), IN_PUT, 0);

        p_tccb->openflag = TRUE;

        ercd = E_OK;
    }

    return (ercd);
}


/**
 *    @brief   读取红外接受器的值
 *
 *    @param   telectrl_id  红外接受器的ID号
 *
 *    @return  telectrl_state 红外接受器的电平状态
 */
bool_t telectrl_read(ID telectrl_id)
{
    TCCB *p_tccb;
    ID telectrl_no;
    bool_t telectrl_state = 0;

    telectrl_no = TELECTRL_NO_GET(telectrl_id);

    if (!(0 <= telectrl_no && telectrl_no < TELECTRL_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_tccb = get_tccb(telectrl_no);

    if (p_tccb->openflag)
    { /* 检查是否已经打开 */
        telectrl_state = gpio_get(TELECTRL_PORT_GET(telectrl_id), 
                                   TELECTRL_PIN_GET(telectrl_id));
        
        p_tccb->state  = telectrl_state;
    }
    else
    {
        return (E_ILUSE);
    }

    return (telectrl_state);
}
