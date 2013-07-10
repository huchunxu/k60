/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     exception.c
 *
 *        @brief    exception management functions
 *
 *        @version  0.1
 *        @date     2011/12/30 16:00:41
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei 2011/12/30  create orignal file
 * =====================================================================================
 */
#include "exception.h"

#define DEFAULT_STKSZ 0x2000	/* 8KB */
static unsigned char system_stack[DEFAULT_STKSZ] __attribute((aligned(8)));
const unsigned char *  p_system_stack = &system_stack[DEFAULT_STKSZ];

extern void	__onchip_ram_end(void);
extern void system_start(void);
extern void nmi_handler(void);
extern void hard_fault_handler(void);
static void default_exc_handler(void);

__attribute__ ((aligned(512))) FP vector_table[128] =
{
	__onchip_ram_end,		  	  /* 0x0000_0000 0 -		  ARM core		  Initial MSP	 */
	system_start,				  /* 0x0000_0004 1 -          ARM core        Initial Program Counter */
	nmi_handler,                  /* 0x0000_0008 2 -          ARM core        Non-maskable Interrupt (NMI) */
	hard_fault_handler,           /* 0x0000_000C 3 -          ARM core        Hard Fault */
	default_exc_handler,          /* 0x0000_0010 4 - 										*/
	default_exc_handler,          /* 0x0000_0014 5 -          ARM core         Bus Fault */
	default_exc_handler,          /* 0x0000_0018 6 -          ARM core         Usage Fault */
	default_exc_handler,          /* 0x0000_001C 7 -                            */
	default_exc_handler,          /* 0x0000_0020 8 -                            */
	default_exc_handler,          /* 0x0000_0024 9 - */
	default_exc_handler,          /* 0x0000_0028 10 - */
	default_exc_handler,          /* 0x0000_002C 11 -         ARM core         Supervisor call (SVCall) */
	default_exc_handler,          /* 0x0000_0030 12 -         ARM core         Debug Monitor */
	default_exc_handler,          /* 0x0000_0034 13 -                           */
	default_exc_handler,          /* 0x0000_0038 14 -         ARM core         Pendable request for system service (PendableSrvReq) */
	default_exc_handler,          /* 0x0000_003C 15 -         ARM core         System tick timer (SysTick) */
	default_exc_handler,          /* 0x0000_0040 16     0     DMA              DMA Channel 0 transfer complete */
	default_exc_handler,          /* 0x0000_0044 17     1     DMA              DMA Channel 1 transfer complete */
	default_exc_handler,          /* 0x0000_0048 18     2     DMA              DMA Channel 2 transfer complete */
	default_exc_handler,          /* 0x0000_004C 19     3     DMA              DMA Channel 3 transfer complete */
	default_exc_handler,          /* 0x0000_0050 20     4     DMA              DMA Channel 4 transfer complete */
	default_exc_handler,          /* 0x0000_0054 21     5     DMA              DMA Channel 5 transfer complete */
	default_exc_handler,          /* 0x0000_0058 22     6     DMA              DMA Channel 6 transfer complete */
	default_exc_handler,          /* 0x0000_005C 23     7     DMA              DMA Channel 7 transfer complete */
	default_exc_handler,          /* 0x0000_0060 24     8     DMA              DMA Channel 8 transfer complete */
	default_exc_handler,          /* 0x0000_0064 25     9     DMA              DMA Channel 9 transfer complete */
	default_exc_handler,          /* 0x0000_0068 26    10     DMA              DMA Channel 10 transfer complete */
	default_exc_handler,          /* 0x0000_006C 27    11     DMA              DMA Channel 11 transfer complete */
	default_exc_handler,          /* 0x0000_0070 28    12     DMA              DMA Channel 12 transfer complete */
	default_exc_handler,          /* 0x0000_0074 29    13     DMA              DMA Channel 13 transfer complete */
	default_exc_handler,          /* 0x0000_0078 30    14     DMA              DMA Channel 14 transfer complete */
	default_exc_handler,          /* 0x0000_007C 31    15     DMA              DMA Channel 15 transfer complete */
	default_exc_handler,          /* 0x0000_0080 32    16     DMA              DMA Error Interrupt Channels 0-15 */
	default_exc_handler,          /* 0x0000_0084 33    17     MCM              Normal interrupt */
	default_exc_handler,          /* 0x0000_0088 34    18     Flash memory     Command Complete */
	default_exc_handler,          /* 0x0000_008C 35    19     Flash memory     Read Collision */
	default_exc_handler,          /* 0x0000_0090 36    20     Mode Controller  Low Voltage Detect,Low Voltage Warning, Low Leakage Wakeup */
	default_exc_handler,		  /* 0x0000_0094 37    21     LLWU */
	default_exc_handler,          /* 0x0000_0098 38    22     WDOG */
	default_exc_handler,          /* 0x0000_009C 39    23		 RNGB */
	default_exc_handler,          /* 0x0000_00A0 40    24     I2C0 */
	default_exc_handler,          /* 0x0000_00A4 41    25     I2C1 */
	default_exc_handler,          /* 0x0000_00A8 42    26     SPI0             Single interrupt vector for all sources */
	default_exc_handler,          /* 0x0000_00AC 43    27     SPI1             Single interrupt vector for all sources */
	default_exc_handler,          /* 0x0000_00B0 44    28     SPI2             Single interrupt vector for all sources */
	default_exc_handler,          /* 0x0000_00B4 45    29     CAN0             OR'ed Message buffer (0-15) */
	default_exc_handler,          /* 0x0000_00B8 46    30     CAN0             Bus Off */
	default_exc_handler,          /* 0x0000_00BC 47    31     CAN0             Error */
	default_exc_handler,          /* 0x0000_00C0 48    32     CAN0             Transmit Warning */
	default_exc_handler,          /* 0x0000_00C4 49    33     CAN0             Receive Warning */
	default_exc_handler,           /* 0x0000_00C8 50    34     CAN0             Wake Up */
	default_exc_handler,           /* 0x0000_00CC 51    35     CAN0             Individual Matching Elements Update (IMEU) */
	default_exc_handler,           /* 0x0000_00D0 52    36     CAN0             Lost receive */
	default_exc_handler,           /* 0x0000_00D4 53    37     CAN1             OR'ed Message buffer (0-15) */
	default_exc_handler,           /* 0x0000_00D8 54    38     CAN1             Bus off */
	default_exc_handler,           /* 0x0000_00DC 55    39     CAN1             Error */
	default_exc_handler,           /* 0x0000_00E0 56    40     CAN1             Transmit Warning */
	default_exc_handler,           /* 0x0000_00E4 57    41     CAN1             Receive Warning */
	default_exc_handler,           /* 0x0000_00E8 58    42     CAN1             Wake Up */
	default_exc_handler,           /* 0x0000_00EC 59    43     CAN1             Individual Matching Elements Update (IMEU) */
	default_exc_handler,           /* 0x0000_00F0 60    44     CAN1             Lost receive  */
	default_exc_handler,           /* 0x0000_00F4 61    45     UART0            Single interrupt vector for UART status sources */
	default_exc_handler,           /* 0x0000_00F8 62    46     UART0            Single interrupt vector for UART error sources */
	default_exc_handler,           /* 0x0000_00FC 63    47     UART1            Single interrupt vector for UART status sources */
	default_exc_handler,           /* 0x0000_0100 64    48     UART1            Single interrupt vector for UART error sources */
	default_exc_handler,           /* 0x0000_0104 65    49     UART2            Single interrupt vector for UART status sources */
	default_exc_handler,           /* 0x0000_0108 66    50     UART2            Single interrupt vector for UART error sources */
	default_exc_handler,          /* 0x0000_010C 67    51     UART3            Single interrupt vector for UART status sources */
	default_exc_handler,          /* 0x0000_0110 68    52     UART3            Single interrupt vector for UART error sources */
	default_exc_handler,           /* 0x0000_0114 69    53     UART4            Single interrupt vector for UART status sources */
	default_exc_handler,           /* 0x0000_0118 70    54     UART4            Single interrupt vector for UART error sources */
	default_exc_handler,           /* 0x0000_011C 71    55     UART5            Single interrupt vector for UART status sources */
	default_exc_handler,		  /* 0x0000_0120 72    56     UART5            Single interrupt vector for UART error  */
	default_exc_handler,          /* 0x0000_0124 73    57     ADC0 */
	default_exc_handler,          /* 0x0000_0128 74    58     ADC1 */
	default_exc_handler,          /* 0x0000_012C 75    59     CMP0             High-speed comparator  */
	default_exc_handler,          /* 0x0000_0130 76    60     CMP1 */
	default_exc_handler,          /* 0x0000_0134 77    61     CMP2 */
	default_exc_handler,          /* 0x0000_0138 78    62     FTM0 			 Single interrupt vector for all sources */
	default_exc_handler,          /* 0x0000_013C 79    63     FTM1 			 Single interrupt vector for all sources */
	default_exc_handler,          /* 0x0000_0140 80    64     FTM2 			 Single interrupt vector for all sources */
	default_exc_handler,          /* 0x0000_0144 81    65     CMT */
	default_exc_handler,          /* 0x0000_0148 82    66     RTC Timer interrupt */
	default_exc_handler,          /* 0x0000_014C 83    67 */
	default_exc_handler,          /* 0x0000_0150 84    68     PIT Channel 0 */
	default_exc_handler,          /* 0x0000_0154 85    69     PIT Channel 1 */
	default_exc_handler,          /* 0x0000_0158 86    70     PIT Channel 2 */
	default_exc_handler,          /* 0x0000_015C 87    71     PIT Channel 3 */
	default_exc_handler,          /* 0x0000_0160 88    72     PDB */
	default_exc_handler,          /* 0x0000_0164 89    73     USB OTG */
	default_exc_handler,          /* 0x0000_0168 90    74     USB Charger Detect */
	default_exc_handler,          /* 0x0000_016C 91    75		 ENET			 IEEE 1588 Timer interrupt			  */
	default_exc_handler,          /* 0x0000_0170 92    76		 ENET			 Transmit interrupt */
	default_exc_handler,          /* 0x0000_0174 93    77		 ENET			 Receive interrupt */
	default_exc_handler,          /* 0x0000_0178 94    78		 ENET			 Error and miscellaneous interrupt */
	default_exc_handler,          /* 0x0000_017C 95    79     I2S */
	default_exc_handler,          /* 0x0000_0180 96    80     SDHC */
	default_exc_handler,          /* 0x0000_0184 97    81     DAC0 */
	default_exc_handler,          /* 0x0000_0188 98    82     DAC1 */
	default_exc_handler,          /* 0x0000_018C 99    83     TSI 			 Single interrupt vector for all sources */
	default_exc_handler,          /* 0x0000_0190 100   84     MCG */
	default_exc_handler,          /* 0x0000_0194 101   85     Low Power Timer */
	default_exc_handler,          /* 0x0000_0198 102   86     Segment LCD 	 Single interrupt vector for all sources */
	default_exc_handler,		/* 0x0000_019C 103   87     Port control module Pin Detect (Port A) */
	default_exc_handler,        /* 0x0000_01A0 104   88     Port control module Pin Detect (Port B) */
	default_exc_handler,        /* 0x0000_01A4 105   89     Port control module Pin Detect (Port C) */
	default_exc_handler,        /* 0x0000_01A8 106   90     Port control module Pin Detect (Port D) */
	default_exc_handler,        /* 0x0000_01AC 107   91     Port control module Pin Detect (Port E) */
	default_exc_handler,		/* 0x0000_01B0 108   92  */
	default_exc_handler,        /* 0x0000_01B4 109   93  */
	default_exc_handler,        /* 0x0000_01B8 110   94  */
	default_exc_handler,        /* 0x0000_01BC 111   95  */
	default_exc_handler,        /* 0x0000_01C0 112   96  */
	default_exc_handler,        /* 0x0000_01C4 113   97  */
	default_exc_handler,        /* 0x0000_01C8 114   98  */
	default_exc_handler,        /* 0x0000_01CC 115   99  */
	default_exc_handler,        /* 0x0000_01D0 116   100 */
	default_exc_handler,        /* 0x0000_01D4 117   101 */
	default_exc_handler,        /* 0x0000_01D8 118   102 */
	default_exc_handler,        /* 0x0000_01DC 119   103 */
	default_exc_handler,
	default_exc_handler,
	default_exc_handler,
	default_exc_handler,
	default_exc_handler,
	default_exc_handler,
	default_exc_handler,
	default_exc_handler,	    /* 127 */
};


