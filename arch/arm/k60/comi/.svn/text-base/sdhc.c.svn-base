/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     sdhc.h
 *
 *        @brief    sdhc构件源文件
 *
 *        @version  0.1
 *        @date     2012/4/4  21:57:42
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/4    create orignal file
 * =====================================================================================
 */
#include "sdhc.h"

SDCARD_STRUCT 		SDHC_Card;

/**
 *    @brief   SDHC命令，包括每条命令执行时的XFERTYP寄存器各个域的设置
 */
static const unsigned long ESDHC_COMMAND_XFERTYP[] = 
{
	// CMD0
    SDHC_XFERTYP_CMDINX(ESDHC_CMD0) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD1) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD2) | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD3) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD4) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
    // CMD5 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD5) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD6) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD7) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD8) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD9) | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136),
    // CMD10 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD10) | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD11) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD12) | SDHC_XFERTYP_CMDTYP(ESDHC_XFERTYP_CMDTYP_ABORT) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD13) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    0,
    // CMD15 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD15) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD16) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD17) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD18) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    0,
    // CMD20 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD20) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    0,
    SDHC_XFERTYP_CMDINX(ESDHC_ACMD22) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_ACMD23) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD24) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    // CMD25 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD25) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD26) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD27) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD28) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD29) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    // CMD30 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD30) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    0,
    SDHC_XFERTYP_CMDINX(ESDHC_CMD32) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD33) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD34) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    // CMD35 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD35) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD36) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD37) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD38) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD39) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    // CMD40 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD40) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_ACMD41) | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD42) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    0,
    0,
    // CMD45 
    0,
    0,
    0,
    0,
    0,
    // CMD50 
    0,
    SDHC_XFERTYP_CMDINX(ESDHC_ACMD51) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD52) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD53) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    0,
    // CMD55 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD55) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD56) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    0,
    0,
    0,
    // CMD60 
    SDHC_XFERTYP_CMDINX(ESDHC_CMD60) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    SDHC_XFERTYP_CMDINX(ESDHC_CMD61) | SDHC_XFERTYP_CICEN_MASK | SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY),
    0,
    0
};
static void SDHC_set_baudrate(uint32_t clock, uint32_t baudrate);
static uint8_t SDHC_is_running(void);
static uint32_t SDHC_status_wait(uint32_t mask);
static uint32_t SDHC_send_command (ESDHC_COMMAND_STRUCT_PTR command);

/**
 *    @brief   初始化SDHC模块
 *
 *    @param   coreClk 内核时钟                                                    
 *    @param   baud    SDHC通信频率 
 *
 *    @return  
 *         - ESDHC_OK 成功时返回
 *         - 其他      返回值为错误。
 */
