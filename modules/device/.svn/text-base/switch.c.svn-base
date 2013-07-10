/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     switch.c
 *
 *        @brief    开关硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/4/6  20:49
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/6    create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "switch.h"   
#include "gpio.h"

/**
 * 文件内部宏定义
 */
#define   SWITCH_NUM          10        /**< 开关的数量 */
#define   SWITCH_GROUP_NUM    1         /**< 开关zu的数量 */


/**
 *  开关控制块
 */
typedef struct switch_control_block {
    bool_t  openflag;           /**< 打开标志 */
    bool_t  errorflag;          /**< 错误标志 */
}SWCB;

static SWCB swcb_table[SWITCH_NUM];

typedef struct switch_group{
    ID  switch0;           /**< 开关0 */
    ID  switch1;           /**< 开关1 */
    ID  switch2;           /**< 开关2 */
    ID  switch3;           /**< 开关3 */
    ID  switch4;           /**< 开关4 */
    ID  switch5;           /**< 开关5 */
    ID  switch6;           /**< 开关6 */
    ID  switch7;           /**< 开关7 */
}SWGP;

SWGP swgp_table[SWITCH_GROUP_NUM];

/**
 *  开关控制块和io口ID之间的转换
 */
#define  INDEX_SWITCH(switch_no)  ((uint_t)(switch_no))
#define  get_swcb(switch_no)      (&(swcb_table[INDEX_SWITCH(switch_no)]))

/**
 *  开关控制块和io口ID之间的转换
 */
#define  INDEX_SWITCH_GROUP(switch_no)  ((uint_t)(switch_no))
#define  get_swgp(switch_no)            (&(swgp_table[INDEX_SWITCH_GROUP(switch_no)]))

/** 
 * switch的ID方法定义
 */
#define   SWITCH_NO_GET(switchid)    (switchid & 0x0000ffff)
#define   SWITCH_PORT_GET(switchid)  (PORT_NO_GET(switchid >> 16))
#define   SWITCH_PIN_GET(switchid)   (PIN_NO_GET(switchid >> 16))


static ER switch_open_port(ID switchid);

/**
 *    @brief   开关初始化
 */
void switch_init(void)
{
    uint_t i;
    SWCB *p_swcb;
    SWGP *p_swgp;

    for (p_swcb = swcb_table, i = 0; i < SWITCH_NUM; p_swcb++, i++)
    {
        p_swcb->openflag  = FALSE;
        p_swcb->errorflag = E_SYS;
    }
    for (p_swgp = swgp_table, i = 0; i < SWITCH_GROUP_NUM; p_swgp++, i++)
    {
        p_swgp->switch0 = SWITCH0;
        p_swgp->switch1 = SWITCH1;
        p_swgp->switch2 = SWITCH2;
        p_swgp->switch3 = SWITCH3;
        p_swgp->switch4 = SWITCH0;
        p_swgp->switch5 = SWITCH1;
        p_swgp->switch6 = SWITCH2;
        p_swgp->switch7 = SWITCH3;
    }
    
    switch_open_port(SWITCH0);
    switch_open_port(SWITCH1);
    switch_open_port(SWITCH2);
    switch_open_port(SWITCH3);
}

/**
 *    @brief   打开switch端口
 *
 *    @param   switchid  开关的ID号
 *
 *    @return  ercd 错误码
 */
static ER switch_open_port(ID switchid)
{
    SWCB *p_swcb;
    ER ercd;
    ID switch_no;

    switch_no = SWITCH_NO_GET(switchid);

    if (!(0 <= switch_no && switch_no < SWITCH_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_swcb = get_swcb(switch_no);

    if (p_swcb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        gpio_init(SWITCH_PORT_GET(switchid), SWITCH_PIN_GET(switchid), IN_PUT, 0);

        p_swcb->openflag = TRUE;

        ercd = E_OK;
    }

    return (ercd);
}

/**
 *    @brief   读取开关的值
 *
 *    @param   switchid  开关的ID号
 *
 *    @return  switch_state 开关的电平状态
 */
bool_t switch_read(ID switchid)
{
    SWCB *p_swcb;
    ID switch_no;
    bool_t switch_state;

    switch_no = SWITCH_NO_GET(switchid);

    if (!(0 <= switch_no && switch_no < SWITCH_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_swcb = get_swcb(switch_no);

    if (p_swcb->openflag)
    { /* 检查是否已经打开 */
        switch_state = gpio_get(SWITCH_PORT_GET(switchid), SWITCH_PIN_GET(switchid));
    }
    else
    {
        return (E_ILUSE);
    }

    return (switch_state);
}

/**
 *    @brief   读取8位开关的值
 *
 *    @param   switchid  开关的ID号
 *
 *    @return  switch_state 开关的电平状态
 */
uint8_t switch_read_8bit(ID switchid)
{
    SWGP *p_swgp;
    uint8_t swgp_state;
    bool_t state_temp[7];

    p_swgp = get_swgp(switchid);             /* 获取指针地址 */
    
    state_temp[0] = switch_read(p_swgp->switch0);
    state_temp[1] = switch_read(p_swgp->switch1);
    state_temp[2] = switch_read(p_swgp->switch2);
    state_temp[3] = switch_read(p_swgp->switch3);
    state_temp[4] = switch_read(p_swgp->switch4);
    state_temp[5] = switch_read(p_swgp->switch5);
    state_temp[6] = switch_read(p_swgp->switch6);
    state_temp[7] = switch_read(p_swgp->switch7);
    
    swgp_state = (state_temp[7] << 7) | (state_temp[6] << 6) | (state_temp[5] << 5)
                |(state_temp[4] << 4) | (state_temp[3] << 3) | (state_temp[2] << 2)
                |(state_temp[1] << 1) | (state_temp[0]);
            
    return (swgp_state);
}
