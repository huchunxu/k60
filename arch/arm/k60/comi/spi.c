/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     spi.c
 *
 *        @brief    spi总线驱动函数
 *
 *        @version  0.1
 *        @date     2012/4/23 21:30
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/4/23   create orignal file
 * =====================================================================================
 */
#include "spi.h"
#include "gpio.h"
#include "exception.h"

SPI_MemMapPtr spi_get_base_address(uint8_t spino);


/**
 *    @brief  SPI初始化
 * 
 *    @param   spino   SPI通道号
 *    @param   master  是否是主机  
 *    
 *    @return  E_ID    输入序号错误
 *    @return  E_OK    初始化正常
 */
ER spi_init(uint8_t spino, uint8_t master)
{
    if((spino < 0) || (spino > SPI_NO_GET(SPI2)))
    {
        return (E_ID);
    }
    
    SPI_MemMapPtr base_addr = spi_get_base_address(spino);
    
    /* 使能SPI模块时钟，配置SPI引脚功能 */
    if(SPI_MOD_SET(spino) == SPI0)
    {
        SIM_SCGC6 |= SIM_SCGC6_DSPI0_MASK;
        
        /* PORT_PCR_MUX(0x2) ： SPI功能
         * PORT_PCR_DSE_MASK ： Drive Strength Enable */
        gpio_init(PORT_NO_GET(SD_CS), PIN_NO_GET(SD_CS), OUT_PUT, HIGH_POWER);   /* PCS0 */
        PORTA_PCR15 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SCK */
        PORTA_PCR16 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SOUT */
        PORTA_PCR17 = 0 | PORT_PCR_MUX(0x2);                     /* SIN */
    }
    else if(SPI_MOD_SET(spino) == SPI1)
    {
        SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;
        PORTE_PCR4 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* PCS0 */
        PORTE_PCR2 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SCK */
        PORTE_PCR1 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SOUT */
        PORTE_PCR3 = 0 | PORT_PCR_MUX(0x2);                     /* SIN */
    }
    else 
    {
        SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;
    }
    
    SPI_MCR_REG(base_addr) = 0 
                 | SPI_MCR_CLR_TXF_MASK     /* Clear the Tx FIFO counter. */
                 | SPI_MCR_CLR_RXF_MASK     /* Clear the Rx FIFO counter. */
                 | SPI_MCR_HALT_MASK;       /* Starts and stops DSPI transfers */

    /* 根据主从机模式设置工作模式 */
    if(master == MASTER)
    {
        SPI_MCR_REG(base_addr) |= SPI_MCR_MSTR_MASK;   /* Master/Slave Mode Select */
     
        SPI_CTAR_REG(base_addr,0) = 0
                       | SPI_CTAR_DBR_MASK         /* Double Baud Rate */
                       | SPI_CTAR_FMSZ(0x07)       /* Frame Size： 8bit */
                       | SPI_CTAR_PDT_MASK         /* 延时因子为7 */
                       | SPI_CTAR_BR(0x8);         /* Selects the scaler value for the baud rate.  */
                       //| SPI_CTAR_CPOL_MASK;     /* Clock Polarity */
                       //| SPI_CTAR_CPHA_MASK;     /* Clock Phase */
    }
    else
    {
        SPI_CTAR_SLAVE_REG(base_addr,0) = 0 
                            | SPI_CTAR_SLAVE_FMSZ(0x07)
                            | SPI_CTAR_SLAVE_CPOL_MASK 
                            | SPI_CTAR_SLAVE_CPHA_MASK; 
   }
 
   SPI_SR_REG(base_addr) = SPI_SR_EOQF_MASK    /* End of Queue Flag */
                         | SPI_SR_TFUF_MASK      /* Transmit FIFO Underflow Flag */
                         | SPI_SR_TFFF_MASK      /* Transmit FIFO Fill Flag */
                         | SPI_SR_RFOF_MASK      /* Receive FIFO Overflow Flag */
                         | SPI_SR_RFDF_MASK;    /* Receive FIFO Drain Flag */
    
    SPI_MCR_REG(base_addr) &= ~SPI_MCR_HALT_MASK;   /* start */
    
    return (E_OK);
}