uint32_t sdhc_init(uint32_t coreClk, uint32_t baud)					
{
	SDHC_Card.CARD_TYPE = ESDHC_CARD_NONE;
	
    //使能SDHC模块的时钟门
    SIM_SCGC3 |= SIM_SCGC3_SDHC_MASK;
    
	//复位SDHC
    SDHC_SYSCTL = SDHC_SYSCTL_RSTA_MASK | SDHC_SYSCTL_SDCLKFS(0x80);    
    while (SDHC_SYSCTL & SDHC_SYSCTL_RSTA_MASK){};
    
    //初始化SDHC相关寄存器
    SDHC_VENDOR = 0;
    SDHC_BLKATTR = SDHC_BLKATTR_BLKCNT(1) | SDHC_BLKATTR_BLKSIZE(512);
    SDHC_PROCTL = SDHC_PROCTL_EMODE(ESDHC_PROCTL_EMODE_INVARIANT) 
                | SDHC_PROCTL_D3CD_MASK; 
    SDHC_WML = SDHC_WML_RDWML(1) | SDHC_WML_WRWML(1);
    
    //设置SDHC模块的通信速率
    SDHC_set_baudrate (coreClk,baud);
    
    //检查CMD通道和DAT通道是否准备就绪
    while (SDHC_PRSSTAT & (  SDHC_PRSSTAT_CIHB_MASK 
                           | SDHC_PRSSTAT_CDIHB_MASK)){};

    //设置复用引脚功能为SDHC
    PORTE_PCR(0) = 0xFFFF & (   PORT_PCR_MUX(4) 
                              | PORT_PCR_PS_MASK 
                              | PORT_PCR_PE_MASK 
                              | PORT_PCR_DSE_MASK); // ESDHC.D1  
    PORTE_PCR(1) = 0xFFFF & (   PORT_PCR_MUX(4) 
                              | PORT_PCR_PS_MASK 
                              | PORT_PCR_PE_MASK 
                              | PORT_PCR_DSE_MASK); // ESDHC.D0  
    PORTE_PCR(2) = 0xFFFF & (   PORT_PCR_MUX(4) 
                              | PORT_PCR_DSE_MASK); // ESDHC.CLK 
    PORTE_PCR(3) = 0xFFFF & (   PORT_PCR_MUX(4) 
                              | PORT_PCR_PS_MASK 
                              | PORT_PCR_PE_MASK 
                              | PORT_PCR_DSE_MASK); // ESDHC.CMD 
    PORTE_PCR(4) = 0xFFFF & (   PORT_PCR_MUX(4) 
                              | PORT_PCR_PS_MASK 
                              | PORT_PCR_PE_MASK 
                              | PORT_PCR_DSE_MASK); // ESDHC.D3  
    PORTE_PCR(5) = 0xFFFF & (   PORT_PCR_MUX(4) 
                              | PORT_PCR_PS_MASK 
                              | PORT_PCR_PE_MASK 
                              | PORT_PCR_DSE_MASK);  // ESDHC.D2  
    
    //清除SDHC模块的中断标志
    SDHC_IRQSTAT = 0xFFFF;
    //使能中断位
    SDHC_IRQSTATEN = SDHC_IRQSTATEN_DEBESEN_MASK 
                   | SDHC_IRQSTATEN_DCESEN_MASK 
                   | SDHC_IRQSTATEN_DTOESEN_MASK 
                   | SDHC_IRQSTATEN_CIESEN_MASK 
                   | SDHC_IRQSTATEN_CEBESEN_MASK 
                   | SDHC_IRQSTATEN_CCESEN_MASK 
                   | SDHC_IRQSTATEN_CTOESEN_MASK 
                   | SDHC_IRQSTATEN_BRRSEN_MASK 
                   | SDHC_IRQSTATEN_BWRSEN_MASK 
                   | SDHC_IRQSTATEN_CRMSEN_MASK
                   | SDHC_IRQSTATEN_TCSEN_MASK 
                   | SDHC_IRQSTATEN_CCSEN_MASK;
    
    //80个时钟周期的初始化
    SDHC_SYSCTL |= SDHC_SYSCTL_INITA_MASK;
    while (SDHC_SYSCTL & SDHC_SYSCTL_INITA_MASK){};

    //检查卡是否已经插入
    if (SDHC_PRSSTAT & SDHC_PRSSTAT_CINS_MASK)
    {
    	SDHC_Card.CARD_TYPE = ESDHC_CARD_UNKNOWN;
    }
    SDHC_IRQSTAT |= SDHC_IRQSTAT_CRM_MASK;
    
    return ESDHC_OK;
}

/**
 *    @brief   接收n个字节 
 *
 *    @param   buff    接收缓冲区                                                     
 *    @param   btr     接收长度  
 *
 *    @return  
 *         - 1   成功
 *         - 0   失败
 */
uint32_t sdhc_receive_block (uint8_t *buff,uint32_t btr)
{
    uint32_t  bytes, i, j;
    uint32_t  *ptr = (uint32_t*)buff;
    
    //当可识别的卡插入后，接收数据前，检测DAT通道是否忙（正在使用中）
    if (    (SDHC_Card.CARD_TYPE == ESDHC_CARD_SD) 
         || (SDHC_Card.CARD_TYPE == ESDHC_CARD_SDHC) 
         || (SDHC_Card.CARD_TYPE == ESDHC_CARD_MMC) 
         || (SDHC_Card.CARD_TYPE == ESDHC_CARD_CEATA))
    {
        while (SDHC_PRSSTAT & SDHC_PRSSTAT_DLA_MASK){};
    }    
    
    //读取数据时，每次读取4个字节
    bytes = btr;
    while (bytes)
    {
        i = bytes > 512 ? 512 : bytes;
        for (j = (i + 3) >> 2; j != 0; j--)
        {
            if (SDHC_IRQSTAT & (    SDHC_IRQSTAT_DEBE_MASK 
                                  | SDHC_IRQSTAT_DCE_MASK 
                                  | SDHC_IRQSTAT_DTOE_MASK))
            {
                SDHC_IRQSTAT |= SDHC_IRQSTAT_DEBE_MASK 
                              | SDHC_IRQSTAT_DCE_MASK 
                              | SDHC_IRQSTAT_DTOE_MASK 
                              | SDHC_IRQSTAT_BRR_MASK;
                return 0;
            }
            
            while (0 == (SDHC_PRSSTAT & SDHC_PRSSTAT_BREN_MASK)){};

            *ptr++ = SDHC_DATPORT;
        }
        bytes -= i;
    }
    
	return 1;						// Return with success     
}

