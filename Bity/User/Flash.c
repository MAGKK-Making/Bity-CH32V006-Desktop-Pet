#include <ch32v00X.h>
#include "SPI.h"
#include "Flash.h"

/**
 * @brief Flash发送命令 或数据
 */
void FlashWriteCommand(uint8_t Command){
    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_RESET);
    SPISendByte(Command);
    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);
}

/**
 * @brief Flash初始化
 */
void FlashInit(void){
    FlashWriteCommand(0xAB);
    Delay_Ms(100);
    FlashWriteCommand(0x66);
    Delay_Ms(100);
    FlashWriteCommand(0x99);
    Delay_Ms(100);
}

/**
 * @brief Flash读取数据
 */
uint8_t FlashReadData(uint32_t Addr){
    while((FlashGetRDSR() & 0x01) == 1);
    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_RESET);

    SPISendByte(0x03);

    SPISendByte((Addr >> 16) & 0xFF);
    SPISendByte((Addr >> 8) & 0xFF);
    SPISendByte(Addr & 0xFF);

    SPI_I2S_ReceiveData(SPI1);
    SPISendByte(0x00);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);
    return SPI_I2S_ReceiveData(SPI1);
}

/**
 * @brief Flash写数据
 */
void FlashWriteData(uint32_t Addr, uint8_t Data){
    while(FlashReadData(Addr) != Data){
        while((FlashGetRDSR() & 0x01) == 1);
        FlashWriteCommand(0x06);

        GPIO_WriteBit(GPIOD, FlashSPICS, Bit_RESET);

        SPISendByte(0x02);

        SPISendByte((Addr >> 16) & 0xFF);
        SPISendByte((Addr >> 8) & 0xFF);
        SPISendByte(Addr & 0xFF);
        //Delay_Us(100);
        SPISendByte(Data);
        //Delay_Us(100);
        GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);
        while((FlashGetRDSR() & 0x01) == 1);
    }
}

/**
 * @brief Flash读取RDSR
 */
uint8_t FlashGetRDSR(void){
    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_RESET);

    SPISendByte(0x05);
    SPI_I2S_ReceiveData(SPI1);
    SPISendByte(0x00);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);
    return SPI_I2S_ReceiveData(SPI1);
}

/**
 * @brief Flash按页擦除
 */
void FlashErasePage(uint32_t PageAddr){
    while((FlashGetRDSR() & 0x01) == 1);

    FlashWriteCommand(0x06);

    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_RESET);

    SPISendByte(0x81);

    SPISendByte((PageAddr >> 16) & 0xFF);
    SPISendByte((PageAddr >> 8) & 0xFF);
    SPISendByte(PageAddr & 0xFF);

    GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);

    while((FlashGetRDSR() & 0x01) == 1);
}

/**
 * @brief Flash按页写入8位数据
 */
void FlashWritePage8(uint32_t PageAddr, uint8_t* Data, uint16_t Length){
    uint32_t Delta = 0;
    while(Length > 0){
        FlashErasePage(PageAddr + Delta*256);
        while((FlashGetRDSR() & 0x01) == 1);
        FlashWriteCommand(0x06);

        GPIO_WriteBit(GPIOD, FlashSPICS, Bit_RESET);

        SPISendByte(0x02);

        SPISendByte(((PageAddr + Delta*256) >> 16) & 0xFF);
        SPISendByte(((PageAddr + Delta*256) >> 8) & 0xFF);
        SPISendByte((PageAddr + Delta*256) & 0xFF);

        if(Length > 256){
            for(uint16_t Bit = 0; Bit < 256; Bit ++){
                SPISendByte(Data[Bit + Delta*256]);
            }
            Length -= 256;
            Delta += 1;
        }
        else{
            for(uint16_t Bit = 0; Bit < Length; Bit ++){
                SPISendByte(Data[Bit + Delta*256]);
            }
            Length = 0;
        }
        GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);
        while((FlashGetRDSR() & 0x01) == 1);
    }
}

/**
 * @brief Flash按页写入16位数据
 */
void FlashWritePage16(uint32_t PageAddr, uint16_t* Data, uint16_t Length){
    uint32_t Delta = 0;
    while(Length > 0){
        FlashErasePage(PageAddr + Delta*256);
        while((FlashGetRDSR() & 0x01) == 1);
        FlashWriteCommand(0x06);

        GPIO_WriteBit(GPIOD, FlashSPICS, Bit_RESET);

        SPISendByte(0x02);

        SPISendByte(((PageAddr + Delta*256) >> 16) & 0xFF);
        SPISendByte(((PageAddr + Delta*256) >> 8) & 0xFF);
        SPISendByte((PageAddr + Delta*256) & 0xFF);

        if(Length > 128){
            for(uint16_t Bit = 0; Bit < 128; Bit ++){
                SPISendByte((uint8_t)(Data[Bit + Delta*128] >> 8));
                SPISendByte((uint8_t)((Data[Bit + Delta*128]) & 0xFF));
            }
            Length -= 128;
            Delta += 1;
        }
        else{
            for(uint16_t Bit = 0; Bit < Length; Bit ++){
                SPISendByte((uint8_t)(Data[Bit + Delta*128] >> 8));
                SPISendByte((uint8_t)((Data[Bit + Delta*128]) & 0xFF));
            }
            Length = 0;
        }
        GPIO_WriteBit(GPIOD, FlashSPICS, Bit_SET);
        while((FlashGetRDSR() & 0x01) == 1);
    }
}

/**
 * @brief Flash读取16位数据
 */
void FlashReadData16(uint32_t Addr, uint16_t* DataBuffer, uint32_t Length){
    for(uint32_t Bit = 0; Bit < Length; Bit ++){
        DataBuffer[Bit] = ((uint16_t)FlashReadData(Addr + Bit * 2) << 8) | FlashReadData(Addr + Bit * 2 + 1);
    }
}
