/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sysinit.c
 *
 *        @brief   
 *
 *        @version  0.1
 *        @date     2012/3/9 11:50:06
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2012/3/9    create orignal file
 * =====================================================================================
 */

#include "sysinit.h"

static void trace_clk_init(void);
static void fb_clk_init(void);
static int32_t pll_init(uint8_t clk_option, uint8_t crystal_val);
static void set_sys_dividers(uint8_t mcg, uint8_t sys_bus, uint8_t flex_bus, uint8_t flash);


/**
 * @brief 硬件初始化，调用该函数之前应准备好堆栈
 */
void hardware_init_hook(void) {
    /* Disable the WDOG module */
    /* WDOG_UNLOCK: WDOGUNLOCK=0xC520 */
    WDOG_UNLOCK = (uint16_t)0xC520U;     /* Key 1 */
    /* WDOG_UNLOCK : WDOGUNLOCK=0xD928 */
    WDOG_UNLOCK  = (uint16_t)0xD928U;    /* Key 2 */
    /* WDOG_STCTRLH: ??=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,??=0,STNDBYEN=1,
     * WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 
     */
    WDOG_STCTRLH = (uint16_t)0x01D2U;

    /* 使能IO端口时钟 */
    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                | SIM_SCGC5_PORTB_MASK
                | SIM_SCGC5_PORTC_MASK
                | SIM_SCGC5_PORTD_MASK
                | SIM_SCGC5_PORTE_MASK);

    /* 初始化时钟 */
    pll_init(PLL_100MHZ, XTAL_8MHZ);

    /* 调试时钟 */
    trace_clk_init();

    /* flexbus时钟使能 */
    fb_clk_init();

