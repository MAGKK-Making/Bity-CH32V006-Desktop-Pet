#include <ch32v00X.h>

void USART1_Init(void){
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    // 使能GPIOA和USART1时钟
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD | RCC_PB2Periph_USART1, ENABLE);

    // 配置PA9（TX）为推挽复用输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    // 配置串口参数
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx; // 仅发送模式
    USART_Init(USART1, &USART_InitStruct);

    // 使能串口
    USART_Cmd(USART1, ENABLE);
}

// 串口发送一个字节
void USART1_SendByte(uint8_t data){
    USART_SendData(USART1, data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

// 串口发送多个字节
void USART1_SendBytes(uint8_t *data, uint16_t len){
    for (uint16_t i = 0; i < len; i++) {
        USART1_SendByte(data[i]);
    }
}