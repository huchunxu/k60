/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     light.c
 *
 *        @brief    light.c 
 *
 *        @version  0.1
 *        @date     2012/2/14 15:35:40
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/2/14   create orignal file
 *  @0.2    Hu Chunxu   2012/4/2    加入了结构体变量，增强代码的安全性
 * =====================================================================================
 */
#include <stdio.h> 

#include "light.h"   
#include "gpio.h"
#include "sys_timer.h"


/**
 * 文件内部宏定义
 */
#define   LIGHT_NUM            8            /**< 灯的数量 */


/**
 *  灯控制块
 */
typedef struct light_control_block {
    bool_t  state;
    bool_t  openflag;           /**< 打开标志 */
    bool_t  errorflag;          /**< 错误标志 */
}LGCB;

static LGCB lgcb_table[LIGHT_NUM];


/**
 *  灯控制块和io口ID之间的转换
 */
#define  INDEX_LIGHT(light_no)  ((uint_t)(light_no))
#define  get_lgcb(light_no)     (&(lgcb_table[INDEX_LIGHT(light_no)]))


/** 
 * light的ID方法定义
 */
#define   LIGHT_NO_GET(lightid)    (lightid & 0x0000ffff)
#define   LIGHT_PORT_GET(lightid)  (PORT_NO_GET(lightid >> 16))
#define   LIGHT_PIN_GET(lightid)   (PIN_NO_GET(lightid >> 16))

static ER light_open_port(ID lightid);

/**
 *    @brief   light初始化
 */
void light_init(void)
{
    uint_t i;
    LGCB *p_lgcb;

    for (p_lgcb = lgcb_table, i = 0; i < LIGHT_NUM; p_lgcb++, i++)
    {
        p_lgcb->openflag = FALSE;
        p_lgcb->errorflag = E_SYS;
    }

    /* 打开IO口 */
    light_open_port(LIGHT0);
    light_open_port(LIGHT1);
    light_open_port(LIGHT2);
    light_open_port(LIGHT3);

    /* 初始化灯带端口 */
    gpio_init(LIGHT_PORT_GET(LIGHT_BAR0), LIGHT_PIN_GET(LIGHT_BAR0), OUT_PUT,0);
    gpio_init(LIGHT_PORT_GET(LIGHT_BAR1), LIGHT_PIN_GET(LIGHT_BAR1), OUT_PUT,0);
}

/**
 *    @brief   打开light端口
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 */
static ER light_open_port(ID lightid)
{
    LGCB *p_lgcb;
    ER ercd = 0;
    ID light_no;

    light_no = LIGHT_NO_GET(lightid);

    if (!(0 <= light_no && light_no < LIGHT_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_lgcb = get_lgcb(light_no);

    if (p_lgcb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        gpio_init(LIGHT_PORT_GET(lightid), LIGHT_PIN_GET(lightid), OUT_PUT,
                LIGHT_OFF);

        p_lgcb->openflag = TRUE;
        p_lgcb->state = LIGHT_OFF;

        ercd = E_OK;
    }

    return (ercd);
}

/**
 *    @brief   light开灯控制函数
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
ER light_open(ID lightid)
{
    LGCB *p_lgcb;
    ER ercd = 0;
    ID light_no;

    light_no = LIGHT_NO_GET(lightid);

    if (!(0 <= light_no && light_no < LIGHT_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_lgcb = get_lgcb(light_no);

    if (p_lgcb->openflag)
    { /* 检查是否已经打开 */
        gpio_set(LIGHT_PORT_GET(lightid), LIGHT_PIN_GET(lightid), LIGHT_ON);
        p_lgcb->state = LIGHT_ON;
        
        ercd = E_OK;
    }
    else
    {
        ercd = E_ILUSE;
    }

    return (ercd);
}

/**
 *    @brief   打开多个light
 *
 *    @param   light_mask  多个灯的掩码
 */
void light_open_some(uint8_t light_mask)
{
    uint8_t light_no = 0;
    uint8_t n = 0;

    light_close_some(0xff);
    for(n = 0;n < LIGHT_NUM;n++)
    {
        if(light_mask & 0x01)
        {
            switch(light_no)
            {
                case 0:
                    light_open(LIGHT0);
                    break;
                case 1:
                    light_open(LIGHT1);
                    break;
                case 2:
                    light_open(LIGHT2);
                    break;
                case 3:
                    light_open(LIGHT3);
                    break;
                case 4:
                    light_open(LIGHT4);
                    break;
                case 5:
                    light_open(LIGHT5);
                    break;
                case 6:
                    light_open(LIGHT6);
                    break;
                case 7:
                    //light_open(LIGHT7);
                	break;
                default:
                    break;
            }
             
        }
        light_mask = light_mask >> 1;
        light_no ++;
    }   
}

