/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**
 *        @file     lptmr.c
 *
 *        @brief    lptmr定时器和脉冲捕捉相关函数
 *
 *        @version  0.1
 *        @date     2012/3/25 17:10:09
 *
 *        @author   Cao Shen , caoshen.1992@gmail.com
 *//* ==================================================================================
 *  @0.1    Cao Shen 2012/3/25  create orignal file
 * =====================================================================================
 */
#include "lptmr.h"
#include "exception.h"

/**  设置lptmr timer compare寄存器的值   */
#define LPTMR_TIMER_COMPARE_INTERNAL 12500      /**< 内部高频2M时钟定时时间设定 */
#define LPTMR_TIMER_COMPARE_LPO      50         /**< LPO1000HZ时钟定时设定*/

/**  设置lptmr pulse capture compare寄存器的值 */
#define LPTMR_PULSE_COMPARE    65535             /**< 捕捉次数设定 */

/**
 * LPTMR模块
 */
/**  设置lptmr timer prescale */
#define LPTMR_TIMER_PRESCALE2     0X0
#define LPTMR_TIMER_PRESCALE4     0X1
#define LPTMR_TIMER_PRESCALE8     0X2
#define LPTMR_TIMER_PRESCALE16    0X3
#define LPTMR_TIMER_PRESCALE32    0X4
#define LPTMR_TIMER_PRESCALE64    0X5
#define LPTMR_TIMER_PRESCALE128   0X6
#define LPTMR_TIMER_PRESCALE256   0X7
#define LPTMR_TIMER_PRESCALE512   0X8
#define LPTMR_TIMER_PRESCALE1024  0X9
#define LPTMR_TIMER_PRESCALE2048  0Xa
#define LPTMR_TIMER_PRESCALE4096  0Xb
#define LPTMR_TIMER_PRESCALE8192  0Xc
#define LPTMR_TIMER_PRESCALE16384 0Xd
#define LPTMR_TIMER_PRESCALE32768 0Xe
#define LPTMR_TIMER_PRESCALE65536 0Xf

/** 设置脉冲捕捉时的极性 */
#define LPTMR_PULSE_CAPTURE_RISING      0                             /**< 捕捉上升沿 */
#define LPTMR_PULSE_CAPTURE_FALLING     LPTMR_CSR_TPP_MASK            /**< 捕捉下降沿 */


static void lptmr_registers_clear(void);

/**   
 *    @brief   lptmr     定时器初始化
 *
 *    @param   clock     时钟选择      
 *
 *    @return  E_OK         初始化成功
 *    @return  E_INIT       初始化失败 
 *
 *    @see    lptmr_registers_clear()  
 *    @note   在这个定时器中，由于产生不了小于35.6ms的基准定时，所以统一选择基准为50ms的定时。
 *            在移植过程中应该相应调整COMPARE寄存器和PSR寄存器中的预分频系数。  
 */  
ER lptmr_timer_init(uint32_t clock)
{

    switch (clock)
    {
        case LPTMR_INTERNAL_CLOCK:
            lptmr_registers_clear();             /* 把LPTMR寄存器清零  */
            SIM_SCGC5 |= SIM_SCGC5_LPTIMER_MASK; /* 使能LPT模块时钟   */
            MCG_C1 |= MCG_C1_IRCLKEN_MASK;       /* 使能内部参考时钟   */
            MCG_C2 |= MCG_C2_IRCS_MASK;          /* MCG_C2[IRCS]=1,使能快速内部参考时钟（2MHz） */

            /**
             *  配置 LPTMR参数 
             */
            LPTMR0_CMR = LPTMR_CMR_COMPARE(LPTMR_TIMER_COMPARE_INTERNAL); /* 设置比较寄存器值 */
            LPTMR0_PSR = LPTMR_PSR_PCS(LPTMR_INTERNAL_CLOCK)
                         |LPTMR_PSR_PRESCALE(LPTMR_TIMER_PRESCALE8);      /* 使用内部时钟，系数预分频为8*/
            LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;                             /* 开启LPT模块设置*/
            break;

        case LPTMR_LPO_CLOCK:
            lptmr_registers_clear();              /* 把LPTMR寄存器清零 */
            SIM_SCGC5 |= SIM_SCGC5_LPTIMER_MASK;  /*使能LPT模块时钟*/

            /**
             * 配置 LPTMR 
             */
            LPTMR0_CMR = LPTMR_CMR_COMPARE(LPTMR_TIMER_COMPARE_LPO);           /*设置比较寄存器值 */
            LPTMR0_PSR = LPTMR_PSR_PCS(LPTMR_LPO_CLOCK) | LPTMR_PSR_PBYP_MASK; /*设置PBYP为1，计数器一次一次累加*/
            LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; /*开启LPT模块设置*/
            break;

        default:
            return E_OBJ;     /*如果初始化失败*/
    }
    return E_OK;             /*如果初始化成功*/
} 