/**
 * @brief 
 */
void nmi_handler(void)
{
	while(1);
}


/**
 * @brief 
 */
void hard_fault_handler(void)
{
	while(1);
}


/**
 * @brief 
 */
void default_exc_handler(void)
{
	while(1);
}


/**
 * @brief install an exception handler
 *
 * @param excno exception no.	
 * @param exchdr exception handler
 */
void exc_install(uint32_t excno, FP exchdr)
{
	 *(((FP*)vector_table) + excno) = exchdr;
}


/**
 * @brief set the priority of exception
 *
 * @param excno	exception no.
 * @param pri	exception priority
 */
void exc_set_pri(uint32_t excno, uint8_t pri)
{
	if (excno <= 15 && excno >= 4) {	/* system excepitons */
		*((volatile uint8_t *)(0xE000ED18 + excno)) = (pri & 0xF) << 4;
	}	
	else if (excno > 15) {	/* target define exceptions */
		NVIC_IP(excno) = (pri & 0xF) << 4;
	}
}


/**
 * @brief enable exception
 *
 * @param excno exception no
 */
void exc_enable(uint32_t excno)
{
	uint32_t div;
	uint32_t bits;

	if (excno > 15)
	{
		/* 将中断向量号转换为中断请求号 */
		excno -= 16;

		div = excno / 32;
		bits = excno % 32;

		switch (div)
    	{
    		case 0x0:
              NVICICPR0 = 1 << bits;
              NVICISER0 = 1 << bits;
              break;
    		case 0x1:
              NVICICPR1 = 1 << bits;
              NVICISER1 = 1 << bits;
              break;
    		case 0x2:
              NVICICPR2 = 1 << bits;
              NVICISER2 = 1 << bits;
			case 0x3:
			  NVICICPR3 = 1 << bits;
              NVICISER3 = 1 << bits; 
              break;
   		}
	}/* end if */
	else
	{
		switch (excno)
		{
			case INT_Reserved4:
				SCB_SHCSR |= SCB_SHCSR_MEMFAULTENA_MASK;
				break;
			case INT_Bus_Fault:
				SCB_SHCSR |= SCB_SHCSR_BUSFAULTENA_MASK;
				break;
			case INT_Usage_Fault:
				SCB_SHCSR |= SCB_SHCSR_USGFAULTENA_MASK;
				break;
		}
	}/* end else */
	
}


