#include <ch32v00X.h>

#define DeltaTimeMs 2

void LogicTimeBaseInit(void){
    //TIM2µÍËÙÊ±»ù
    RCC_PB1PeriphClockCmd(RCC_PB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef TIMTimeBaseInitStruct = {0};
    TIMTimeBaseInitStruct.TIM_ClockDivision = 0;
    TIMTimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIMTimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIMTimeBaseInitStruct.TIM_Period = DeltaTimeMs - 1;
    TIMTimeBaseInitStruct.TIM_Prescaler = 48000 - 1;
    TIM_TimeBaseInit(TIM2, &TIMTimeBaseInitStruct);

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVICInitStruct = {0};
    NVICInitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVICInitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVICInitStruct);

    TIM_Cmd(TIM2, ENABLE);
}