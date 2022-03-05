/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <stdint.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "led.h"
#include "spi.h"
#include "lcd.h"




int main(void)
{
    LED_Thread_Config();
    LCD_Init();
    LCD_thread_create();


    while (1)
    {
        rt_thread_delay(500);
    }
}

