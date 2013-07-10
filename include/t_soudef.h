/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     t_soudef.h
 *
 *        @brief    单片机资源编码定义
 *
 *        @version  0.1
 *        @date     2011/3/21 21:32:45
 *
 *        @author:  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2011/3/21   create orignal file
 * =====================================================================================
 */

#ifndef T_SOUDEF_H_
#define T_SOUDEF_H_


/**
 * 内核模块定义
 */
#define  CORE_MODULE     0x00
#define  NVIC_CONTROL    0x01
#define  WIC_CONTROL     0x02

/**
 * 系统模块定义
 */
#define  SYSTEM_MODULE   0x10
#define  CLK_CONTROL     0x11
#define  PMC_CONTROL     0x12
#define  DMA_CONTROL     0x13
#define  EMW_MONITOR     0x14

/**
 * 存储器和存储器接口定义
 */
#define  MEMORY_MODULE   0x20
#define  FLEX_MEM        0x21
#define  FLEX_BUS        0x22
#define  EZ_PORT         0x23
#define  DDR_CONTROL     0x24
#define  NAND_CONTROL    0x25

/**
 * 定时器模块
 */
#define  TIMER_MODULE    0x30
#define  FTM_TIMER       0x31
#define  PIT_TIMER       0x32
#define  LPTMR_TIMER     0x33
#define  CMT_TIMER       0x34
#define  RTC_TIMER       0x35

/**
 * 通讯模块定义
 */
#define  COMMU_MODULE    0x40
#define  UART_INTERF     0x41
#define  SPI_INTERF      0x42
#define  IIC_INTERF      0x43
#define  IIS_INTERF      0x44
#define  SDHC_INTERF     0x45
#define  CAN_INTERF      0x46
#define  USB_INTERF      0x47

/**
 * 人机接口模块定义
 */
#define  INTERF_MODULE    0x50
#define  GPIO_INTERF      0x51
#define  TSI_INTERF       0x52

/**
 * 模拟模块定义
 */
#define  ADC0_MODULE    0x60
#define  ADC1_MODULE    0x61


/**
 * FTM功能模块定义
 */
#define   FTM0           0x3100
#define   FTM0_CH0       0x3101
#define   FTM0_CH1       0x3102
#define   FTM0_CH2       0x3103
#define   FTM0_CH3       0x3104
#define   FTM0_CH4       0x3105
#define   FTM0_CH5       0x3106
#define   FTM0_CH6       0x3107
#define   FTM0_CH7       0x3108

#define   FTM1           0x3110
#define   FTM1_CH0       0x3111
#define   FTM1_CH1       0x3112

#define   FTM2           0x3120
#define   FTM2_CH0       0x3121
#define   FTM2_CH1       0x3122

#define   FTM_MOD_GET(ftm_module)         ((ftm_module & 0x00f0) >> 4)     /**< 获取ftm模块号 */
#define   FTM_CH_GET(ftm_module)          ((ftm_module & 0x000f)-1)        /**< 获取ftm通道号 */
#define   FTM_MOD_SET(ftm_module)         ((ftm_module << 4) | (FTM_TIMER << 8))                       /**< 设置ftm模块号 */
#define   FTM_CH_SET(ftm_module,ftm_ch)   ((ftm_module << 4) | (FTM_TIMER << 8) | (ftm_ch +1))        /**< 设置ftm通道号 */

/**
 * PIT功能模块定义
 */
#define  PIT_TIMER0       0x3200
#define  PIT_TIMER1       0x3201
#define  PIT_TIMER2       0x3202
#define  PIT_TIMER3       0x3203

#define  PIT_NO_GET(pit_mod)   (pit_mod & 0x00ff)
#define  PIT_ID_SET(pit_no)    ((PIT_TIMER << 8) | pit_no)

/**
 * LPTMR功能模块定义
 */
#define   LPTMR    0x3300

/**
 * UART功能模块定义
 */
#define   UART0      0x4100
#define   UART1      0x4104
#define   UART2      0x4102
#define   UART3      0x4103
#define   UART4      0x4101
#define   UART5      0x4105

#define   UART_NO_GET(siopid)   (siopid & 0x00ff)                 /**< 获取串口号 */
#define   UART_ID_SET(siopno)   (siopno | (UART_INTERF << 8))     /**< 设置串口号 */

/**
 * AD功能模块定义
 */
#define ADC0 0x6000
#define ADC1 0x6100