/**
 * @brief disable exception
 *
 * @param excno exception no
 */
void exc_disable(uint32_t excno)
{
	uint32_t div;
	uint32_t bits;

	if (excno > 15) {
	    /* 将中断向量号转换为中断请求号 */
	    excno -= 16;
	    
		div = excno / 32;
		bits = excno % 32;

		switch (div)
    	{
    		case 0x0:
              NVICISER0 = 1 << bits;
              break;
    		case 0x1:
              NVICISER1 = 1 << bits;
              break;
    		case 0x2:
              NVICISER2 = 1 << bits;
			case 0x3:
              NVICISER3 = 1 << bits; 
              break;
    	}
	}
	else {
		switch (excno) {
			case INT_Reserved4:
				SCB_SHCSR &= ~SCB_SHCSR_MEMFAULTENA_MASK;
				break;
			case INT_Bus_Fault:
				SCB_SHCSR &= ~SCB_SHCSR_BUSFAULTENA_MASK;
				break;
			case INT_Usage_Fault:
				SCB_SHCSR &= ~SCB_SHCSR_USGFAULTENA_MASK;
				break;
		}
	}		
}

/**
 * @brief set exception vector table
 *
 * @param vector address of vector table
 */
void exc_set_vector(void * vector)
{
	SCB_VTOR = (uint32_t)vector;
}



/**
 * @brief init exceptions
 */
void exc_init(void) 
{
	//SCB_AIRCR |= SCB_AIRCR_PRIGROUP(3) | SCB_AIRCR_VECTKEY(0x05FA);  
	exc_set_vector((void *)vector_table);
	set_basepri(0x0);
	exc_set_pri(INT_Reserved4,0x0);
	exc_set_pri(INT_Bus_Fault,0x0);
	exc_set_pri(INT_Usage_Fault,0x0);
	exc_set_pri(INT_DebugMonitor,0x0);
	exc_set_pri(INT_PendableSrvReq,0x0);
	exc_set_pri(INT_SVCall,0x0);
	clear_faultmask();
	clear_primask();
}
