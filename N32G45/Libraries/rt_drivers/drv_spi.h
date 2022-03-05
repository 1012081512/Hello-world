#ifndef __DRV_SPI_H
#define __DRV_SPI_H

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_Module* cs_gpiox, uint16_t cs_gpio_pin);

struct n32_hw_spi_cs
{
    GPIO_Module* GPIOx;
    uint16_t GPIO_Pin;
};

struct n32_spi_config
{
    SPI_Module *Instance;
    char *bus_name;
    struct dma_config *dma_rx, *dma_tx;
};

struct n32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};

#define SPI_USING_RX_DMA_FLAG   (1<<0)
#define SPI_USING_TX_DMA_FLAG   (1<<1)

/* n32 spi dirver class */
struct n32_spi
{
    // SPI_HandleTypeDef handle;
    struct n32_spi_config *config;
    struct rt_spi_configuration *cfg;

    // struct
    // {
    //     DMA_HandleTypeDef handle_rx;
    //     DMA_HandleTypeDef handle_tx;
    // } dma;

    rt_uint8_t spi_dma_flag;
    struct rt_spi_bus spi_bus;
};





#endif /*__DRV_SPI_H*/