#define ADC0_CH0  0x6001
#define ADC0_CH1  0x6002
#define ADC0_CH2  0x6003
#define ADC0_CH3  0x6004
#define ADC0_CH4  0x6005
#define ADC0_CH5  0x6006
#define ADC0_CH6  0x6007
#define ADC0_CH7  0x6008
#define ADC0_CH8  0x6009
#define ADC0_CH9  0x600a
#define ADC0_CH10 0x600b
#define ADC0_CH11 0x600c
#define ADC0_CH12 0x600d
#define ADC0_CH13 0x600e
#define ADC0_CH14 0x600f
#define ADC0_CH15 0x6010
#define ADC0_CH16 0x6011
#define ADC0_CH17 0x6012
#define ADC0_CH18 0x6013
#define ADC0_CH19 0x6014
#define ADC0_CH20 0x6015
#define ADC0_CH21 0x6016
#define ADC0_CH22 0x6017
#define ADC0_CH23 0x6018

#define ADC1_CH0  0x6101
#define ADC1_CH1  0x6102
#define ADC1_CH2  0x6103
#define ADC1_CH3  0x6104
#define ADC1_CH4  0x6105
#define ADC1_CH5  0x6106
#define ADC1_CH6  0x6107
#define ADC1_CH7  0x6108
#define ADC1_CH8  0x6109
#define ADC1_CH9  0x610a
#define ADC1_CH10 0x610b
#define ADC1_CH11 0x610c
#define ADC1_CH12 0x610d
#define ADC1_CH13 0x610e
#define ADC1_CH14 0x610f
#define ADC1_CH15 0x6110
#define ADC1_CH16 0x6111
#define ADC1_CH17 0x6112
#define ADC1_CH18 0x6113
#define ADC1_CH19 0x6114
#define ADC1_CH20 0x6115
#define ADC1_CH21 0x6116
#define ADC1_CH22 0x6117
#define ADC1_CH23 0x6118

#define   ADC_NO_GET(adc_id)      ((adc_id & 0x0f00) >> 8)  
#define   ADC_ID_SET(adc_no)      (( adc_no << 8)|0x6000)            
#define   ADC_CH_GET(adc_id)        ((adc_id & 0x00ff) - 1)        
#define   ADC_MOD_CH_SET(adc_no, ch)  ((ch + 1) | ( adc_no << 8 ) | 0x6000)

/**
 * SPI模块定义
 */
#define   SPI0       0x4200
#define   SPI1       0x4201
#define   SPI2       0x4202

#define   SPI_NO_GET(spi_id)      (spi_id & 0x00ff)
#define   SPI_MOD_SET(spino)      ((SPI_INTERF << 8) | spino)
/**
 * 单片机端口定义
 */
#define   PTA        0x0100
#define   PTB        0x0200
#define   PTC        0x0300
#define   PTD        0x0400
#define   PTE        0x0500

/**
 * 端口A的引脚定义
 */
#define   PTA0        0x0101
#define   PTA1        0x0102
#define   PTA2        0x0103
#define   PTA3        0x0104
#define   PTA4        0x0105
#define   PTA5        0x0106
#define   PTA6        0x0107
#define   PTA7        0x0108
#define   PTA8        0x0109
#define   PTA9        0x010a
#define   PTA10       0x010b
#define   PTA11       0x010c
#define   PTA12       0x010d
#define   PTA13       0x010e
#define   PTA14       0x010f
#define   PTA15       0x0110
#define   PTA16       0x0111
#define   PTA17       0x0112
#define   PTA18       0x0113
#define   PTA19       0x0114
#define   PTA20       0x0115
#define   PTA21       0x0116
#define   PTA22       0x0117
#define   PTA23       0x0118
#define   PTA24       0x0119
#define   PTA25       0x011a
#define   PTA26       0x011b
#define   PTA27       0x011c
#define   PTA28       0x011d
#define   PTA29       0x011e
#define   PTA30       0x011f
#define   PTA31       0x0120

/**
 * 端口B的引脚定义
 */
