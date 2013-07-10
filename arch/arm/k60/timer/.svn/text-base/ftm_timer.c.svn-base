/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     ftm_timer.c
 *
 *        @brief    ftm定时器相关函数
 *
 *        @version  0.1
 *        @date     2012/3/18 14:14:45
 *
 *        @author   Cao Shen , caoshen.1992@gmail.com
 *//* ==================================================================================
 *  @0.1    Cao Shen 2012/3/18  create orignal file
 * =====================================================================================
 */

#include "ftm_timer.h"
#include "exception.h"

/** FTM_MOD寄存器的值 */
#define   FTM_TIMER_1MS   6250     /**< 总线时钟50MHZ 定时1ms */

/**
 * FTM计数器寄存器，可以任意赋值，赋值后该寄存器值立即变为FTM_CNTIN中的值
 */
#define   FTM_CNT   0

/**
 *  FTM_CNTIN寄存器的值
 */
#define   FTM0_CNTIN_REG   0x0000
#define   FTM1_CNTIN_REG   0x0000
#define   FTM2_CNTIN_REG   0x0000

/**
 *  FTM计数器SC寄存器宏定义设置
 */
#define   FTM_SC_CLKS_SYS  1   /**< 时钟选择：SYS为System clock */
#define   FTM_SC_CLKS_FFC  2   /**< 时钟选择：FFC为Fixed frequency clock */
#define   FTM_SC_CLKS_EXT  3   /**< 时钟选择：EXT为External clock */

#define   FTM_SC_PS_1   0      /**< 时钟选择：预分频因子为1 */
#define   FTM_SC_PS_2   1      /**< 时钟选择：预分频因子为2 */
#define   FTM_SC_PS_4   2      /**< 时钟选择：预分频因子为4 */
#define   FTM_SC_PS_8   3      /**< 时钟选择：预分频因子为8 */
#define   FTM_SC_PS_16  4      /**< 时钟选择：预分频因子为16 */
#define   FTM_SC_PS_32  5      /**< 时钟选择：预分频因子为32 */
#define   FTM_SC_PS_64  6      /**< 时钟选择：预分频因子为64 */
#define   FTM_SC_PS_128 7      /**< 时钟选择：预分频因子为128 */

/**
 * 全局变量定义
 */
volatile uint32_t ftm_count;

/**
 *    @brief ftm定时器初始化 周期：1ms
 *
 *    @param ftm_module  ftm定时器模块号 
 *
 *    @retval
 *          -  0     初始化成功
 *          -  1     初始化失败
 *
 *    @note   移植完毕后要根据加载的时钟相应的调整FTM_MOD寄存器中的值和分频值FTM_SC_PS_X
 */
ER ftm_timer_init(uint32_t ftm_module)
{
	/* 全局变量清零 */
	ftm_count = 0;

	switch(ftm_module)
    {
        case FTM0:
        	/* 使能FTM时钟 */
            SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;

            /*  FTM计数器的终值寄存器，如果系统时钟变为48MHZ，分频后的时钟为3MHZ，那么3000次就是1毫秒
             ** 如果系统时钟变为50MHZ，那么8分频后是6.25MHZ，6250次就是1毫秒 */
            FTM_MOD_REG(FTM0_BASE_PTR) = FTM_TIMER_1MS;

            /* FTM计数器初始值，一般设为0 */
            FTM_CNTIN_REG(FTM0_BASE_PTR) = FTM0_CNTIN_REG;

            /* 写入该寄存器时会立刻装入CNTIN寄存器中的初试值 */
            FTM_CNT_REG(FTM0_BASE_PTR) = FTM_CNT;

            /* 使能TOF溢出中断,选择时钟,选择预分频系数 */
            FTM_SC_REG(FTM0_BASE_PTR) |=((FTM_SC_TOIE_MASK)|(FTM_SC_CLKS(FTM_SC_CLKS_SYS)
                    |(FTM_SC_PS(FTM_SC_PS_8))));

            /* 中断向量表注册，中断优先级设置 */
            exc_install(INT_FTM0, ftm0_timer_handler);
            exc_set_pri(INT_FTM0, 1);
            break;

        case FTM1:
            SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
            FTM_MOD_REG(FTM1_BASE_PTR) = FTM_TIMER_1MS;
            FTM_CNTIN_REG(FTM1_BASE_PTR) = FTM1_CNTIN_REG;
            FTM_CNT_REG(FTM1_BASE_PTR) =FTM_CNT;
            FTM_SC_REG(FTM1_BASE_PTR) |=((FTM_SC_TOIE_MASK)|(FTM_SC_CLKS(FTM_SC_CLKS_SYS)
                                |(FTM_SC_PS(FTM_SC_PS_8))));

            exc_install(INT_FTM1, ftm1_timer_handler);
			exc_set_pri(INT_FTM1, 1);
            break;

        case FTM2:
            SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;
            FTM_MOD_REG(FTM2_BASE_PTR) = FTM_TIMER_1MS;
            FTM_CNTIN_REG(FTM2_BASE_PTR) = FTM2_CNTIN_REG;
            FTM_CNT_REG(FTM2_BASE_PTR) =FTM_CNT;
            FTM_SC_REG(FTM2_BASE_PTR) |=((FTM_SC_TOIE_MASK)|(FTM_SC_CLKS(FTM_SC_CLKS_SYS)
                                |(FTM_SC_PS(FTM_SC_PS_8))));

            exc_install(INT_FTM2, ftm2_timer_handler);
            exc_set_pri(INT_FTM2, 1);
            break;

        default :
            return 1;
            break;
    }
    return E_OK;
}

/**
 *    @brief   停止ftm定时器
 *
 *    @param   ftm_module ftm定时器模块号
 *    @note    未选择任何时钟
 */
void ftm_timer_stop(uint32_t ftm_module)
{
    switch(ftm_module)
    {
		case 0:
		  /* 清零FTM_SC_CLKS值（00没有选择时钟） */
		  FTM_SC_REG(FTM0_BASE_PTR) &= ~FTM_SC_CLKS_MASK;
		  break;

		case 1:
		  FTM_SC_REG(FTM1_BASE_PTR) &= ~FTM_SC_CLKS_MASK;
		  break;

		case 2:
		  FTM_SC_REG(FTM2_BASE_PTR) &= ~FTM_SC_CLKS_MASK;
		  break;
    }
}

/**
 * 	  @brief   ftm定时器中断使能
 *
 *    @param   ftm_module ftm定时器模块号
 *
 *    @note
 */
void ftm_timer_enable(uint32_t ftm_module)
{
	/*开FTM中断*/
	exc_enable(INT_FTM0 + FTM_MOD_GET(ftm_module));
}

/**
 *    @brief   ftm定时器中断使能
 *
 *    @param   ftm_module ftm定时器模块号
 *
 *    @note
 */
void ftm_timer_disable(uint32_t ftm_module)
{
	/* 关FTM中断 */
	exc_disable(INT_FTM0 + FTM_MOD_GET(ftm_module));
}

/**
 *    @brief ftm0定时器中断函数
 */
void ftm0_timer_handler(void)
{
	if((FTM_SC_REG(FTM0_BASE_PTR) & FTM_SC_TOF_MASK) == FTM_SC_TOF_MASK)
	{
		ftm_count++;
	}
	FTM_SC_REG(FTM0_BASE_PTR) &= ~FTM_SC_TOF_MASK;
}

/**
 *    @brief ftm1定时器中断函数
 */
void ftm1_timer_handler(void)
{
    while(1);
}

/**
 *    @brief ftm2定时器中断函数
 */
void ftm2_timer_handler(void)
{
    while(1);
}
