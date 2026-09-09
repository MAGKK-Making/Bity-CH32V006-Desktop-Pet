#include <ch32v00X.h>

//引脚分布
//            T    T    T
//  |- PA2   PD2  PD3  PD4
//  |- PA1      正面

void ButtonInit(void){
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIOInitStruct = {0};
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_30MHz;

    GPIOInitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIOInitStruct);

    GPIOInitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_Init(GPIOD, &GPIOInitStruct);
}

uint8_t PrevButtonUp = 0;
uint8_t ButtonIsPressedUp(void){
    uint8_t KeyStatue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
    if(PrevButtonUp == 0 && KeyStatue == 1){
        PrevButtonUp = 1;
        return 1;
    }
    else if(PrevButtonUp == 1 && KeyStatue == 0){
        PrevButtonUp = 0;
        return 0;
    }
    else{
        return 0;
    }
}

uint8_t PrevButtonDown = 0;
uint8_t ButtonIsPressedDown(void){
    uint8_t KeyStatue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
    if(PrevButtonDown == 0 && KeyStatue == 1){
        PrevButtonDown = 1;
        return 1;
    }
    else if(PrevButtonDown == 1 && KeyStatue == 0){
        PrevButtonDown = 0;
        return 0;
    }
    else{
        return 0;
    }
}

uint8_t PrevButtonLeft = 0;
uint8_t ButtonIsPressedLeft(void){
    uint8_t KeyStatue = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
    if(PrevButtonLeft == 0 && KeyStatue == 1){
        PrevButtonLeft = 1;
        return 1;
    }
    else if(PrevButtonLeft == 1 && KeyStatue == 0){
        PrevButtonLeft = 0;
        return 0;
    }
    else{
        return 0;
    }
}

uint8_t PrevButtonMiddle = 1;
uint8_t ButtonIsPressedMiddle(void){
    uint8_t KeyStatue = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3);
    if(PrevButtonMiddle == 0 && KeyStatue == 1){
        PrevButtonMiddle = 1;
        return 1;
    }
    else if(PrevButtonMiddle == 1 && KeyStatue == 0){
        PrevButtonMiddle = 0;
        return 0;
    }
    else{
        return 0;
    }
}

uint8_t PrevButtonRight = 0;
uint8_t ButtonIsPressedRight(void){
    uint8_t KeyStatue = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4);
    if(PrevButtonRight == 0 && KeyStatue == 1){
        PrevButtonRight = 1;
        return 1;
    }
    else if(PrevButtonRight == 1 && KeyStatue == 0){
        PrevButtonRight = 0;
        return 0;
    }
    else{
        return 0;
    }
}