/**   
 *    @brief   lptmr脉冲捕捉初始化
 *
 *    @param   pin       捕捉引脚      
 *
 *    @return  E_OK      初始化成功
 *    @return  E_PIN     初始化失败 
 *
 *    @see     lptmr_registers_clear() 
 *    @note    捕捉上升沿；捕捉一次lptmr计数器加1，到compare寄存器中的值后产生中断 
 *    		   移植过程中要注意根据捕捉的脉冲的频率来调整COMPARE寄存器的值，例如要捕捉频率为1000HZ的脉冲则该值设为1000.
 */      

ER lptmr_pulse_capture_init(PIN pin)
{
    SIM_SCGC5 |= SIM_SCGC5_LPTIMER_MASK; /*使能LPT模块时钟*/
    lptmr_registers_clear();

    switch (pin)
    {
        case PTA19:
            SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; /*打开 PORTA 时钟*/
            PORTA_PCR19 = PORT_PCR_MUX(0x6);   /*在PTA19上使用 ALT6*/
            LPTMR0_CSR = LPTMR_CSR_TPS(0x01);  /*设置LPT使用选择的引脚*/
            break;

        case PTC5:
            SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; /*打开 PORTC 时钟*/
            PORTC_PCR5 = PORT_PCR_MUX(0x4);    /*在PTC5上使用 ALT4*/
            LPTMR0_CSR = LPTMR_CSR_TPS(0x02);  /*设置LPT使用选择的引脚*/
            break;

        default:
            return E_OBJ;
    }

    LPTMR0_PSR |= LPTMR_PSR_PBYP_MASK; /*设定PBYP为1即每捕捉到一次上升沿计数器累加一次*/
    LPTMR0_CMR =  LPTMR_CMR_COMPARE(LPTMR_PULSE_COMPARE); /*设置比较值*/
    LPTMR0_CSR |= LPTMR_CSR_TMS_MASK; /*进入脉冲累加模式,上升沿捕捉*/

    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; /*开启 LPT模块*/
    return E_OK;
}

/**   
 *    @brief   lptmr寄存器清零
 */   
static void lptmr_registers_clear(void)
{
	LPTMR0_CSR=0x00;
	LPTMR0_PSR=0x00;
	LPTMR0_CMR=0x00;
}

/**   
 *    @brief   lptmr使能中断
 *    
 *    @see     exc_enable()
 *    @note    注意在中断使能中要调用exception.c中的exc_enable()函数
 */ 
void lptmr_enable(void)
{
	LPTMR0_CSR|=LPTMR_CSR_TIE_MASK;  /*开启LPT定时器中断 */          
	exc_enable(INT_LPTimer);	     /*开引脚的IRQ中断*/	
}

/**   
 *    @brief   lptmr关闭中断
 *    
 *    @see     exc_disable()
 *    @note    注意在中断使能中要调用exception.c中的exc_disable()函数
 */
void lptmr_disable(void)
{
	LPTMR0_CSR &=~LPTMR_CSR_TIE_MASK;   /*禁止LPT定时器中断 */         
	exc_disable(INT_LPTimer);	    /*关引脚的IRQ中断*/
}

