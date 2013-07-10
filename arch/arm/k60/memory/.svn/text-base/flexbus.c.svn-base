/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     flexbus.c
 *
 *        @brief    SRAM initial
 *
 *        @version  0.1
 *        @date     2012/2/15 15:46:40
 *
 *        @author  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/2/15   create orignal file
 * =====================================================================================
 */
#include "flexbus.h"

/**
 *    @brief   FlexBus初始化
 *    @note   Configure the FlexBus Registers for 16-bit port size 
 *            with separate address and data using chip select 0
 *            Configure the pins needed to FlexBus Function (Alt 5 or 6)
 */
void flexbus_init(void)
{
	/* Set Base address */
	FB_CSAR0 = (uint32_t)&MRAM_START_ADDRESS;

	FB_CSCR0 =  FB_CSCR_PS(2)      /*  16-bit port */
			  | FB_CSCR_AA_MASK    /*  auto-acknowledge */
			  | FB_CSCR_ASET(0x1)  /*  assert chip select on second clock edge after address is asserted */
			  | FB_CSCR_WS(0x1)    /*  1 wait state - may need a wait state depending on the bus speed */
			  | FB_CSCR_BEM_MASK
			  | FB_CSCR_RDAH(1);
	
	
	FB_CSMR0  =   FB_CSMR_BAM(0x7)  /* Set base address mask for 512K address space */
			    | FB_CSMR_V_MASK;   /* Enable cs signal */

	/** enable BE signals - note, not used in this example */
	FB_CSPMCR = FB_CSPMCR_GROUP2(2) | FB_CSPMCR_GROUP3(2);
	
	/**
	 * address(1~18)
	 */
	PORTD_PCR8  = PORT_PCR_MUX(6);           /*  fb_a[16] */
	PORTD_PCR5  = PORT_PCR_MUX(5);           /*  fb_ad[1] */
	PORTD_PCR4  = PORT_PCR_MUX(5);           /*  fb_ad[2] */
	PORTD_PCR3  = PORT_PCR_MUX(5);           /*  fb_ad[3] */
	PORTD_PCR2  = PORT_PCR_MUX(5);           /*  fb_ad[4] */
	PORTC_PCR10 = PORT_PCR_MUX(5);           /*  fb_ad[5] */
	PORTC_PCR9  = PORT_PCR_MUX(5);           /*  fb_ad[6] */
	PORTC_PCR8  = PORT_PCR_MUX(5);           /*  fb_ad[7] */
	PORTC_PCR7  = PORT_PCR_MUX(5);           /*  fb_ad[8] */
	PORTC_PCR6  = PORT_PCR_MUX(5);           /*  fb_ad[9] */
	PORTB_PCR18 = PORT_PCR_MUX(5);           /*  fb_ad[15] */
	PORTC_PCR0  = PORT_PCR_MUX(5);           /*  fb_ad[14] */
	PORTC_PCR1  = PORT_PCR_MUX(5);           /*  fb_ad[13] */
	PORTC_PCR2  = PORT_PCR_MUX(5);           /*  fb_ad[12] */
	PORTC_PCR4  = PORT_PCR_MUX(5);           /*  fb_ad[11] */
	PORTC_PCR5  = PORT_PCR_MUX(5);           /*  fb_ad[10] */
	PORTD_PCR9  = PORT_PCR_MUX(6);           /*  fb_a[17] */
	PORTD_PCR10 = PORT_PCR_MUX(6);           /*  fb_a[18] */

	/**
	 * data(15~0)
	 */
	PORTB_PCR17 = PORT_PCR_MUX(5);           /*  fb_ad[16] used as d[15] */
	PORTB_PCR16 = PORT_PCR_MUX(5);           /*  fb_ad[17] used as d[14] */
	PORTB_PCR11 = PORT_PCR_MUX(5);           /*  fb_ad[18] used as d[13] */
	PORTB_PCR10 = PORT_PCR_MUX(5);           /*  fb_ad[19] used as d[12] */
	PORTB_PCR9  = PORT_PCR_MUX(5);           /*  fb_ad[20] used as d[11] */
	PORTB_PCR8  = PORT_PCR_MUX(5);           /*  fb_ad[21] used as d[10] */
	PORTB_PCR7  = PORT_PCR_MUX(5);           /*  fb_ad[22] used as d[9] */
	PORTB_PCR6  = PORT_PCR_MUX(5);           /*  fb_ad[23] used as d[8] */
	PORTB_PCR23 = PORT_PCR_MUX(5);           /*  fb_ad[28] used as d[7] */
	PORTB_PCR22 = PORT_PCR_MUX(5);           /*  fb_ad[29] used as d[6] */
	PORTB_PCR21 = PORT_PCR_MUX(5);           /*  fb_ad[30] used as d[5] */
	PORTB_PCR20 = PORT_PCR_MUX(5);           /*  fb_ad[31] used as d[4] */
	PORTC_PCR12 = PORT_PCR_MUX(5);           /*  fb_ad[27] used as d[3] */
	PORTC_PCR13 = PORT_PCR_MUX(5);           /*  fb_ad[26] used as d[2] */
	PORTC_PCR14 = PORT_PCR_MUX(5);           /*  fb_ad[25] used as d[1] */
	PORTC_PCR15 = PORT_PCR_MUX(5);           /*  fb_ad[24] used as d[0] */

	/**
	 *  control signals 
	 */
	PORTB_PCR19 = PORT_PCR_MUX(5);           /* fb_oe_b as SRAM_OE */
	PORTC_PCR11 = PORT_PCR_MUX(5);           /* fb_rw_b as SRAM_WE */
	PORTD_PCR1  = PORT_PCR_MUX(5);           /* fb_cs0_b as SRAM_CE */
}
