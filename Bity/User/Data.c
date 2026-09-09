#include <ch32v00X.h>
#include "Flash.h"

void DataSaveAndRead(float *PetValLike, float *PetValEnergy, uint8_t *PetValDay, uint16_t *PetValCoins, uint8_t *PetValIsFirstMonth){
    FlashErasePage(0x00000100);
    FlashWriteData(0x00000100 + 0, (uint8_t)*PetValLike);
    FlashWriteData(0x00000100 + 1, (uint8_t)*PetValEnergy);
    FlashWriteData(0x00000100 + 2, (uint8_t)*PetValDay);
    FlashWriteData(0x00000100 + 3, (uint8_t)(*PetValCoins >> 8));
    FlashWriteData(0x00000100 + 4, (uint8_t)(*PetValCoins));
    FlashWriteData(0x00000100 + 5, (uint8_t)(*PetValIsFirstMonth));

    *PetValLike = FlashReadData(0x00000100 + 0);
    *PetValEnergy = FlashReadData(0x00000100 + 1);
    *PetValDay = FlashReadData(0x00000100 + 2);
    *PetValCoins  = (FlashReadData(0x00000100 + 3) << 8) | FlashReadData(0x00000100 + 4);
    *PetValIsFirstMonth  = FlashReadData(0x00000100 + 5);
}

void DataRead(float *PetValLike, float *PetValEnergy, uint8_t *PetValDay, uint16_t *PetValCoins, uint8_t *PetValIsFirstMonth){
    *PetValLike = FlashReadData(0x00000100 + 0);
    *PetValEnergy = FlashReadData(0x00000100 + 1);
    *PetValDay = FlashReadData(0x00000100 + 2);
    *PetValCoins  = (FlashReadData(0x00000100 + 3) << 8) | FlashReadData(0x00000100 + 4);
    *PetValIsFirstMonth  = FlashReadData(0x00000100 + 5);
}

void DataInit(void){
    FlashErasePage(0x00000100);
    FlashWriteData(0x00000100 + 0, 50);
    FlashWriteData(0x00000100 + 1, 100);
    FlashWriteData(0x00000100 + 2, 1);
    FlashWriteData(0x00000100 + 3, 0);
    FlashWriteData(0x00000100 + 4, 100);
    FlashWriteData(0x00000100 + 5, 1);
}