/**
 *    @brief   关闭多个light
 *
 *    @param   light_mask  多个灯的掩码
 */
void light_close_some(uint8_t light_mask)
{
    uint8_t light_no = 0;
    uint8_t n = 0;
    
    for(n = 0;n < LIGHT_NUM;n++)
    {
        if(light_mask & 0x01)
        {
            switch(light_no)
            {
                case 0:
                    light_close(LIGHT0);
                    break;
                case 1:
                    light_close(LIGHT1);
                    break;
                case 2:
                    light_close(LIGHT2);
                    break;
                case 3:
                    light_close(LIGHT3);
                    break;
                case 4:
                    light_close(LIGHT4);
                    break;
                case 5:
                    light_close(LIGHT5);
                    break;
                case 6:
                    light_close(LIGHT6);
                    break;
                case 7:
                    //light_close(LIGHT7);
                    break;
                default:
                    break;
            }
        }
        light_mask = light_mask >> 1;
        light_no ++;
    }   
}

/**
 *    @brief   light关灯控制函数
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
ER light_close(ID lightid)
{
    LGCB *p_lgcb;
    ER ercd = 0;
    ID light_no;

    light_no = LIGHT_NO_GET(lightid);

    if (!(0 <= light_no && light_no < LIGHT_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_lgcb = get_lgcb(light_no);

    if (p_lgcb->openflag)
    { /* 检查是否已经打开 */
        gpio_set(LIGHT_PORT_GET(lightid), LIGHT_PIN_GET(lightid), LIGHT_OFF);
        p_lgcb->state = LIGHT_OFF;
        
        ercd = E_OK;
    }
    else
    {
        ercd = E_ILUSE;
    }

    return (ercd);
}


/**
 *    @brief   light状态获取函数
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   控制指示灯亮暗
 */
bool_t light_read(ID lightid)
{
    LGCB *p_lgcb;
    ID light_no;

    light_no = LIGHT_NO_GET(lightid);

    if (!(0 <= light_no && light_no < LIGHT_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_lgcb = get_lgcb(light_no);

    if (p_lgcb->openflag)
    { /* 检查是否已经打开 */
        return (p_lgcb->state);
    }
    else
    {
        return (E_ILUSE);
    }
}

/**
 *    @brief   light状态变化
 *
 *    @param   lightid  灯的ID号
 *
 *    @return  ercd 错误码
 *
 *    @note   切换指示灯亮暗
 */
ER light_change(ID lightid)
{
    LGCB *p_lgcb;
    ER ercd = 0;
    ID light_no;

    light_no = LIGHT_NO_GET(lightid);

    if (!(0 <= light_no && light_no < LIGHT_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_lgcb = get_lgcb(light_no);

    if (p_lgcb->openflag)
    { /* 检查是否已经打开 */
        gpio_reverse(LIGHT_PORT_GET(lightid), LIGHT_PIN_GET(lightid));
        ercd = E_OK;
    }
    else
    {
        ercd = E_OBJ;
    }

    return (ercd);
}

void light_bar_open(int light_bar_id)
{
	if(light_bar_id == LIGHT_BAR0)
	{
		 gpio_set(LIGHT_PORT_GET(LIGHT_BAR0), LIGHT_PIN_GET(LIGHT_BAR0), 1);
	}
	else
	{
		 gpio_set(LIGHT_PORT_GET(LIGHT_BAR1), LIGHT_PIN_GET(LIGHT_BAR1), 1);
	}

}

void light_bar_close(int light_bar_id)
{
	if(light_bar_id == LIGHT_BAR0)
	{
		 gpio_set(LIGHT_PORT_GET(LIGHT_BAR0), LIGHT_PIN_GET(LIGHT_BAR0), 0);
	}
	else
	{
		 gpio_set(LIGHT_PORT_GET(LIGHT_BAR1), LIGHT_PIN_GET(LIGHT_BAR1), 0);
	}
}

void light_bar_flash(void)
{
	static int flag = 0;

	if((sys_timer_count % 100) == 0)
	{
		if(flag == 0)
		{
			light_bar_open(LIGHT_BAR0);
			light_bar_close(LIGHT_BAR1);
			flag = 1;
		}
		else
		{
			light_bar_open(LIGHT_BAR1);
			light_bar_close(LIGHT_BAR0);
			flag = 0;
		}
	}
}
