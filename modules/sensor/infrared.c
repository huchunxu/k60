/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**
 *        @file     Infrared.c
 *
 *        @brief    红外硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/10/17  15：36
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/10/17    create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "infrared.h"
#include "gpio.h"

/**
 * 文件内部宏定义
 */
#define   INFRARED_NUM          12        /**< 开关的数量 */

/**
 *  开关控制块
 */
typedef struct infrared_control_block {
    bool_t  openflag;           /**< 打开标志 */
    bool_t  errorflag;          /**< 错误标志 */
}IRCB;

static IRCB ircb_table[INFRARED_NUM];

/**
 *  开关控制块和io口ID之间的转换
 */
#define  INDEX_INFRARED(infrared_no)  ((uint_t)(infrared_no))
#define  get_ircb(infrared_no)      (&(ircb_table[INDEX_INFRARED(infrared_no)]))

/**
 * infrared的ID方法定义
 */
#define   INFRARED_NO_GET(infraredid)    (infraredid & 0x0000ffff)
#define   INFRARED_PORT_GET(infraredid)  (PORT_NO_GET(infraredid >> 16))
#define   INFRARED_PIN_GET(infraredid)   (PIN_NO_GET(infraredid >> 16))


static ER infrared_open_port(ID infraredid);

/**
 *    @brief   红外初始化
 */
void infrared_init(void)
{
    uint_t i;
    IRCB *p_ircb;

    for (p_ircb = ircb_table, i = 0; i < INFRARED_NUM; p_ircb++, i++)
    {
        p_ircb->openflag  = FALSE;
        p_ircb->errorflag = E_SYS;
    }

    infrared_open_port(INFRARED0);
    infrared_open_port(INFRARED1);
    infrared_open_port(INFRARED2);
    infrared_open_port(INFRARED3);
    infrared_open_port(INFRARED4);
    infrared_open_port(INFRARED5);
    infrared_open_port(INFRARED6);
    infrared_open_port(INFRARED7);
    infrared_open_port(INFRARED8);
    infrared_open_port(INFRARED9);
    infrared_open_port(INFRARED10);
    infrared_open_port(INFRARED11);
}

/**
 *    @brief   打开infrared端口
 *
 *    @param   infraredid  开关的ID号
 *
 *    @return  ercd 错误码
 */
static ER infrared_open_port(ID infraredid)
{
	IRCB *p_ircb;
    ER ercd;
    ID infrared_no;

    infrared_no = INFRARED_NO_GET(infraredid);

    if (!(0 <= infrared_no && infrared_no < INFRARED_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_ircb = get_ircb(infrared_no);

    if (p_ircb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        gpio_init(INFRARED_PORT_GET(infraredid), INFRARED_PIN_GET(infraredid), IN_PUT, 0);

        p_ircb->openflag = TRUE;

        ercd = E_OK;
    }

    return (ercd);
}

/**
 *    @brief   读取红外的值
 *
 *    @param   infraredid  开关的ID号
 *
 *    @return  infrared_state 开关的电平状态
 */
bool_t infrared_read(ID infraredid)
{
    IRCB *p_ircb;
    ID infrared_no;
    bool_t infrared_state;

    infrared_no = INFRARED_NO_GET(infraredid);

    if (!(0 <= infrared_no && infrared_no < INFRARED_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_ircb = get_ircb(infrared_no);

    if (p_ircb->openflag)
    { /* 检查是否已经打开 */
        infrared_state = gpio_get(INFRARED_PORT_GET(infraredid), INFRARED_PIN_GET(infraredid));
    }
    else
    {
        return (E_ILUSE);
    }

    return (infrared_state);
}

/**
 *    @brief   读取红外的值
 */
int infrared_read_loc(int infrared_loc)
{
	int infrared_value = 0;

	if(infrared_loc == INFRARED_FRONT)
	{
		infrared_value |= (infrared_read(INFRARED5) & 0x01) << 5;
		infrared_value |= (infrared_read(INFRARED4) & 0x01) << 4;
		infrared_value |= (infrared_read(INFRARED3) & 0x01) << 3;
		infrared_value |= (infrared_read(INFRARED2) & 0x01) << 2;
		infrared_value |= (infrared_read(INFRARED1) & 0x01) << 1;
		infrared_value |= infrared_read(INFRARED0) & 0x01;
	}
	else
	{
		infrared_value |= (infrared_read(INFRARED11) & 0x01) << 5;
		infrared_value |= (infrared_read(INFRARED10) & 0x01) << 4;
		infrared_value |= (infrared_read(INFRARED9)  & 0x01) << 3;
		infrared_value |= (infrared_read(INFRARED8)  & 0x01) << 2;
		infrared_value |= (infrared_read(INFRARED7)  & 0x01) << 1;
		infrared_value |= infrared_read(INFRARED6)   & 0x01;
	}

	return infrared_value;
}

/**
 *    @brief   从右向左找到第一个红外的值
 */
int infrared_read_num(int infrared_value)
{
	int infrared_num = 0;

	for(infrared_num=0;infrared_num<6;infrared_num++)
	{
		if(infrared_value & (0x01 << infrared_num))
		{
			break;
		}
	}

	return infrared_num;
}

/**
 *    @brief   读取传感器亮灯的总数
 */
int infrared_read_amount(int infrared_value)
{
	int i = 0;
	int infrared_amount = 0;

	for(i=0;i<6;i++)
	{
		if(infrared_value & (0x01<<i))
		{
			infrared_amount++;
		}
	}

	return infrared_amount;
}

/**
 *    @brief   读取传感器亮灯的权重
 */
int infrared_read_weight(int infrared_value)
{
	int infrared_weight = 0;

	if(infrared_value & 0x01)
	{
		infrared_weight += 3;
	}
	if(infrared_value & 0x02)
	{
		infrared_weight += 2;
	}
	if(infrared_value & 0x04)
	{
		infrared_weight += 1;
	}
	if(infrared_value & 0x08)
	{
		infrared_weight += -1;
	}
	if(infrared_value & 0x10)
	{
		infrared_weight += -2;
	}
	if(infrared_value & 0x20)
	{
		infrared_weight += -3;
	}

	return infrared_weight;
}
