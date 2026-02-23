/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/01/01
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#include <ch32v00x.h>
#include "debug.h"
#include "ram.h"
#include "mode_function.h"
#include "pwm.h"
#include "spi.h"
#include "sequence.h"
#include "timer.h"
#include "color_data.h"



__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update))
    { 
        tick++; 
        button_cnt++;
    
        if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 1) //pressing
        {
            if(button_cnt >= 30) 
            {
                button_flag = 1;
            }
        }
        else //release
        {
            if(button_flag == 1)
            {
                button_flag = 0;

                led_mode_reset(); //mode initialization
            
                seq_i++;
                if(seq_i<0 || seq_i>=MAX_SEQUENCE)
                    seq_i=0;

                if(seq_i>=0) //go to next sequence
                {
                    led.r = sequence[seq_i].r;
                    led.g = sequence[seq_i].g;
                    led.b = sequence[seq_i].b;
                    led.ms = sequence[seq_i].ms;
                    led.mode = sequence[seq_i].mode;
                }

            }
            else 
            {
                button_cnt = 0;
            }

        }

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	}
}



int main()
{ 
    TIM1_init(255-1, (SystemCoreClock/1000000)-1); //for PWM, max brightness: 255
    TIM2_init(1000-1, (SystemCoreClock/1000000)-1); //1tick = 1000ms
    SystemCoreClockUpdate(); //update SystemCoreClock variable
    Delay_Init(); //delay initialization
    
    color_data_init(); //led color array initialization
    half_streaming_color_init(); //set array to rainbow color according to number of led

    //set according to led type
    if(LED_TYPE == PWM)
    {
        pwm_led_init(); //pwm, gpio
    }
    else if(LED_TYPE == SPI) 
    {
        spi_led_init(); //spi, gpio
    }
        
    //led sequence
    led_sequence_init();

    while(1)
    {
        if(tick >= ACTIVE_TICK) //every (ACTIVE_TICK)tick
        {
            tick = 0;
            
            if(led.mode == STROBE)
            {   
                strobe();
            }
            else if(led.mode == DIMMING)
            {
                dimming();
            }
            else if(led.mode == STREAMING)
            {
                streaming();
            }
        }

    }
}