/**
 *    @brief   发送n个字节
 *
 *    @param   buff    接收缓冲区                                                     
 *    @param   btr     接收长度  
 *
 *    @return  
 *         - 1   成功
 *         - 0   失败
 */
uint32_t sdhc_send_block (const uint8_t *buff,uint32_t btr)
{
    uint32_t  bytes, i;
    uint32_t  *ptr = (uint32_t*)buff;

    //读取数据时，每次读取4个字节
    bytes = btr;
    while (bytes)
    {
        i = bytes > 512 ? 512 : bytes;
        bytes -= i;
        for (i = (i + 3) >> 2; i != 0; i--)
        {
            if (SDHC_IRQSTAT & (    SDHC_IRQSTAT_DEBE_MASK 
                                  | SDHC_IRQSTAT_DCE_MASK 
                                  | SDHC_IRQSTAT_DTOE_MASK))
            {
            	SDHC_IRQSTAT |= SDHC_IRQSTAT_DEBE_MASK 
            	              | SDHC_IRQSTAT_DCE_MASK 
            	              | SDHC_IRQSTAT_DTOE_MASK 
            	              | SDHC_IRQSTAT_BWR_MASK;
                return 0;
            }
            while (0 == (SDHC_PRSSTAT & SDHC_PRSSTAT_BWEN_MASK)){};

            SDHC_DATPORT = *ptr++;

        }
    }
	return 1;
}

/**
 *    @brief   配置SDHC模块
 *
 *    @param   cmd          配置命令                                               
 *    @param   param_ptr     数据指针  
 *
 *    @return  
 *         - ESDHC_OK 成功时返回
 *         - 其他      返回值为错误。
 */