/**
 *    @brief  SPI初始化(快速)
 * 
 *    @param   spino   SPI通道号
 *    @param   master  是否是主机  
 *    
 *    @return  E_ID    输入序号错误
 *    @return  E_OK    初始化正常
 */
ER spi_init_fast(uint8_t spino, uint8_t master)
{
    if((spino < 0) || (spino > SPI_NO_GET(SPI2)))
    {
        return (E_ID);
    }
    
    SPI_MemMapPtr base_addr = spi_get_base_address(spino);
    
    /* 使能SPI模块时钟，配置SPI引脚功能 */
    if(SPI_MOD_SET(spino) == SPI0)
    {
        SIM_SCGC6 |= SIM_SCGC6_DSPI0_MASK;
        
        /* PORT_PCR_MUX(0x2) ： SPI功能
         * PORT_PCR_DSE_MASK ： Drive Strength Enable */
        gpio_init(PORT_NO_GET(SD_CS), PIN_NO_GET(SD_CS), OUT_PUT, HIGH_POWER);   /* PCS0 */
        PORTA_PCR15 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SCK */
        PORTA_PCR16 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SOUT */
        PORTA_PCR17 = 0 | PORT_PCR_MUX(0x2);                     /* SIN */
    }
    else if(SPI_MOD_SET(spino) == SPI1)
    {
        SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;
        PORTE_PCR4 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* PCS0 */
        PORTE_PCR2 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SCK */
        PORTE_PCR1 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK; /* SOUT */
        PORTE_PCR3 = 0 | PORT_PCR_MUX(0x2);                     /* SIN */
    }
    else 
    {
        SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;
    }
    
    SPI_MCR_REG(base_addr) = 0 
                 | SPI_MCR_CLR_TXF_MASK     /* Clear the Tx FIFO counter. */
                 | SPI_MCR_CLR_RXF_MASK     /* Clear the Rx FIFO counter. */
                 | SPI_MCR_HALT_MASK;       /* Starts and stops DSPI transfers */

    /* 根据主从机模式设置工作模式 */
    if(master == MASTER)
    {
        SPI_MCR_REG(base_addr) |= SPI_MCR_MSTR_MASK;   /* Master/Slave Mode Select */
     
        SPI_CTAR_REG(base_addr,0) = 0
                       | SPI_CTAR_DBR_MASK         /* Double Baud Rate */
                       | SPI_CTAR_FMSZ(0x07)       /* Frame Size： 8bit */
                       | SPI_CTAR_PDT_MASK         /* 延时因子为7 */
                       | SPI_CTAR_BR(0x0);         /* Selects the scaler value for the baud rate.  */
                       //| SPI_CTAR_CPOL_MASK;     /* Clock Polarity */
                       //| SPI_CTAR_CPHA_MASK;     /* Clock Phase */
    }
    else
    {
        SPI_CTAR_SLAVE_REG(base_addr,0) = 0 
                            | SPI_CTAR_SLAVE_FMSZ(0x07)
                            | SPI_CTAR_SLAVE_CPOL_MASK 
                            | SPI_CTAR_SLAVE_CPHA_MASK; 
   }
 
   SPI_SR_REG(base_addr) = SPI_SR_EOQF_MASK    /* End of Queue Flag */
                         | SPI_SR_TFUF_MASK      /* Transmit FIFO Underflow Flag */
                         | SPI_SR_TFFF_MASK      /* Transmit FIFO Fill Flag */
                         | SPI_SR_RFOF_MASK      /* Receive FIFO Overflow Flag */
                         | SPI_SR_RFDF_MASK;    /* Receive FIFO Drain Flag */
    
    SPI_MCR_REG(base_addr) &= ~SPI_MCR_HALT_MASK;   /* start */
    
    return (E_OK);
}

/**
 *    @brief  SPI发送数据
 * 
 *    @param   spino   SPI通道号
 *    @param   data[]  需要发送的数据  
 *    @param   len     需要发送的数据 
 */
