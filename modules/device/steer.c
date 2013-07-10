/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     steer.c
 *
 *        @brief    电机硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/4/12  21:33
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/12    create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "steer.h"

/**
 * 文件内部宏定义
 */
#define    STEER_NUM    2           /**< 舵机的数量 */

/**
 * 舵机类型定义
 */
#define    STEER_DIGITAL   0x00    /**< 数字舵机 */
#define    STEER_ANALOG    0x80    /**< 模拟舵机 */

/**
 * 舵机功能定义
 */
#define    STEER_DIR_FUNC     0x00      /**< 转向舵机 */
#define    STEER_SERVO_FUNC   0x01      /**< 随动舵机 */

/**
 *  灯控制块
 */
typedef struct steer_control_block {
    ID        id;               /**< 电机的ID号 */
    uint8_t   type;             /**< 电机的类型 */
    int16_t   angle;            /**< 舵机的角度值 */
    uint32_t  value;            /**< 舵机电位器的大小值 */
    int32_t   value_vary;       /**< 舵机电位器值的增量 */
    int32_t   voltage;          /**< 舵机电压值（占空比） */
    uint8_t   func;             /**< 舵机功能 */
    bool_t    openflag;         /**< 打开标志 */
    bool_t    errorflag;        /**< 错误标志 */
}STCB;

static STCB stcb_table[STEER_NUM];

/**
 *  舵机控制块和io口ID之间的转换
 */
#define  INDEX_STEER(steer_no)  ((uint_t)(steer_no))
#define  get_stcb(steer_no)     (&(stcb_table[INDEX_STEER(steer_no)]))


/** 
 * 舵机的ID方法定义
 */
#define   STEER_NO_GET(steerid)    (steerid & 0x0000ffff)
#define   STEER_MOD_GET(steerid)   (FTM_MOD_GET((steerid & 0xffff0000) >> 16))
#define   STEER_CH_GET(steerid)    (FTM_CH_GET((steerid & 0xffff0000) >> 16))


static ER steer_open_port(ID steerid);

/**
 *    @brief   steer初始化
 */
void steer_init(void)
{
    uint_t i;
    STCB *p_stcb;

    for (p_stcb = stcb_table, i = 0; i < STEER_NUM; p_stcb++, i++)
    {
        if(i==0)
        {
            p_stcb->type  = STEER_ANALOG;
            p_stcb->angle = 0;          
            p_stcb->value = 0;                
            p_stcb->value_vary = 0;    
            p_stcb->voltage    = 0;       
            p_stcb->func       = STEER_DIR_FUNC;         
            p_stcb->openflag   = FALSE;
            p_stcb->errorflag  = E_SYS;
        }
        else
        {
            p_stcb->type  = STEER_ANALOG;
            p_stcb->angle = 0;          
            p_stcb->value = 0;                
            p_stcb->value_vary = 0;    
            p_stcb->voltage    = 0;       
            p_stcb->func       = STEER_SERVO_FUNC;         
            p_stcb->openflag   = FALSE;
            p_stcb->errorflag  = E_SYS;
            
        }
    }
    
    /* 打开端口 */
    steer_open_port(STEER_DIR);
    steer_output_angle(STEER_DIR, 0);
}

/**
 *    @brief   打开steer端口
 *
 *    @param   steerid  舵机的ID号
 *
 *    @return  ercd 错误码
 */