#define   PTB0        0x0201
#define   PTB1        0x0202
#define   PTB2        0x0203
#define   PTB3        0x0204
#define   PTB4        0x0205
#define   PTB5        0x0206
#define   PTB6        0x0207
#define   PTB7        0x0208
#define   PTB8        0x0209
#define   PTB9        0x020a
#define   PTB10       0x020b
#define   PTB11       0x020c
#define   PTB12       0x020d
#define   PTB13       0x020e
#define   PTB14       0x020f
#define   PTB15       0x0210
#define   PTB16       0x0211
#define   PTB17       0x0212
#define   PTB18       0x0213
#define   PTB19       0x0214
#define   PTB20       0x0215
#define   PTB21       0x0216
#define   PTB22       0x0217
#define   PTB23       0x0218
#define   PTB24       0x0219
#define   PTB25       0x021a
#define   PTB26       0x021b
#define   PTB27       0x021c
#define   PTB28       0x021d
#define   PTB29       0x021e
#define   PTB30       0x021f
#define   PTB31       0x0220

/**
 * 端口C的引脚定义
 */
#define   PTC0        0x0301
#define   PTC1        0x0302
#define   PTC2        0x0303
#define   PTC3        0x0304
#define   PTC4        0x0305
#define   PTC5        0x0306
#define   PTC6        0x0307
#define   PTC7        0x0308
#define   PTC8        0x0309
#define   PTC9        0x030a
#define   PTC10       0x030b
#define   PTC11       0x030c
#define   PTC12       0x030d
#define   PTC13       0x030e
#define   PTC14       0x030f
#define   PTC15       0x0310
#define   PTC16       0x0311
#define   PTC17       0x0312
#define   PTC18       0x0313
#define   PTC19       0x0314
#define   PTC20       0x0315
#define   PTC21       0x0316
#define   PTC22       0x0317
#define   PTC23       0x0318
#define   PTC24       0x0319
#define   PTC25       0x031a
#define   PTC26       0x031b
#define   PTC27       0x031c
#define   PTC28       0x031d
#define   PTC29       0x031e
#define   PTC30       0x031f
#define   PTC31       0x0320

/**
 * 端口D的引脚定义
 */
#define   PTD0        0x0401
#define   PTD1        0x0402
#define   PTD2        0x0403
#define   PTD3        0x0404
#define   PTD4        0x0405
#define   PTD5        0x0406
#define   PTD6        0x0407
#define   PTD7        0x0408
#define   PTD8        0x0409
#define   PTD9        0x040a
#define   PTD10       0x040b
#define   PTD11       0x040c
#define   PTD12       0x040d
#define   PTD13       0x040e
#define   PTD14       0x040f
#define   PTD15       0x0410
#define   PTD16       0x0411
#define   PTD17       0x0412
#define   PTD18       0x0413
#define   PTD19       0x0414
#define   PTD20       0x0415
#define   PTD21       0x0416
#define   PTD22       0x0417
#define   PTD23       0x0418
#define   PTD24       0x0419
#define   PTD25       0x041a
#define   PTD26       0x041b
#define   PTD27       0x041c
#define   PTD28       0x041d
#define   PTD29       0x041e
#define   PTD30       0x041f
#define   PTD31       0x0420

/**
 * 端口E的引脚定义
 */
#define   PTE0        0x0501
#define   PTE1        0x0502
#define   PTE2        0x0503
#define   PTE3        0x0504
#define   PTE4        0x0505
#define   PTE5        0x0506
#define   PTE6        0x0507
#define   PTE7        0x0508
#define   PTE8        0x0509
#define   PTE9        0x050a
#define   PTE10       0x050b
#define   PTE11       0x050c
#define   PTE12       0x050d
#define   PTE13       0x050e
#define   PTE14       0x050f
#define   PTE15       0x0510
#define   PTE16       0x0511
#define   PTE17       0x0512
#define   PTE18       0x0513
#define   PTE19       0x0514
#define   PTE20       0x0515
#define   PTE21       0x0516
#define   PTE22       0x0517
#define   PTE23       0x0518
#define   PTE24       0x0519
#define   PTE25       0x051a
#define   PTE26       0x051b
#define   PTE27       0x051c
#define   PTE28       0x051d
#define   PTE29       0x051e
#define   PTE30       0x051f
#define   PTE31       0x0520

/**
 * 引脚编码宏定义
 */
#define   PORT_NO_GET(port)      (((port & 0xff00) >> 8)-1)   /**< 端口号获取 */
#define   PORT_ID_SET(port)      ((port + 1) << 8)            /**< 端口ID设置 */
#define   PIN_NO_GET(pin)        ((pin & 0x00ff) - 1)         /**< 引脚号获取 */
#define   PIN_ID_SET(port, pin)  ((pin + 1) | port)           /**< 引脚ID设置 */

#endif /* T_SOUDEF_H_ */
