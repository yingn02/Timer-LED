#include <ch32v00x.h>
#include "debug.h"
#include "ram.h"
#include "spi.h"
#include "color_data.h"



void strobe() 
{
    if(led.ms != 0) //strobe on/off
    {
        strobe_cnt++;

        if(strobe_cnt < led.ms) 
        {
            strobe_on_flag = 1; //on
        }
        else if (led.ms <= strobe_cnt && strobe_cnt < led.ms*2) 
        {
            strobe_on_flag = 0; //off
        }
        else //strobe_cnt >= led.s*2
        {
            strobe_cnt = 0;
        }
    }
    else if(led.ms == 0) //if 0, always on
    {
        strobe_on_flag = 1;
    }
    
    if(LED_TYPE == PWM) 
    {
        if(strobe_on_flag == 1)
        {
            TIM_SetCompare3(TIM1, led.r); //red
            TIM_SetCompare4(TIM1, led.g); //green
            TIM_SetCompare1(TIM1, led.b); //blue   
        }
        else if(strobe_on_flag == 0)
        {
            TIM_SetCompare3(TIM1, 0); //red
            TIM_SetCompare4(TIM1, 0); //green
            TIM_SetCompare1(TIM1, 0); //blue
        }
    }
    else if(LED_TYPE == SPI) 
    {
        if(strobe_on_flag == 1) 
        {
            set_color_data(color_data, led.r, led.g, led.b);
            spi_write(color_data);
        }
        else if(strobe_on_flag == 0)
        {
            set_color_data(color_data, 0, 0, 0);
            spi_write(color_data);
        }

    }

}



void dimming() 
{
    if(dimming_direction == 1) //increase brightness
    {
        dimming_cnt++;
    }
    else if(dimming_direction == 2) //decrease brightness
    {
        dimming_cnt--;
    }

    r_dimming_brightness = (led.r*dimming_cnt)/led.ms;
    g_dimming_brightness = (led.g*dimming_cnt)/led.ms;
    b_dimming_brightness = (led.b*dimming_cnt)/led.ms;

    //When brightness is minimum or maximum, turn
    if(r_dimming_brightness <= 0 && g_dimming_brightness <= 0 && b_dimming_brightness <= 0)
    {
        dimming_direction = 1;
    }
    else if(r_dimming_brightness >= led.r && g_dimming_brightness >= led.g && b_dimming_brightness >= led.b)
    {
        dimming_direction = 2;
    }
    
    if(LED_TYPE == PWM) 
    {
        TIM_SetCompare3(TIM1, r_dimming_brightness); //red
        TIM_SetCompare4(TIM1, g_dimming_brightness); //green
        TIM_SetCompare1(TIM1, b_dimming_brightness); //blue
    }
    else if (LED_TYPE == SPI)
    {
        set_color_data(color_data, r_dimming_brightness, g_dimming_brightness, b_dimming_brightness);
        spi_write(color_data);
    }
}



void streaming() 
{
    streaming_color_cnt++;

    if(streaming_color_cnt >= led.ms) //led can reach to next color every (led.s)ms
    { 
        streaming_color_cnt = 0;
        target_animation++;
            
        if(target_animation >= (COLOR_DATA_LEN/8)) target_animation = 0;
    }

    half_set_color_data_streaming(color_data, led.ms);

    if(LED_TYPE == PWM) 
    {
        TIM_SetCompare3(TIM1, color_data[3]); //red
        TIM_SetCompare4(TIM1, color_data[2]); //green
        TIM_SetCompare1(TIM1, color_data[1]); //blue
    }
    else if(LED_TYPE == SPI) 
    {
        spi_write(color_data);
    }

}



void led_mode_reset()
{
    //strobe reset
    strobe_cnt = 0;

    //dimming reset
    dimming_cnt = 0;
    dimming_direction = 1;
    r_dimming_brightness = 0;
    g_dimming_brightness = 0;
    b_dimming_brightness = 0;

    //streaming reset
    streaming_color_cnt = 0;
    target_animation = 0;
}