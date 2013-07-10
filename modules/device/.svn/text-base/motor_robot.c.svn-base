/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     motor_robot.c
 *
 *        @brief    机器人电机硬件抽象层函数
 *
 *        @version  0.1
 *        @date     2012/10/17  16:16
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/10/17   create orignal file
 * =====================================================================================
 */
#include<stdio.h>

#include "motor_robot.h"
#include "gpio.h"

/**
 * 文件内部宏定义
 */
#define   MOTOR_NUM    4       /**< 电机的数量 */

/**
 * 电机类型定义
 */
#define    MOTOR_DC    0x00    /**< 直流电机 */
#define    MOTOR_AC    0x80    /**< 交流电机 */

/**
 *  灯控制块
 */
typedef struct motor_control_block {
    ID        id;               /**< 电机的ID号 */
    uint8_t   type;             /**< 电机的类型 */
    int32_t   speed;            /**< 电机的转速 */    
    int32_t   voltage;          /**< 电机的电压值（占空比） */
    int32_t   current;          /**< 电机的电流值 */
    bool_t    openflag;         /**< 打开标志 */
    bool_t    errorflag;        /**< 错误标志 */
}MTCB;

static MTCB mtcb_table[MOTOR_NUM];

/**
 *  电机控制块和io口ID之间的转换
 */
#define  INDEX_MOTOR(motor_no)  ((uint_t)(motor_no))
#define  get_mtcb(motor_no)     (&(mtcb_table[INDEX_MOTOR(motor_no)]))


/** 
 * 电机的ID方法定义
 */
#define   MOTOR_NO_GET(motorid)    (motorid & 0x0000ffff)
#define   MOTOR_MOD_GET(motorid)   (FTM_MOD_GET((motorid & 0xffff0000) >> 16))
#define   MOTOR_CH_GET(motorid)    (FTM_CH_GET((motorid & 0xffff0000) >> 16))

static ER motor_robot_open_port(ID motorid);

const int gl_cSpeedDifference[3][ANGLE_MAX] = {
{100, 98, 97, 95, 93, 	92, 90, 88, 87, 85, 	83, 82, 80, 78, 77, 	75, 73, 72, 70, 69, 	67, 65, 64, 62, 60, 	59, 57, 56, 54, 52,
51, 49, 48, 46, 45, 	43, 41, 40, 38, 37, 	35, 34, 32, 31, 29, 	28, 26, 25, 23, 22, 	21, 19, 18, 16, 15, 	13, 12, 11, 9, 8},
{100, 98, 97, 95, 94, 	92, 91, 89, 88, 86, 	85, 83, 82, 81, 79, 	78, 77, 76, 74, 73, 	72, 71, 70, 69, 68, 	67, 66, 65, 64, 63,
62, 61, 60, 59, 58, 	57, 56, 56, 55, 54, 	53, 53, 52, 51, 50, 	50, 49, 49, 48, 47, 	47, 46, 46, 45, 45, 	44, 44, 43, 43, 42},
{100, 100, 100, 100, 100, 	100, 99, 99, 99, 99, 	99, 98, 98, 98, 97, 	97, 97, 96, 96, 95, 	95, 94, 94, 93, 93, 	92, 92, 91, 90, 90,
89, 89, 88, 87, 86, 	86, 85, 84, 84, 83, 	82, 81, 81, 80, 79, 	78, 77, 76, 76, 75, 	74, 73, 72, 71, 70, 	69, 68, 67, 67, 66}};


/**
 *    @brief   motor初始化
 */
void motor_robot_init(void)
{
    uint_t i;
    MTCB *p_mtcb;

    for (p_mtcb = mtcb_table, i = 0; i < MOTOR_NUM; p_mtcb++, i++)
    {
        p_mtcb->type = MOTOR_DC;
        p_mtcb->speed = 0;
        p_mtcb->voltage = 0;
        p_mtcb->current = 0;
        p_mtcb->openflag = FALSE;
        p_mtcb->errorflag = E_SYS;
    }
    
    /* 打开电机端口 */
    motor_robot_open_port(MOTOR0_ROBOT);
    motor_robot_open_port(MOTOR1_ROBOT);
    motor_robot_open_port(MOTOR2_ROBOT);
    motor_robot_open_port(MOTOR3_ROBOT);
    
    gpio_init(PORT_NO_GET(MOTOR0_INA_PIN), PIN_NO_GET(MOTOR0_INA_PIN),
              OUT_PUT, MOTOR_HIGH);
    gpio_init(PORT_NO_GET(MOTOR0_INB_PIN), PIN_NO_GET(MOTOR0_INB_PIN),
                  OUT_PUT, MOTOR_LOW);
    
    gpio_init(PORT_NO_GET(MOTOR1_INC_PIN), PIN_NO_GET(MOTOR1_INC_PIN),
              OUT_PUT, MOTOR_HIGH);
    gpio_init(PORT_NO_GET(MOTOR1_IND_PIN), PIN_NO_GET(MOTOR1_IND_PIN),
                  OUT_PUT, MOTOR_LOW);

    gpio_init(PORT_NO_GET(MOTOR2_INA_PIN), PIN_NO_GET(MOTOR2_INA_PIN),
              OUT_PUT, MOTOR_HIGH);
    gpio_init(PORT_NO_GET(MOTOR2_INB_PIN), PIN_NO_GET(MOTOR2_INB_PIN),
                  OUT_PUT, MOTOR_LOW);

    gpio_init(PORT_NO_GET(MOTOR3_INC_PIN), PIN_NO_GET(MOTOR3_INC_PIN),
              OUT_PUT, MOTOR_HIGH);
    gpio_init(PORT_NO_GET(MOTOR3_IND_PIN), PIN_NO_GET(MOTOR3_IND_PIN),
                  OUT_PUT, MOTOR_LOW);

    motor_robot_output(MOTOR0_ROBOT, 0);
    motor_robot_output(MOTOR1_ROBOT, 0);
    motor_robot_output(MOTOR2_ROBOT, 0);
    motor_robot_output(MOTOR3_ROBOT, 0);
}

