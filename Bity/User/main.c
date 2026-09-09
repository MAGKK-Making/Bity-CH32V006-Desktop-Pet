#include "debug.h"
#include "LogicFunc.h"
#include "LogicTimeBase.h"

volatile uint8_t StepFlag = 0;
volatile uint8_t StepSlowStart = 0;
volatile uint8_t StepFastFlag = 0;
 
int main(void){
    LogicTimeBaseInit();

    LogicFuncInit();
    while(1){
        if(StepSlowStart == 1){
            StepSlowStart = 0;
            LogicFuncStep();
        }
        if(StepFastFlag == 1){
            StepFastFlag = 0;
            LogicFuncStepFast();
        }
    }
}

__attribute__((interrupt))
void TIM2_IRQHandler(void){
    //Step
    if(StepFlag <= 60)StepFlag += 1;
    else{
        StepFlag = 0;
        StepSlowStart = 1;
    }
    //StepFast
    StepFastFlag = 1;
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
