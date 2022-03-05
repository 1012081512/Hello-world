#include "spi.h"
#include <stdint.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"



//硬件SPI初始化
void n32_spi_init( void )
{
    SPI_InitType SPI_InitStruct;

    n32_msp_spi_init(SPI1);

    SPI_InitStruct.SpiMode      = SPI_MODE_MASTER;
    SPI_InitStruct.BaudRatePres = SPI_BR_PRESCALER_4;
    SPI_InitStruct.CLKPHA       = SPI_CLKPHA_FIRST_EDGE;
    SPI_InitStruct.CLKPOL       = SPI_CLKPOL_LOW;
    SPI_InitStruct.DataLen      = SPI_DATA_SIZE_8BITS;
    SPI_InitStruct.FirstBit     = SPI_FB_MSB;
    SPI_InitStruct.CRCPoly      = 7;
    SPI_InitStruct.DataDirection= SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStruct.NSS          = SPI_NSS_SOFT;
    SPI_Init(SPI1,&SPI_InitStruct);
    SPI_Enable(SPI1,ENABLE);

    rt_kprintf("SPI Initialization...\n");
}

uint8_t n32_spi_send_byte( uint8_t data )
{
    uint8_t count = 0;

    //BIT0 RNE   空为0 非空为1
    //BIT1 TX   非空为0  空为1
    //BIT7 BUSY 不忙为0 忙为1
    while((SPI1->STS & 0X02) == RESET )//等待上次数据发送完毕
    {
        count++;
        if(count > 200)
            return 0;
    }
    SPI_I2S_TransmitData(SPI1,data);
    count = 0;
    while((SPI1->STS & 0X01) == RESET )//等待接收缓冲区非空
    {
        count++;
        if(count > 200)
            return 0;
    }
    return SPI_I2S_ReceiveData(SPI1);
}





