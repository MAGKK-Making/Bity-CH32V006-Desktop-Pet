#ifndef __Flash
#define __Flash

void FlashWriteCommand(uint8_t Command);
void FlashInit(void);
uint8_t FlashReadData(uint32_t Addr);
void FlashWriteData(uint32_t Addr, uint8_t Data);
uint8_t FlashGetRDSR(void);
void FlashErasePage(uint32_t PageAddr);
void FlashWritePage8(uint32_t PageAddr, uint8_t* Data, uint16_t Length);
void FlashWritePage16(uint32_t PageAddr, uint16_t* Data, uint16_t Length);
void FlashReadData16(uint32_t Addr, uint16_t* DataBuffer, uint32_t Length);

#endif