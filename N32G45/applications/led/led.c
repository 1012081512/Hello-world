#include <stdint.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "led.h"


/* defined the LED1 pin: PB5 */
#define LED1_PIN    57


static void LED_Thread_entry( void* parameter )
{
    uint32_t Speed = 200;
    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);


    while(1)
    {
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(Speed);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(Speed);
    }
}





void LED_Thread_Config( void )
{
    rt_thread_t pin_thread = rt_thread_create("led_thread",
                                               LED_Thread_entry,
                                               RT_NULL,
                                               512,
                                               20,
                                               10);

    if(pin_thread != RT_NULL)
    {
        rt_thread_startup(pin_thread);
    }
}

//INIT_DEVICE_EXPORT(LED_Thread_Config);