uint32_t sdhc_ioctl(uint32_t cmd, void *param_ptr)
{
    ESDHC_COMMAND_STRUCT    command; 
    uint8_t   mem, io, mmc, ceata, mp, hc; //标志当前卡类型
    uint32_t  i, val;
    uint32_t  result = ESDHC_OK;
    uint32_t  *param32_ptr = param_ptr;
    
    switch (cmd) 
    {
        //初始化SD卡读写系统
        case IO_IOCTL_ESDHC_INIT:        	
            result = sdhc_init (CORE_CLOCK_HZ, BAUD_RATE_HZ);
            if (ESDHC_OK != result)
            {
                break;
            }
            
            mem = FALSE;
            io = FALSE;
            mmc = FALSE;
            ceata = FALSE;
            hc = FALSE;
            mp = FALSE;

            //CMD0,使得SD卡进入空闲模式，复位SD卡
            command.COMMAND = ESDHC_CMD0;
            command.TYPE = ESDHC_TYPE_NORMAL;
            command.ARGUMENT = 0;
            command.READ = FALSE;
            command.BLOCKS = 0;
            if (SDHC_send_command (&command))
            {
                result = ESDHC_ERROR_INIT_FAILED;
                break;
            }
            
            for(i = 0;i < 2000000;i++)
            {
            }

            //CMD8
            command.COMMAND = ESDHC_CMD8;
            command.TYPE = ESDHC_TYPE_NORMAL;
            command.ARGUMENT = 0x000001AA;
            command.READ = FALSE;
            command.BLOCKS = 0;
            val = SDHC_send_command (&command);
            
            if (val == 0)
            {
                // SDHC卡
            	if (command.RESPONSE[0] != command.ARGUMENT)
                {
                    result = ESDHC_ERROR_INIT_FAILED;
                    break;
                }
                hc = TRUE;
            }

            mp = TRUE;
            
            if (mp)
            {
                //CMD55，检查是否为MMC卡
                command.COMMAND = ESDHC_CMD55;
                command.TYPE = ESDHC_TYPE_NORMAL;
                command.ARGUMENT = 0;
                command.READ = FALSE;
                command.BLOCKS = 0;
                val = SDHC_send_command (&command);
                if (val > 0)
                {
                    result = ESDHC_ERROR_INIT_FAILED;
                    break;
                }
                if (val < 0)
                {
                    // MMC 或 CE-ATA
                    io = FALSE;
                    mem = FALSE;
                    hc = FALSE;
                    
                    //CMD1
                    command.COMMAND = ESDHC_CMD1;
                    command.TYPE = ESDHC_TYPE_NORMAL;
                    command.ARGUMENT = 0x40300000;
                    command.READ = FALSE;
                    command.BLOCKS = 0;
                    if (SDHC_send_command (&command))
                    {
                        result = ESDHC_ERROR_INIT_FAILED;
                        break;
                    }
                    if (0x20000000 == (command.RESPONSE[0] & 0x60000000))
                    {
                        hc = TRUE;
                    }
                    mmc = TRUE;

                    //CMD39
                    command.COMMAND = ESDHC_CMD39;
                    command.TYPE = ESDHC_TYPE_NORMAL;
                    command.ARGUMENT = 0x0C00;
                    command.READ = FALSE;
                    command.BLOCKS = 0;
                    if (SDHC_send_command (&command))
                    {
                        result = ESDHC_ERROR_INIT_FAILED;
                        break;
                    }
                    if (0xCE == ((command.RESPONSE[0] >> 8) & 0xFF))
                    {
                        //CMD39
                        command.COMMAND = ESDHC_CMD39;
                        command.TYPE = ESDHC_TYPE_NORMAL;
                        command.ARGUMENT = 0x0D00;
                        command.READ = FALSE;
                        command.BLOCKS = 0;
                        if (SDHC_send_command (&command))
                        {
                            result = ESDHC_ERROR_INIT_FAILED;
                            break;
                        }
                        if (0xAA == ((command.RESPONSE[0] >> 8) & 0xFF))
                        {
                            mmc = FALSE;
                            ceata = TRUE;
                        }
                    }
                }
                else
                {
                    //当为SD卡时
                    // ACMD41
                    command.COMMAND = ESDHC_ACMD41;
                    command.TYPE = ESDHC_TYPE_NORMAL;
                    command.ARGUMENT = 0;
                    command.READ = FALSE;
                    command.BLOCKS = 0;
                    if (SDHC_send_command (&command))
                    {
                        result = ESDHC_ERROR_INIT_FAILED;
                        break;
                    }
                    if (command.RESPONSE[0] & 0x300000)
                    {
                        val = 0;
                        do 
                        {
                            for(i = 0;i < 500000;i++)
                            {
                            }
                            val++;
                            
                            // CMD55 + ACMD41 - Send OCR 
                            command.COMMAND = ESDHC_CMD55;
                            command.TYPE = ESDHC_TYPE_NORMAL;
                            command.ARGUMENT = 0;
                            command.READ = FALSE;
                            command.BLOCKS = 0;
                            if (SDHC_send_command (&command))
                            {
                                result = ESDHC_ERROR_INIT_FAILED;
                                break;
                            }

                            command.COMMAND = ESDHC_ACMD41;
                            command.TYPE = ESDHC_TYPE_NORMAL;
                            if (hc)
                            {
                                command.ARGUMENT = 0x40300000;
                            }
                            else
                            {
                                command.ARGUMENT = 0x00300000;
                            }
                            command.READ = FALSE;
                            command.BLOCKS = 0;
                            if (SDHC_send_command (&command))
                            {
                                result = ESDHC_ERROR_INIT_FAILED;
                                break;
                            }
                        } while ((0 == (command.RESPONSE[0] & 0x80000000)) && (val < 10));
                        if (ESDHC_OK != result)
                        {
                            break;
                        }
                        if (val >= 10)
                        {
                            hc = FALSE;
                        }
                        else
                        {
                            mem = TRUE;
                            if (hc)
                            {
                                hc = FALSE;
                                if (command.RESPONSE[0] & 0x40000000)
                                {
                                    hc = TRUE;
                                }
                            }
                        }
                    }
                }
            }
            
            
            if (mmc)
            {
            	SDHC_Card.CARD_TYPE = ESDHC_CARD_MMC;
            }
            if (ceata)
            {
            	SDHC_Card.CARD_TYPE = ESDHC_CARD_CEATA;
            }
            if (io)
            {
            	SDHC_Card.CARD_TYPE = ESDHC_CARD_SDIO;
            }
            if (mem)
            {
            	SDHC_Card.CARD_TYPE = ESDHC_CARD_SD;
                if (hc)
                {
                	SDHC_Card.CARD_TYPE = ESDHC_CARD_SDHC;
                }
            }
            if (io && mem)
            {
            	SDHC_Card.CARD_TYPE = ESDHC_CARD_SDCOMBO;
                if (hc)
                {
                	SDHC_Card.CARD_TYPE = ESDHC_CARD_SDHCCOMBO;
                }
            }

            /*
            //清除引脚复用寄存器
            PORTE_PCR(0) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D1  
            PORTE_PCR(1) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D0  
            PORTE_PCR(2) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_DSE_MASK);                                          // ESDHC.CLK 
            PORTE_PCR(3) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.CMD 
            PORTE_PCR(4) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D3  
            PORTE_PCR(5) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D2  

            //设置SDHC模块的波特率
            SDHC_set_baudrate (CORE_CLOCK_HZ, BAUD_RATE_HZ);

            //设置复用引脚功能为SDHC
            PORTE_PCR(0) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D1  
            PORTE_PCR(1) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D0  
            PORTE_PCR(2) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_DSE_MASK);                                          // ESDHC.CLK 
            PORTE_PCR(3) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.CMD 
            PORTE_PCR(4) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D3  
            PORTE_PCR(5) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D2  

            //使能SDHC模块的时钟
            SIM_SCGC3 |= SIM_SCGC3_SDHC_MASK;
            */
            break;
        //向卡发送命令
        case IO_IOCTL_ESDHC_SEND_COMMAND:
            val = SDHC_send_command ((ESDHC_COMMAND_STRUCT_PTR)param32_ptr);
            if (val > 0)
            {
                result = ESDHC_ERROR_COMMAND_FAILED;
            }
            if (val < 0)
            {
                result = ESDHC_ERROR_COMMAND_TIMEOUT;
            }
            break;
        //获取当前通信波特率状态
        case IO_IOCTL_ESDHC_GET_BAUDRATE:
            if (NULL == param32_ptr) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else 
            {
                //获取当前设置的波特率
                val = ((SDHC_SYSCTL & SDHC_SYSCTL_SDCLKFS_MASK) >> SDHC_SYSCTL_SDCLKFS_SHIFT) << 1;
                val *= ((SDHC_SYSCTL & SDHC_SYSCTL_DVS_MASK) >> SDHC_SYSCTL_DVS_SHIFT) + 1;
                *param32_ptr = (uint32_t)(CORE_CLOCK_HZ / val);
            }
            break;
        //设定当前通信波特率状态
        case IO_IOCTL_ESDHC_SET_BAUDRATE:
            if (NULL == param32_ptr) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else if (0 == (*param32_ptr)) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else 
            {
                if (! SDHC_is_running())
                {
                	//清除引脚复用寄存器
                    PORTE_PCR(0) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D1  
                    PORTE_PCR(1) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D0  
                    PORTE_PCR(2) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_DSE_MASK);                                          // ESDHC.CLK 
                    PORTE_PCR(3) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.CMD 
                    PORTE_PCR(4) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D3  
                    PORTE_PCR(5) = 0 & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D2  

                    //设置SDHC模块的波特率
                    SDHC_set_baudrate (CORE_CLOCK_HZ, *param32_ptr);

                    //设置复用引脚功能为SDHC
                    PORTE_PCR(0) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D1  
                    PORTE_PCR(1) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D0  
                    PORTE_PCR(2) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_DSE_MASK);                                          // ESDHC.CLK 
                    PORTE_PCR(3) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.CMD 
                    PORTE_PCR(4) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D3  
                    PORTE_PCR(5) = 0xFFFF & (PORT_PCR_MUX(4) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK);    // ESDHC.D2  

                    //使能SDHC模块的时钟
                    SIM_SCGC3 |= SIM_SCGC3_SDHC_MASK;
                }
                else
                {
                    result = IO_ERROR_DEVICE_BUSY;
                }
            }
            break;
        //获取块长度
        case IO_IOCTL_ESDHC_GET_BLOCK_SIZE:
            if (NULL == param32_ptr) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else 
            {
                //获取SDHC模块设置的块的大小
                *param32_ptr = (SDHC_BLKATTR & SDHC_BLKATTR_BLKSIZE_MASK) >> SDHC_BLKATTR_BLKSIZE_SHIFT;
            }       
            break;
        //设定块长度
        case IO_IOCTL_ESDHC_SET_BLOCK_SIZE:
            if (NULL == param32_ptr) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else 
            {
                //设置SDHC模块处理的块的大小
                if (! SDHC_is_running())
                {
                    if (*param32_ptr > 0x0FFF)
                    {
                        result = IO_ERROR_INVALID_PARAMETER;
                    }
                    else
                    {
                        SDHC_BLKATTR &= (~ SDHC_BLKATTR_BLKSIZE_MASK); 
                        SDHC_BLKATTR |= SDHC_BLKATTR_BLKSIZE(*param32_ptr);
                    }
                }
                else
                {
                    result = IO_ERROR_DEVICE_BUSY;
                }
            }       
            break;
        //获取卡通信总线位宽
        case IO_IOCTL_ESDHC_GET_BUS_WIDTH:
            if (NULL == param32_ptr) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else 
            {
                //获取当前配置的SDHC模块的总线宽度
                val = (SDHC_PROCTL & SDHC_PROCTL_DTW_MASK) >> SDHC_PROCTL_DTW_SHIFT;
                if (ESDHC_PROCTL_DTW_1BIT == val)
                {
                    *param32_ptr = ESDHC_BUS_WIDTH_1BIT;
                }
                else if (ESDHC_PROCTL_DTW_4BIT == val)
                {
                    *param32_ptr = ESDHC_BUS_WIDTH_4BIT;
                }
                else if (ESDHC_PROCTL_DTW_8BIT == val)
                {
                    *param32_ptr = ESDHC_BUS_WIDTH_8BIT;
                }
                else
                {
                    result = ESDHC_ERROR_INVALID_BUS_WIDTH; 
                }
            }       
            break;
        //设定卡通信总线位宽
        case IO_IOCTL_ESDHC_SET_BUS_WIDTH:
            if (NULL == param32_ptr) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else 
            {
            	//设置SDHC模块的总线宽度
                if (! SDHC_is_running())
                {
                    if (ESDHC_BUS_WIDTH_1BIT == *param32_ptr)
                    {
                        SDHC_PROCTL &= (~ SDHC_PROCTL_DTW_MASK);
                        SDHC_PROCTL |= SDHC_PROCTL_DTW(ESDHC_PROCTL_DTW_1BIT);
                    }
                    else if (ESDHC_BUS_WIDTH_4BIT == *param32_ptr)
                    {
                        SDHC_PROCTL &= (~ SDHC_PROCTL_DTW_MASK);
                        SDHC_PROCTL |= SDHC_PROCTL_DTW(ESDHC_PROCTL_DTW_4BIT);
                    }
                    else if (ESDHC_BUS_WIDTH_8BIT == *param32_ptr)
                    {
                        SDHC_PROCTL &= (~ SDHC_PROCTL_DTW_MASK);
                        SDHC_PROCTL |= SDHC_PROCTL_DTW(ESDHC_PROCTL_DTW_8BIT);
                    }
                    else
                    {
                        result = ESDHC_ERROR_INVALID_BUS_WIDTH; 
                    }
                }
                else
                {
                    result = IO_ERROR_DEVICE_BUSY;
                }
            }       
            break;
        //获取卡当前状态
        case IO_IOCTL_ESDHC_GET_CARD:
            if (NULL == param32_ptr) 
            {
                result = IO_ERROR_INVALID_PARAMETER;
            } 
            else 
            {
                //等待80个时钟
                SDHC_SYSCTL |= SDHC_SYSCTL_INITA_MASK;
                while (SDHC_SYSCTL & SDHC_SYSCTL_INITA_MASK){};
                    
                //读取SD卡返回的状态
                if (SDHC_IRQSTAT & SDHC_IRQSTAT_CRM_MASK)
                {
                    SDHC_IRQSTAT |= SDHC_IRQSTAT_CRM_MASK;
                    SDHC_Card.CARD_TYPE = ESDHC_CARD_NONE;
                }
                if (SDHC_PRSSTAT & SDHC_PRSSTAT_CINS_MASK)
                {
                    if (ESDHC_CARD_NONE == SDHC_Card.CARD_TYPE)
                    {
                    	SDHC_Card.CARD_TYPE = ESDHC_CARD_UNKNOWN;
                    }
                }
                else
                {
                	SDHC_Card.CARD_TYPE = ESDHC_CARD_NONE;
                }
                *param32_ptr = SDHC_Card.CARD_TYPE;
            }
            break;
        default:
            result = IO_ERROR_INVALID_IOCTL_CMD;
            break;
    }
    return result;
}

