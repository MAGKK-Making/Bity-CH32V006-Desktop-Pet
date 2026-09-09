#include <ch32v00X.h>
#include "SPI.h"

void SPIPeriphInit(void){
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC | RCC_PB2Periph_GPIOD | RCC_PB2Periph_SPI1, ENABLE);

    GPIO_InitTypeDef GPIOInitStruct = {0};
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_30MHz;

    GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIOInitStruct.GPIO_Pin = SPIMISO | SPIMOSI | SPISCL;
    GPIO_Init(SPIPort, &GPIOInitStruct);
    
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOInitStruct.GPIO_Pin = ScreenSPIDC | ScreenSPICS | ScreenSPIRST;
    GPIO_Init(GPIOC, &GPIOInitStruct);

    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOInitStruct.GPIO_Pin = FlashSPIWP | FlashSPIRST;
    GPIO_Init(GPIOC, &GPIOInitStruct);

    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOInitStruct.GPIO_Pin = FlashSPICS;
    GPIO_Init(GPIOD, &GPIOInitStruct);

    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
    GPIO_WriteBit(GPIOC, ScreenSPIRST, Bit_SET);

    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);
    GPIO_WriteBit(GPIOC, FlashSPIRST, Bit_SET);
    GPIO_WriteBit(GPIOC, FlashSPIWP, Bit_SET);

    SPI_InitTypeDef SPIInitStruct = {0};
    SPIInitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPIInitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPIInitStruct.SPI_CPOL = SPI_CPOL_Low;//1Edge + Low OR 2Edge + High
    SPIInitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPIInitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPIInitStruct.SPI_CRCPolynomial = 7;
    SPIInitStruct.SPI_Mode = SPI_Mode_Master;
    SPIInitStruct.SPI_NSS = SPI_NSS_Soft;
    SPIInitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

    SPI_Init(SPI1, &SPIInitStruct);
    SPI_Cmd(SPI1, ENABLE);
}

void SPISendByte(uint8_t Byte){
    SPI_I2S_SendData(SPI1, Byte);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

void ScreenSPISendCommand(uint8_t Command){
    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, Command);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

void ScreenSPISendData(uint8_t Data8){
    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, Data8);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

void ScreenSPISendData16(uint16_t Data16){
    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, (uint8_t)(Data16 >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(Data16));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

void ScreenSPISendData16WithCommand(uint16_t Data16){
    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, 0x2C);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);

    SPI_I2S_SendData(SPI1, (uint8_t)(Data16 >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(Data16));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

void ScreenSPISendData16sWithCommand(uint16_t Data16, uint16_t Times){
    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, 0x2C);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
    for(uint16_t i = 0; i < Times; i ++){
        SPI_I2S_SendData(SPI1, (uint8_t)(Data16 >> 8));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_SendData(SPI1, (uint8_t)(Data16));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    }

    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}