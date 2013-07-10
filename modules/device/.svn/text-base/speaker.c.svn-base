/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     speaker.c
 *
 *        @brief    蜂鸣器硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/4/16  20：57
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/16    create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "speaker.h"   
#include "gpio.h"


/**
 * 文件内部宏定义
 */
#define   SPEAKER_NUM    1        /**< 蜂鸣器的数量 */

/**
 *  灯控制块
 */
typedef struct speaker_control_block {
    bool_t  speaker_state;
    bool_t  openflag;           /**< 打开标志 */
    bool_t  errorflag;          /**< 错误标志 */
}SPKCB;

static SPKCB spkcb_table[SPEAKER_NUM];

/**
 *  灯控制块和io口ID之间的转换
 */
#define  INDEX_SPEAKER(speaker_no)  ((uint_t)(speaker_no))
#define  get_spkcb(speaker_no)      (&(spkcb_table[INDEX_SPEAKER(speaker_no)]))


/** 
 * light的ID方法定义
 */
#define   SPEAKER_NO_GET(speakerid)    (speakerid & 0x0000ffff)
#define   SPEAKER_PORT_GET(speakerid)  (PORT_NO_GET(speakerid >> 16))
#define   SPEAKER_PIN_GET(speakerid)   (PIN_NO_GET(speakerid >> 16))


static ER speaker_open_port(ID speakerid);

/**
 *    @brief   蜂鸣器初始化
 */
void speaker_init(void)
{
    uint_t i;
    SPKCB *p_spkcb;

    for (p_spkcb = spkcb_table, i = 0; i < SPEAKER_NUM; p_spkcb++, i++)
    {
        p_spkcb->openflag  = FALSE;
        p_spkcb->errorflag = E_SYS;
    }
    
    /* 打开IO口 */
    if(speaker_open_port(SPEAKER0))
        printf("The speaker initialize failed!\n");
}

/**
 *    @brief   打开蜂鸣器端口
 *
 *    @param   speakerid  蜂鸣器的ID号
 *
 *    @return  ercd 错误码
 */
static ER speaker_open_port(ID speakerid)
{
    SPKCB *p_spkcb;
    ER ercd = 0;
    ID speaker_no;

    speaker_no = SPEAKER_NO_GET(speakerid);

    if (!((0 <= speaker_no) && (speaker_no < SPEAKER_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    p_spkcb = get_spkcb(speaker_no);

    if (p_spkcb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        gpio_init(SPEAKER_PORT_GET(speakerid), SPEAKER_PIN_GET(speakerid), OUT_PUT,
                SPEAKER_OFF);

        p_spkcb->openflag = TRUE;
        p_spkcb->speaker_state = SPEAKER_OFF;

        ercd = E_OK;
    }

    return (ercd);
}

/**
 *    @brief   speaker打开控制函数
 *
 *    @param   speakerid  蜂鸣器的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制蜂鸣器的开关
 */
ER speaker_open(ID speakerid)
{
    SPKCB *p_spkcb;
    ER ercd = 0;
    ID speaker_no;

    speaker_no = SPEAKER_NO_GET(speakerid);

    if (!((0 <= speaker_no) && (speaker_no < SPEAKER_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    p_spkcb = get_spkcb(speaker_no);

    if (p_spkcb->openflag)
    { /* 检查是否已经打开 */
        gpio_set(SPEAKER_PORT_GET(speakerid), SPEAKER_PIN_GET(speakerid), SPEAKER_ON);
        p_spkcb->speaker_state = SPEAKER_ON;
        
        ercd = E_OK;
    }
    else
    {
        ercd = E_ILUSE;
    }

    return (ercd);
}

/**
 *    @brief   speaker关闭控制函数
 *
 *    @param   speakerid  蜂鸣器的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制蜂鸣器的开关
 */
ER speaker_close(ID speakerid)
{
    SPKCB *p_spkcb;
    ER ercd = 0;
    ID speaker_no;

    speaker_no = SPEAKER_NO_GET(speakerid);

    if (!((0 <= speaker_no) && (speaker_no < SPEAKER_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    p_spkcb = get_spkcb(speaker_no);

    if (p_spkcb->openflag)
    { /* 检查是否已经打开 */
        gpio_set(SPEAKER_PORT_GET(speakerid), SPEAKER_PIN_GET(speakerid), SPEAKER_OFF);
        p_spkcb->speaker_state = SPEAKER_OFF;
        
        ercd = E_OK;
    }
    else
    {
        ercd = E_ILUSE;
    }

    return (ercd);
}

/**
 *    @brief   speaker状态获取函数
 *
 *    @param   speakerid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
bool_t speaker_read(ID speakerid)
{
    SPKCB *p_spkcb;
    ID speaker_no;

    speaker_no = SPEAKER_NO_GET(speakerid);

    if (!(0 <= speaker_no && speaker_no < SPEAKER_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_spkcb = get_spkcb(speaker_no);

    if (p_spkcb->openflag)
    { /* 检查是否已经打开 */
        return (p_spkcb->speaker_state);
    }
    else
    {
        return (E_ILUSE);
    }
}

