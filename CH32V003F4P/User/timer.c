#include "timer.h"

void TIM1_init(u16 period, u16 prescaler) //for PWM
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    //NVIC_InitTypeDef nvic = {0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE );

    TIM_TimeBaseInitStructure.TIM_Period = period; 
    TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    //TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    // nvic.NVIC_IRQChannel = TIM1_UP_IRQn;
    // nvic.NVIC_IRQChannelPreemptionPriority = 0;
    // nvic.NVIC_IRQChannelSubPriority = 1;
    // nvic.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_Init(&nvic);

    //TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_ARRPreloadConfig( TIM1, ENABLE );
    TIM_Cmd( TIM1, ENABLE );
}



void TIM2_init(u16 period, u16 prescaler) //for tick
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    NVIC_InitTypeDef nvic = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = period; //value to be loaded into the active
    TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler; //used to divide the TIM clock.
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // timer clock : smpling clock = 1 : 1(DIV)
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //tick++
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //interrupt enable or disable

    nvic.NVIC_IRQChannel = TIM2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0; //set interrupt priority (0~15)
    nvic.NVIC_IRQChannelSubPriority = 1; //set interrupt priority2 (0~15)
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    TIM_CtrlPWMOutputs(TIM2, DISABLE); //output enable or disable
    TIM_ARRPreloadConfig(TIM2, ENABLE); //ENABLE: update ARR after overflow, It prevents the interrupt call cycle getting longer
    TIM_Cmd(TIM2, ENABLE); //TIM2 enable or disable
}