void spi_snd(uint8_t spino, uint8_t data[], uint32_t len)
{
    uint32_t i = 0;
    SPI_MemMapPtr base_addr = spi_get_base_address(spino);
        
    SPI_SR_REG(base_addr) = (SPI_SR_EOQF_MASK
         | SPI_SR_TFUF_MASK
         | SPI_SR_TFFF_MASK
         | SPI_SR_RFOF_MASK
         | SPI_SR_RFDF_MASK);
    
    SPI_MCR_REG(base_addr) |= SPI_MCR_CLR_TXF_MASK    /* Clear TX FIFO */
                            | SPI_MCR_CLR_RXF_MASK;   /* Clears the RX Counter */
    
    for (i = 0; i < len; i++)
    {
        if (i == (len - 1))
        {
            SPI_PUSHR_REG(base_addr) = 0 
                    | SPI_PUSHR_CTAS(0)            /* Clock and Transfer Attributes Select */
                    | SPI_PUSHR_EOQ_MASK           /* End Of Queue */
                    | SPI_PUSHR_TXDATA(data[i]);   /* Transmit Data */
        }
        else
        {
            SPI_PUSHR_REG(base_addr) = 0 
                    | SPI_PUSHR_CONT_MASK
                    | SPI_PUSHR_CTAS(0) 
                    | SPI_PUSHR_TXDATA(data[i]);
        }
    }
    
    /* 等待数据发送完毕 */
    while((SPI_SR_REG(base_addr) & SPI_SR_TCF_MASK)==0);
    SPI_SR_REG(base_addr) |= SPI_SR_TCF_MASK;
}

/**
 *    @brief   SPI接收数据
 * 
 *    @param   spino   SPI通道号
 *    @param   data[]  需要发送的数据  
 *    
 *    @return  1     成功
 *    @return  0     失败
 */
uint8_t spi_rcv(uint8_t spino, uint8_t data[])
{
      SPI_MemMapPtr base_addr = spi_get_base_address(spino);

      if(SPI_SR_REG(base_addr) & SPI_SR_RFDF_MASK)    /* Rx FIFO is not empty */
      {
              data[0] = (uint8_t)SPI_POPR_REG(base_addr);      /* Received Data */           
              SPI_SR_REG(base_addr) |= SPI_SR_RFDF_MASK;       /* The RFDF bit can be cleared by writing 1  */
              return 1;
      }
      SPI_SR_REG(base_addr) = (SPI_SR_EOQF_MASK
               | SPI_SR_TFUF_MASK
               | SPI_SR_TFFF_MASK
               | SPI_SR_RFOF_MASK
               | SPI_SR_RFDF_MASK);

      SPI_MCR_REG(base_addr) |= SPI_MCR_CLR_TXF_MASK     /* Clear the Tx FIFO counter. */
                             | SPI_MCR_CLR_RXF_MASK;     /* Clear the Rx FIFO counter. */
      
      return 0;
}


/**
 *    @brief   开SPI接收中断
 * 
 *    @param   spino   SPI通道号
 */
void spi_enable_rcv_int(uint8_t spino)
{
    SPI_MemMapPtr base_addr = spi_get_base_address(spino);
    BSET(SPI_RSER_RFDF_RE_SHIFT, SPI_RSER_REG(base_addr));/* 开放SPI接收中断 */
    exc_enable(spino + INT_SPI0);             /* 开接收引脚的IRQ中断 */
}

/**
 *    @brief   关SPI接收中断
 * 
 *    @param   spino   SPI通道号
 */
void spi_disable_rcv_int(uint8_t spino)
{
    SPI_MemMapPtr base_addr = spi_get_base_address(spino);
    BCLR(SPI_RSER_RFDF_RE_SHIFT, SPI_RSER_REG(base_addr));/* 关闭SPI接收中断 */
    exc_disable(spino + INT_SPI0);             /* 开接收引脚的IRQ中断 */
}

/**
 *    @brief   将SPI通道号转换成对应基指针
 * 
 *    @param   spino   SPI通道号
 *    
 *    @return  SPI通道基址
 */
SPI_MemMapPtr spi_get_base_address(uint8_t spino)
{
    uint16_t spi_mod;
    
    spi_mod = SPI_MOD_SET(spino);
    
    switch(spi_mod)
    {
        case SPI0:
           return SPI0_BASE_PTR;
        case SPI1:
           return SPI1_BASE_PTR;
        case SPI2:
           return SPI2_BASE_PTR;
        default:
           return 0;
    }
}