/**
 *    @brief   设置SDHC模块的时钟
 *
 *    @param   clock        系统时钟                                                   
 *    @param   baudrate     波特率  
 */
static void SDHC_set_baudrate(uint32_t clock,uint32_t baudrate)
{
	uint32_t i, pres, div, min, minpres = 0x80, mindiv = 0x0F;
	int32_t  val;

    //找到相近的分频因子
    min = (uint32_t)-1;
    for (pres = 2; pres <= 256; pres <<= 1) 
    {
        for (div = 1; div <= 16; div++) 
        {
            val = pres * div * baudrate - clock;
            if (val >= 0)
            {
                if (min > val) 
                {
                    min = val;
                    minpres = pres;
                    mindiv = div;
                }
            }
        }
    }

    //禁止SDHC模块时钟
    SDHC_SYSCTL &= (~ SDHC_SYSCTL_SDCLKEN_MASK);

    //修改分频因子
    div = SDHC_SYSCTL & (~ (SDHC_SYSCTL_DTOCV_MASK | SDHC_SYSCTL_SDCLKFS_MASK | SDHC_SYSCTL_DVS_MASK));
    SDHC_SYSCTL = div | (SDHC_SYSCTL_DTOCV(0x0E) | SDHC_SYSCTL_SDCLKFS(minpres >> 1) | SDHC_SYSCTL_DVS(mindiv - 1));

    //等在时钟稳定
    while (0 == (SDHC_PRSSTAT & SDHC_PRSSTAT_SDSTB_MASK))
    {
		for(i = 0;i < 200000;i++)
		{
		}
    };

    //使能SDHC模块时钟
    SDHC_SYSCTL |= SDHC_SYSCTL_SDCLKEN_MASK;
    SDHC_IRQSTAT |= SDHC_IRQSTAT_DTOE_MASK;
}