/**
 *    @brief   打开motor端口
 *
 *    @param   motorid  电机的ID号
 *
 *    @return  ercd 错误码
 */
static ER motor_robot_open_port(ID motorid)
{
    MTCB *p_mtcb;
    ER ercd;
    ID motor_no;

    motor_no = MOTOR_NO_GET(motorid);

    if (!(0 <= motor_no && motor_no < MOTOR_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    p_mtcb = get_mtcb(motor_no);

    if (p_mtcb->openflag)
    { /* 检查是否已经打开 */
        ercd = E_OBJ;
    }
    else
    {
        /**
         *  硬件初始化
         */
        ftm_pwm_init(MOTOR_MOD_GET(motorid), MOTOR_CH_GET(motorid));

        p_mtcb->openflag = TRUE;

        ercd = E_OK;
    }

    return (ercd);
}

/**
 *    @brief   motor*4输出
 */
void motor_robot_handle(int speed, int angle)
{
	int insideFrontSpeedRef;
	int insideRearSpeedRef;
	int outsideFrontSpeedRef;
	int outsideRearSpeedRef;
	int absangle;

	if ((angle == 0) || (speed == 0))
	{
		motor_robot_output4(speed,speed,speed,speed);
	}
	else
	{

		if (angle < 0)
		{
			absangle = -angle;
		}
		else
		{
			absangle = angle;
		}
		if (absangle >= ANGLE_MAX)
		{
			absangle = ANGLE_MAX - 1;
		}

		insideRearSpeedRef = ((int32_t)gl_cSpeedDifference[0][absangle] * speed) / 100;
		insideFrontSpeedRef = ((int32_t)gl_cSpeedDifference[1][absangle] * speed) / 100;
		outsideRearSpeedRef = ((int32_t)gl_cSpeedDifference[2][absangle] * speed) / 100;
		outsideFrontSpeedRef = speed;

		if ((angle > 0) && (speed > 0))
		{
			motor_robot_output4(outsideRearSpeedRef, outsideFrontSpeedRef, insideRearSpeedRef, insideFrontSpeedRef);
		}
		else if ((angle < 0) && (speed > 0))
		{
			motor_robot_output4(insideRearSpeedRef, insideFrontSpeedRef, outsideRearSpeedRef, outsideFrontSpeedRef);
		}
		else if ((angle > 0) && (speed < 0))
		{
			motor_robot_output4(outsideFrontSpeedRef, outsideRearSpeedRef, insideFrontSpeedRef, insideRearSpeedRef);
		}
		else if ((angle < 0) && (speed < 0))
		{
			motor_robot_output4(insideFrontSpeedRef, insideRearSpeedRef, outsideFrontSpeedRef, outsideRearSpeedRef);
		}
	}
}

/**
 *    @brief   motor*4输出
 */
void motor_robot_output4(int LR_PWM, int LF_PWM, int RR_PWM, int RF_PWM)
{
	motor_robot_output(MOTOR_LR, LR_PWM);
	motor_robot_output(MOTOR_LF, LF_PWM);
	motor_robot_output(MOTOR_RR, RR_PWM);
	motor_robot_output(MOTOR_RF, RF_PWM);
}

/**
 *    @brief   motor输出
 *
 *    @param   motorid    电机的ID号
 *    @param   motor_duty 电机占空比
 *
 *    @return  ercd 错误码
 */
ER motor_robot_output(ID motorid, int32_t motor_duty)
{
    MTCB *p_mtcb;
    ER ercd = 0;
    ID motor_no;
    int32_t motor_value;

    motor_no = MOTOR_NO_GET(motorid);

    if (!(0 <= motor_no && motor_no < MOTOR_NUM))
    {
        return (E_ID); /* ID号错误 */
    }
    
    /* 占空比范围保护 */
    if(motor_duty > MOTOR_MAX_VAL)
    {
        motor_duty = MOTOR_MAX_VAL;
    }
    else if (motor_duty < MOTOR_MIN_VAL)
    {
        motor_duty = MOTOR_MIN_VAL;
    }
    
    p_mtcb = get_mtcb(motor_no);

    if (p_mtcb->openflag)
    { /* 检查是否已经打开 */
        
        /* for "H" Bridge Drive,there is an "IO" Port to Control Motor Direction */
        if (motor_duty >= 0)
        {
            /*  If PWM is Positive Number,Motor Running Forward. */
            motor_robot_output_dir_fw(motorid);
            //motor_duty = 100 - motor_duty;     /* 电磁组电机默认高点平，需要取反 */
        }
        else
        {
            /*  Else,Motor Running Backward.*/
            motor_robot_output_dir_bw(motorid);
            motor_duty = -motor_duty;
            //motor_duty = 100 + motor_duty;  /* 电磁组电机默认高点平，需要取反 */
        }
        motor_value = motor_duty * MOTOR_PWM_PRESCALE;
        ftm_pwm_output(MOTOR_MOD_GET(motorid), MOTOR_CH_GET(motorid), motor_value);
    
        ercd = E_OK;
    }
    else
    {
        ercd = E_ILUSE;
    }

    return (ercd);
}

/**
 *    @brief   motor前进方向设置
 *
 *    @param   motorid    电机的ID号
 */
void motor_robot_output_dir_fw(ID motorid)
{
	if (motorid == MOTOR_LF)
	{
		gpio_set(PORT_NO_GET(MOTOR0_INA_PIN), PIN_NO_GET(MOTOR0_INA_PIN),
				MOTOR_LOW);
		gpio_set(PORT_NO_GET(MOTOR0_INB_PIN), PIN_NO_GET(MOTOR0_INB_PIN),
				MOTOR_HIGH);
	}
	else if (motorid == MOTOR_RF)
	{
		gpio_set(PORT_NO_GET(MOTOR1_INC_PIN), PIN_NO_GET(MOTOR1_INC_PIN),
				MOTOR_HIGH);
		gpio_set(PORT_NO_GET(MOTOR1_IND_PIN), PIN_NO_GET(MOTOR1_IND_PIN),
				MOTOR_LOW);
	}
	else if (motorid == MOTOR_LR)
	{
		gpio_set(PORT_NO_GET(MOTOR2_INA_PIN), PIN_NO_GET(MOTOR2_INA_PIN),
				MOTOR_LOW);
		gpio_set(PORT_NO_GET(MOTOR2_INB_PIN), PIN_NO_GET(MOTOR2_INB_PIN),
				MOTOR_HIGH);
	}
	else
	{
		gpio_set(PORT_NO_GET(MOTOR3_INC_PIN), PIN_NO_GET(MOTOR3_INC_PIN),
				MOTOR_HIGH);
		gpio_set(PORT_NO_GET(MOTOR3_IND_PIN), PIN_NO_GET(MOTOR3_IND_PIN),
				MOTOR_LOW);
	}
}

/**
 *    @brief   motor后退方向设置
 *
 *    @param   motorid    电机的ID号
 */
void motor_robot_output_dir_bw(ID motorid)
{
	if (motorid == MOTOR_LF)
	{
		gpio_set(PORT_NO_GET(MOTOR0_INA_PIN), PIN_NO_GET(MOTOR0_INA_PIN),
				MOTOR_HIGH);
		gpio_set(PORT_NO_GET(MOTOR0_INB_PIN), PIN_NO_GET(MOTOR0_INB_PIN),
				MOTOR_LOW);
	}
	else if (motorid == MOTOR_RF)
	{
		gpio_set(PORT_NO_GET(MOTOR1_INC_PIN), PIN_NO_GET(MOTOR1_INC_PIN),
				MOTOR_LOW);
		gpio_set(PORT_NO_GET(MOTOR1_IND_PIN), PIN_NO_GET(MOTOR1_IND_PIN),
				MOTOR_HIGH);
	}
	else if (motorid == MOTOR_LR)
	{
		gpio_set(PORT_NO_GET(MOTOR2_INA_PIN), PIN_NO_GET(MOTOR2_INA_PIN),
				MOTOR_HIGH);
		gpio_set(PORT_NO_GET(MOTOR2_INB_PIN), PIN_NO_GET(MOTOR2_INB_PIN),
				MOTOR_LOW);
	}
	else
	{
		gpio_set(PORT_NO_GET(MOTOR3_INC_PIN), PIN_NO_GET(MOTOR3_INC_PIN),
				MOTOR_LOW);
		gpio_set(PORT_NO_GET(MOTOR3_IND_PIN), PIN_NO_GET(MOTOR3_IND_PIN),
				MOTOR_HIGH);
	}
}
