#include "ch32v00X.h"

uint8_t RandomSeed = 0;

const uint8_t RandomBuffer[100] = {
91,17,82,4,53,28,70,11,66,35,
79,2,47,95,6,88,21,59,14,74,
42,98,31,63,8,50,24,85,1,77,
38,69,19,93,44,12,56,80,27,61,
3,72,49,90,16,84,33,68,22,52,
97,7,41,87,10,65,30,76,18,55,
81,5,46,92,13,71,36,62,20,58,
86,9,43,78,25,67,32,94,15,51,
73,29,60,39,83,48,96,23,54,75,
40,64,34,89,99,0,45,57,26,37
};

void RandomSeedRefresh(void){
    if(RandomSeed < 99)RandomSeed += 1;
    else RandomSeed = 0;
}

uint8_t RandomNumGet(void){
    uint8_t RandomVal = RandomBuffer[RandomSeed];
    RandomSeed += RandomVal;
    while(RandomSeed > 99)RandomSeed -= 99;
    return RandomVal;
}