/**
 *    @brief   检测SDHC模块是否忙 
 *    
 *    @return  
 *         - 0   其他
 *         - 1   正忙
 */
static uint8_t SDHC_is_running(void)
{
    return (0 != (SDHC_PRSSTAT & (SDHC_PRSSTAT_RTA_MASK | SDHC_PRSSTAT_WTA_MASK | SDHC_PRSSTAT_DLA_MASK | SDHC_PRSSTAT_CDIHB_MASK | SDHC_PRSSTAT_CIHB_MASK)));
}   

/**
 *    @brief   等待中断标志位置位    
 *
 *    @param   mask  待不断的标志位掩码 
 *
 *    @return  返回传入的数
 */
static uint32_t SDHC_status_wait(uint32_t mask)
{
    uint32_t	result;
    do
    {
        result = SDHC_IRQSTAT & mask;
    } 
    while (0 == result);
    return result;
}

/**
 *    @brief   发送命令   
 *
 *    @param   command   命令结构体指针
 *
 *    @return  
 *         - 0   成功
 *         - 1   错误
 *         - -1  超时
 */
static uint32_t SDHC_send_command (ESDHC_COMMAND_STRUCT_PTR command)
{
    uint32_t	xfertyp;//Transfer Type Register (SDHC_XFERTYP)
    
    //检查和配置命令
    xfertyp = ESDHC_COMMAND_XFERTYP[command->COMMAND & 0x3F];
    if ((0 == xfertyp) && (0 != command->COMMAND))
    {
        return 1;
    }

    //卡移除检测
    SDHC_IRQSTAT |= SDHC_IRQSTAT_CRM_MASK;

    //等待CMD通道空闲
    while (SDHC_PRSSTAT & SDHC_PRSSTAT_CIHB_MASK){};

    //设置传输类型寄存器参数
    //写命令参数寄存器(Command Argument Register，SDHC_CMDARG)
    SDHC_CMDARG = command->ARGUMENT;
    //清除XFERTYP寄存器的命令类型域
    xfertyp &= (~ SDHC_XFERTYP_CMDTYP_MASK);
    //设置XFERTYP寄存器的命令类型域
    xfertyp |= SDHC_XFERTYP_CMDTYP(command->TYPE);
    //如果为恢复类型
    if (ESDHC_TYPE_RESUME == command->TYPE)
    {
    	//如果命令类型为恢复CMD52写功能选择，则置数据传送选择位。
        xfertyp |= SDHC_XFERTYP_DPSEL_MASK;
    }
    //如果是切换忙类型
    if (ESDHC_TYPE_SWITCH_BUSY == command->TYPE)
    {
    	
        if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) == SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48))
        {
            xfertyp &= (~ SDHC_XFERTYP_RSPTYP_MASK);
            xfertyp |= SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY);
        }
        else
        {
            xfertyp &= (~ SDHC_XFERTYP_RSPTYP_MASK);
            xfertyp |= SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48);
        }
    }
    //清除块数
    SDHC_BLKATTR &= (~ SDHC_BLKATTR_BLKCNT_MASK);
    //块数判断
    if (0 != command->BLOCKS)
    {
    	//块不为0
        if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) != SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_48BUSY))
        {
            xfertyp |= SDHC_XFERTYP_DPSEL_MASK;
        }
        if (command->READ)
        {
            xfertyp |= SDHC_XFERTYP_DTDSEL_MASK;    
        }
        if (command->BLOCKS > 1)
        {
            xfertyp |= SDHC_XFERTYP_MSBSEL_MASK;    
        }
        if ((uint32_t)-1 != command->BLOCKS)
        {
        	SDHC_BLKATTR |= SDHC_BLKATTR_BLKCNT(command->BLOCKS);
            xfertyp |= SDHC_XFERTYP_BCEN_MASK;
        }
    }

    //执行命令
    SDHC_DSADDR = 0;
    SDHC_XFERTYP = xfertyp;
    
    //等待状态寄存器置位
    if (SDHC_status_wait (SDHC_IRQSTAT_CIE_MASK | SDHC_IRQSTAT_CEBE_MASK | SDHC_IRQSTAT_CCE_MASK | SDHC_IRQSTAT_CC_MASK) != SDHC_IRQSTAT_CC_MASK)
    {
    	SDHC_IRQSTAT |= SDHC_IRQSTAT_CTOE_MASK | SDHC_IRQSTAT_CIE_MASK | SDHC_IRQSTAT_CEBE_MASK | SDHC_IRQSTAT_CCE_MASK | SDHC_IRQSTAT_CC_MASK;
        return 1;
    }

    //检测卡是否被移除
    if (SDHC_IRQSTAT & SDHC_IRQSTAT_CRM_MASK)
    {
    	SDHC_IRQSTAT |= SDHC_IRQSTAT_CTOE_MASK | SDHC_IRQSTAT_CC_MASK;
        return 1;
    }

    //检查命令是否超时
    if (SDHC_IRQSTAT & SDHC_IRQSTAT_CTOE_MASK)
    {
    	SDHC_IRQSTAT |= SDHC_IRQSTAT_CTOE_MASK | SDHC_IRQSTAT_CC_MASK;
        return -1;
    }
    if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) != SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_NO))
    {
        command->RESPONSE[0] = SDHC_CMDRSP(0);
        if ((xfertyp & SDHC_XFERTYP_RSPTYP_MASK) == SDHC_XFERTYP_RSPTYP(ESDHC_XFERTYP_RSPTYP_136))
        {
            command->RESPONSE[1] = SDHC_CMDRSP(1);
            command->RESPONSE[2] = SDHC_CMDRSP(2);
            command->RESPONSE[3] = SDHC_CMDRSP(3);
        }
    }
    
    SDHC_IRQSTAT |= SDHC_IRQSTAT_CC_MASK;

    return 0;
}