#if 0
      /* SIM_SCGC5: PORTB=1,PORTA=1 */
    SIM_SCGC5 |= (uint32_t)0x0600UL;     /* Enable clock gate for ports to enable pin routing */

    /* PORTA_PCR4: ISF=0,MUX=7 */
    PORTA_PCR4 = (uint32_t)((PORTA_PCR4 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);
    /* PORTA_PCR2: ISF=0,MUX=7 */
    PORTA_PCR2 = (uint32_t)((PORTA_PCR2 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);
    /* PORTA_PCR1: ISF=0,MUX=7 */
    PORTA_PCR1 = (uint32_t)((PORTA_PCR1 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);
    /* PORTA_PCR0: ISF=0,MUX=7 */
    PORTA_PCR0 = (uint32_t)((PORTA_PCR0 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);
    /* PORTA_PCR3: ISF=0,MUX=7 */
    PORTA_PCR3 = (uint32_t)((PORTA_PCR3 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);
    /* PORTA_PCR5: ISF=0,MUX=7 */
    PORTA_PCR5 = (uint32_t)((PORTA_PCR5 & (uint32_t)~0x01000000UL) | (uint32_t)0x0700UL);
    /* SIM_SOPT6: RSTFLTEN=0,RSTFLTSEL=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
    SIM_SOPT6 = (uint32_t)0x00UL;        /* Set reset pin filter */
     /* SIM_SCGC7: MPU=1 */
    SIM_SCGC7 |= (uint32_t)0x04UL;
    /* Initialization of the MPU module */
    /* MPU_CESR: SPERR=0,VLD=0, MPU is disabled */
    MPU_CESR &= (uint32_t)~0xF8000001UL;
    /* Initialization of the PMC module */
    /* PMC_LVDSC1: LVDACK=1,LVDIE=0,LVDRE=1,LVDV=0 */
    PMC_LVDSC1 = (uint8_t)((PMC_LVDSC1 & (uint8_t)~(uint8_t)0x23U) | (uint8_t)0x50U);
    /* PMC_LVDSC2: LVWACK=1,LVWIE=0,LVWV=0 */
    PMC_LVDSC2 = (uint8_t)((PMC_LVDSC2 & (uint8_t)~(uint8_t)0x23U) | (uint8_t)0x40U);
    /* PMC_REGSC: TRAMPO=0,??=0,BGBE=0 */
    PMC_REGSC &= (uint8_t)~(uint8_t)0x13U;
    /* MC_PMPROT: ??=0,??=0,AVLP=0,ALLS=0,??=0,AVLLS3=0,AVLLS2=0,AVLLS1=0 */
    MC_PMPROT = (uint8_t)0x00U;          /* Setup Power mode protection register */
    /* Common initialization of the CPU registers */
    /* NVICIP20: PRI20=0 */
    NVICIP20 = (uint8_t)0x00U;
#endif  
}


/**
 * @brief 初始化外部存储控制器
 */
/*static void flexbus_init(void)
{
    ;
}*/


/**
 * @brief 初始化PLL时钟，系统启动时，由FLL提供时钟，如需要切换到由PLL提
 * 供时钟，需要写切换到FBE模式（停止FLL，由外部时钟提供系统时钟），然后
 * 切换到PBE模式（使能PLL），最后切换到PEE模式（由PLL提供系统时钟）
 *
 * @param clk_option    时钟选项：50 Mhz,48 Mhz,96 Mhz, 100 Mhz
 * @param crystal_val   晶振选项：2-32 Mhz
 *
 * @return >0 系统时钟频率 <0 失败
 */
static int32_t pll_init(uint8_t clk_option, uint8_t crystal_val)
{
    int32_t pll_freq;
    /* 参数检查 */
    if (clk_option > PLL_100MHZ) 
        return -1;
    if (crystal_val > XTAL_32MHZ)
        return -1;
    
    /* SIM_SOPT2: PLLFLLSEL=0 */
    /* Select FLL as a clock source for various peripherals */
    SIM_SOPT2 &= (uint32_t)~0x00010000UL; 
    /* SIM_SOPT1: OSC32KSEL=0 */
    /* System oscillator drives 32 kHz clock for various peripherals */
    SIM_SOPT1 &= (uint32_t)~0x00080000UL;
       
    /* 使能外部晶振，如果使用了无源晶振可能还需要设定电容匹配 */
    OSC_CR = (uint8_t)0x80U; 
    /* SIM_SOPT2: MCGCLKSEL=0 */
    SIM_SOPT2 &= (uint32_t)~0x01UL;  
    /* Very high frequency range selected for the crystal oscillator */
    MCG_C2 = MCG_C2_RANGE(2);
    
    /* Select ext oscillator, reference divider and clear IREFS to start ext osc */
    /* CLKS=2, select the external clock source */
    /* FRDIV=3, set the FLL ref divider to keep the ref clock in range */
    /* (even if FLL is not being used) 8 MHz / 256 = 31.25 kHz */
    /* IREFS=0, select the external clock */
    /* IRCLKEN=0, disable IRCLK (can enable it if desired) */
    /* IREFSTEN=0, disable IRC in stop mode (can keep it enabled in stop if desired) */
    MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);
    /* MCG_C4: DMX32=0,DRST_DRS=0 */
    MCG_C4 &= (uint8_t)~(uint8_t)0xE0U;                           
    /* MCG_C5: ??=0,PLLCLKEN=0,PLLSTEN=0,PRDIV=1 */
    MCG_C5 = (uint8_t)0x01U;                             
    /* MCG_C6: LOLIE=0,PLLS=0,CME=0,VDIV=0 */
    MCG_C6 = (uint8_t)0x00U; 

    /* 等待晶振稳定    */
    while (!(MCG_S & MCG_S_OSCINIT_MASK));  
    /* 等待参考时钟状态位清零 */
    while (MCG_S & MCG_S_IREFST_MASK);
    /* 等待时钟状态位显示时钟源来自外部参考时钟 */
    while ((MCG_S & 0x0CU) != 0x08U); 
    /* FBE mode */
        
    /* MCG_C6: LOLIE=0,PLLS=1,CME=0,VDIV=0 */
    MCG_C6 = (uint8_t)0x40U;
    /* Wait until external reference clock is selected as MCG output */ 
    while((MCG_S & 0x0CU) != 0x08U);
    /* PBE mode */

    /* switch to PEE mode */    
    /* 配置PLL分频器来匹配所用的晶振,PLL来源为2 Mhz */
    MCG_C5 = MCG_C5_PRDIV(crystal_val);  

    /* 选择PLL VCO分频器，系统时钟分频器取决于时钟选项 */
    switch (clk_option) {
        case PLL_48MHZ:
            /* MCG=PLL, core = MCG, bus = MCG, FlexBus = MCG, Flash clock= MCG/2 */
            set_sys_dividers(0,0,0,1);
            /* 设置VCO分频器，使能PLL为48MHz, LOLIE=0, PLLS=1, CME=0, VDIV=0 */
            MCG_C6 = MCG_C6_PLLS_MASK; /* VDIV = 0 (x24) */
            pll_freq = 48000000;
            break;
        case PLL_50MHZ:
            /* MCG=PLL, core = MCG, bus = MCG, FlexBus = MCG, Flash clock= MCG/2 */
            set_sys_dividers(0,0,0,1);
            /* 设置VCO分频器，使能PLL为50MHz, LOLIE=0, PLLS=1, CME=0, VDIV=1 */
            MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(1); /* VDIV = 1 (x25) */
            pll_freq = 50000000;
            break;
        case PLL_96MHZ:
            /* MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/4 */
            set_sys_dividers(0,1,1,3);
            /* 设置VCO分频器，使能PLL为96MHz, LOLIE=0, PLLS=1, CME=0, VDIV=24 */
            MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(24); /* VDIV = 24 (x48) */
            pll_freq = 96000000;
            break;
        case PLL_100MHZ:
            /* MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/4 */
            set_sys_dividers(0,1,1,3);
            /* 设置VCO分频器，使能PLL为100MHz, LOLIE=0, PLLS=1, CME=0, VDIV=26 */
            MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(26); /* VDIV = 26 (x50) */
            pll_freq = 100000000;
            break;
        default:
            break;
    }
    /* wait for PLL status bit to set */
    while (!(MCG_S & MCG_S_PLLST_MASK));
    /* Wait for LOCK bit to set */
    while (!(MCG_S & MCG_S_LOCK_MASK)); 

    /* 通过清零CLKS位来进入PEE模式 */
    /* CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0 */
    MCG_C1 &= ~MCG_C1_CLKS_MASK;
    
    /* 等待时钟状态位更新 */
    /* Wait until output of the PLL is selected */
    while((MCG_S & 0x0CU) != 0x0CU);  
  
    /* 开始进入PEE模式 */
    
    return pll_freq;
}

/**
 * @brief 设置系系统分频器，此函数必须放在RAM里执行，否则会产生错误e2448。
 *        当FLASH时钟分频改变时，必须禁止FLASH的预取功能。在时钟分频改变之后，
 *        必须延时一小段时间才可以从新使能预取功能。
 *
 * @param mcg       内核时钟
 * @param sys_bus   系统总线时钟
 * @param flex_bus  外部总线时钟
 * @param flash     内部flash时钟
 */
static void set_sys_dividers(uint8_t mcg, uint8_t sys_bus, uint8_t flex_bus, uint8_t flash)
{
    uint32_t temp_reg;
    volatile uint8_t i;
    /* 保存FMC_PFAPR当前的值 */
    temp_reg = FMC_PFAPR;
    
    /* 通过M&PFD置位M0PFD来禁止预取功能 */
    FMC_PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | FMC_PFAPR_M5PFD_MASK
             | FMC_PFAPR_M4PFD_MASK | FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK
             | FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;
    
    /* 给时钟分频器设置期望值   */
    SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(mcg) | SIM_CLKDIV1_OUTDIV2(sys_bus) 
              | SIM_CLKDIV1_OUTDIV3(flex_bus) | SIM_CLKDIV1_OUTDIV4(flash);
    
    /* 等待分频器改变 */
    for (i = 0 ; i < flash ; i++);
    
    /* 从新存FMC_PFAPR的原始值 */
    FMC_PFAPR = temp_reg;

    return;
}


/**
 * @brief 跟踪时钟初始化
 */
static void trace_clk_init(void)
{
    /* 设置跟踪时钟为内核时钟 */
    SIM_SOPT2 |= SIM_SOPT2_TRACECLKSEL_MASK;
    /* 在PTA6引脚上使能TRACE_CLKOU功能 */
    PORTA_PCR6 = ( PORT_PCR_MUX(0x7));
}


/**
 * @brief FlexBus时钟初始化
 */
static void fb_clk_init(void)
{
    /* 使能FlexBus模块时钟 */
    SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
    /* 在PTA6引脚上使能FB_CLKOUT功能 */
    PORTC_PCR3 = ( PORT_PCR_MUX(0x5));
}
