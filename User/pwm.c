#include <ch32v00x.h>
#include "debug.h"
#include "pwm.h"



void pwm_led_init() //pwm, gpio
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_OCInitTypeDef TIM_OCInitStructure={0};

    //RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE );

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //if TIMn, set PWMn
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; //brightness
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //output polarity

    //channel Initialization
    TIM_OC1Init(TIM1, &TIM_OCInitStructure); //channel1
    TIM_OC2Init(TIM1, &TIM_OCInitStructure); //channel2
    TIM_OC3Init(TIM1, &TIM_OCInitStructure); //channel3
    TIM_OC4Init(TIM1, &TIM_OCInitStructure); //channel4

    //DISABLE: back up CCPR to CCSR without 'update event'
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable); //channel1
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Disable); //channel2
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Disable); //channel3
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable); //channel4

    TIM_CtrlPWMOutputs(TIM1, ENABLE); //output enable or disable

    //led (red, CH3)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    //led (green, CH4)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //led (blue, CH1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //switch
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}