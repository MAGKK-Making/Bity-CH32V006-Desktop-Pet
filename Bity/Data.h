#ifndef __Data
#define __Data

void DataSaveAndRead(float *PetValLike, float *PetValEnergy, uint8_t *PetValDay, uint16_t *PetValCoins, uint8_t *PetValIsFirstMonth);
void DataRead(float *PetValLike, float *PetValEnergy, uint8_t *PetValDay, uint16_t *PetValCoins, uint8_t *PetValIsFirstMonth);
void DataInit(void);

#endif