static ER steer_open_port(ID steerid)
{
    STCB *p_stcb;
    ER ercd;
    ID steer_no;

    steer_no = STEER_NO_GET(steerid);

    if (!((0 <= steer_no) && (steer_no < STEER_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    p_stcb = get_stcb(steer_no);

    if (p_stcb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        ftm_pwm_init(STEER_MOD_GET(steerid), STEER_CH_GET(steerid));

        p_stcb->openflag = TRUE;

        ercd = E_OK;
    }

    return (ercd);
}

/**
 *    @brief   steer输出
 *
 *    @param   steerid     舵机的ID号
 *    @param   steer_angle 舵机占空比
 *
 *    @return  ercd 错误码
 */
ER steer_output_angle(ID steerid, int16_t steer_angle)
{
    STCB *p_stcb;
    ER ercd;
    ID steer_no;
    int32_t steer_value;

    steer_no = STEER_NO_GET(steerid);

    if (!((0 <= steer_no) && (steer_no < STEER_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
       
    p_stcb = get_stcb(steer_no);

    if (p_stcb->openflag)
    { /* 检查是否已经打开 */
        if(p_stcb->func == STEER_DIR_FUNC)
        {
            /* 占空比范围保护 */
            if(steer_angle > STEER_DIR_MAX_ANGLE)
            {
                steer_angle = STEER_DIR_MAX_ANGLE;
            }
            else if (steer_angle < STEER_DIR_MIN_ANGLE)
            {
                steer_angle = STEER_DIR_MIN_ANGLE;
            }
            
            if (steer_angle < 0)
            {
                steer_value = (STEER_DIR_CENTER - steer_angle * LEFT_STEER_DIR_PRES);
            }
            else
            {
                steer_value = (STEER_DIR_CENTER - steer_angle * RIGHT_STEER_DIR_PRES);
            }
        }
        else
        {
            /* 占空比范围保护 */
            if(steer_angle > STEER_SERVO_MAX_ANGLE)
            {
                steer_angle = STEER_SERVO_MAX_ANGLE;
            }
            else if (steer_angle < STEER_SERVO_MIN_ANGLE)
            {
                steer_angle = STEER_SERVO_MIN_ANGLE;
            }
            
            if (steer_angle < 0)
            {
                steer_value = (STEER_SERVO_CENTER + steer_angle * LEFT_STEER_SERVO_PRES);
            }
            else
            {
                steer_value = (STEER_SERVO_CENTER + steer_angle * RIGHT_STEER_SERVO_PRES);
            }
        }
        
        /* 舵机输出 */
        ftm_pwm_output(STEER_MOD_GET(steerid), STEER_CH_GET(steerid), steer_value);
    }
    else
    {
        ercd = E_ILUSE;
    }

    return (ercd);
}

/**
 *    @brief   steer输出
 *
 *    @param   steerid         舵机的ID号
 *    @param   steer_add_value 舵机计数值在中心值的基础上增加的值
 *
 *    @return  ercd 错误码
 */
ER steer_output_value(ID steerid, int16_t steer_add_value)
{
    STCB *p_stcb;
    ER ercd;
    ID steer_no;
    int32_t steer_value;

    steer_no = STEER_NO_GET(steerid);

    if (!((0 <= steer_no) && (steer_no < STEER_NUM)))
    {
        return (E_ID); /* ID号错误 */
    }
    
    p_stcb = get_stcb(steer_no);

    if (p_stcb->openflag)
    { /* 检查是否已经打开 */
        
        if(p_stcb->func == STEER_DIR_FUNC)
        {
            /* 计数值范围保护 */
            if(steer_add_value > STEER_DIR_MAX_VALUE)
            {
                steer_add_value = STEER_DIR_MAX_VALUE;
            }
            else if (steer_add_value < STEER_DIR_MIN_VALUE)
            {
                steer_add_value = STEER_DIR_MIN_VALUE;
            }
            
            steer_value = STEER_DIR_CENTER + steer_add_value;
        }
        else
        {
            /* 计数值范围保护 */
            if(steer_add_value > STEER_SERVO_MAX_VALUE)
            {
                steer_add_value = STEER_SERVO_MAX_VALUE;
            }
            else if (steer_add_value < STEER_SERVO_MIN_VALUE)
            {
                steer_add_value = STEER_SERVO_MIN_VALUE;
            }
            
            steer_value = STEER_SERVO_CENTER + steer_add_value;
        }
        
        /* 舵机输出 */
        ftm_pwm_output(STEER_MOD_GET(steerid), STEER_CH_GET(steerid), steer_value);
    }
    else
    {
        ercd = E_ILUSE;
    }

    return (ercd);
}
