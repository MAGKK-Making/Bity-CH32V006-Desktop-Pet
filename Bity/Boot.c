#include <ch32v00X.h>
#include "Screen.h"
#include "Button.h"
#include "Flash.h"
#include "Data.h"

uint8_t BootCheckKey[8] = {
    0x73, 0x1A, 0xE8, 0x45, 0x92, 0x0B, 0xCF, 0x5D,
};
uint8_t BootGetKey[8];

uint8_t BootCheckKeyHexOutput[24];
uint8_t BootGetKeyHexOutput[24];

uint8_t BootValToString(uint8_t Val){
    switch(Val){
        case 0:{Val = '0';break;}
        case 1:{Val = '1';break;}
        case 2:{Val = '2';break;}
        case 3:{Val = '3';break;}
        case 4:{Val = '4';break;}
        case 5:{Val = '5';break;}
        case 6:{Val = '6';break;}
        case 7:{Val = '7';break;}
        case 8:{Val = '8';break;}
        case 9:{Val = '9';break;}
        case 10:{Val = 'A';break;}
        case 11:{Val = 'B';break;}
        case 12:{Val = 'C';break;}
        case 13:{Val = 'D';break;}
        case 14:{Val = 'E';break;}
        case 15:{Val = 'F';break;}
        default:{break;}
    }
    return Val;
}

//Target长度需为Source长度*3
void BootCodeToHexString(uint16_t Len, uint8_t *Source, uint8_t *Target){
    for(uint16_t Bit = 0; Bit < Len; Bit ++){
        Target[3 * Bit + 0] = BootValToString((Source[Bit] >> 4) & 0x0F);
        Target[3 * Bit + 1] = BootValToString((Source[Bit]) & 0x0F);
        Target[3 * Bit + 2] = ' ';
    }
}

const uint32_t BootKeyAddress = 0x00000000;
void Boot(uint8_t ForceBootInto){
    if(ForceBootInto == 1){
        uint8_t WordsEntry[] = "--- BOOT ---\nForced into BOOT mode...";
        LCDDrawWords(0,0,WordsEntry,37, 0xffff,0x0000);
        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1);
        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
        LCDClear(0x0000);
    }
    //读取Flash
    for(uint8_t Bit = 0; Bit < 8; Bit ++){
        BootGetKey[Bit] = FlashReadData(BootKeyAddress + Bit);
    }
    //检查
    if( BootCheckKey[0] == BootGetKey[0] &&
        BootCheckKey[1] == BootGetKey[1] &&
        BootCheckKey[2] == BootGetKey[2] &&
        BootCheckKey[3] == BootGetKey[3] &&
        BootCheckKey[4] == BootGetKey[4] &&
        BootCheckKey[5] == BootGetKey[5] &&
        BootCheckKey[6] == BootGetKey[6] &&
        BootCheckKey[7] == BootGetKey[7] &&
        ForceBootInto == 0
        )return;
    //转换为字符串
    BootCodeToHexString(8, BootCheckKey, BootCheckKeyHexOutput);
    BootCodeToHexString(8, BootGetKey, BootGetKeyHexOutput);
    //显示
    uint8_t Words00[] = "--- BOOT ---\nWhy is this screen displayed?\n1.The program has detected a FLASH\nerror.\n2.Hold down B1 during POWERON.\n- Please press B1 to continue. -";
    LCDDrawWords(0,0,Words00,148, 0xffff,0x0000);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
    LCDClear(0x0000);
    uint8_t Words01[] = "--- BOOT ---\nTarget key:";
    LCDDrawWords(0,0,Words01,24, 0xffff,0x0000);
    LCDDrawWords(0,20,BootCheckKeyHexOutput,24, 0x001f,0x0000);
    uint8_t Words02[] = "Key retrieved from address 0x00000000:";
    LCDDrawWords(0,30,Words02,38, 0xffff,0x0000);
    if( BootCheckKey[0] == BootGetKey[0] &&
        BootCheckKey[1] == BootGetKey[1] &&
        BootCheckKey[2] == BootGetKey[2] &&
        BootCheckKey[3] == BootGetKey[3] &&
        BootCheckKey[4] == BootGetKey[4] &&
        BootCheckKey[5] == BootGetKey[5] &&
        BootCheckKey[6] == BootGetKey[6] &&
        BootCheckKey[7] == BootGetKey[7]
        )LCDDrawWords(0,40,BootGetKeyHexOutput,24, 0x07E0,0x0000);
    else LCDDrawWords(0,40,BootGetKeyHexOutput,24, 0xf800,0x0000);
    uint8_t Words03[] = "Please make sure to memorize the content\non this page before proceeding with the\nfollowing operations.   -Press B1-";
    LCDDrawWords(0,50,Words03,115, 0xffff,0x0000);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
    LCDClear(0x0000);
    uint8_t Words04[] = "--- BOOT ---\nThe program will then provide repair\nsolutions for different scenarios.\nPress B1 to switch.\nPerform corresponding operations by\npressing keys as instructed on-screen.";
    LCDDrawWords(0,0,Words04,179,0xf800,0x0000);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
    LCDClear(0x0000);
    uint8_t Words05[] = "--- BOOT ---\nOption1:Fully erase and format FLASH\nFor device initialization\nAll data will be erased\n\nB1:Next Option  B4:Execute";
    LCDDrawWords(0,0,Words05,127,0xf800,0x0000);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1){
        if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0){
            LCDClear(0x0000);
            uint8_t Words06[] = "--- BOOT ---\nErasing...\nDo not power off.";
            LCDDrawWords(0,0,Words06,41,0xf800,0x0000);
            for(uint32_t Addr = 0x00000000; Addr < 0x0007FF00; Addr += 256){
                FlashErasePage(Addr);
            }
            for(uint32_t Addr = 0; Addr < 8; Addr += 1){
                FlashWriteData(BootKeyAddress + Addr, BootCheckKey[Addr]);
            }
            DataInit();
            LCDClear(0x0000);
            uint8_t Words07[] = "--- BOOT ---\nCompleted!\nPlease turn off the power to restart.";
            LCDDrawWords(0,0,Words07,61,0x07E0,0x0000);
            while(1);
        }
    }
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
    LCDClear(0x0000);
    uint8_t Words08[] = "--- BOOT ---\nOption2:Only erase Flash\nRestore FLASH completely to factory\ndefault state\nAll data will be erased\n\nB1:Next Option  B4:Execute";
    LCDDrawWords(0,0,Words08,139,0xf800,0x0000);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1){
        if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0){
            LCDClear(0x0000);
            uint8_t Words09[] = "--- BOOT ---\nErasing...\nDo not power off.";
            LCDDrawWords(0,0,Words09,41,0xf800,0x0000);
            for(uint32_t Addr = 0x00000000; Addr < 0x0007FF00; Addr += 256){
                FlashErasePage(Addr);
            }
            LCDClear(0x0000);
            uint8_t Words10[] = "--- BOOT ---\nCompleted!\nPlease turn off the power to restart.";
            LCDDrawWords(0,0,Words10,61,0x07E0,0x0000);
            while(1);
        }
    }
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
    LCDClear(0x0000);
    uint8_t Words11[] = "--- BOOT ---\nOption3:Restore key only\nPotential bad data cannot be recovered\n\nB1:Next Option  B4:Execute";
    LCDDrawWords(0,0,Words11,104,0xf800,0x0000);
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1){
        if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0){
            LCDClear(0x0000);
            uint8_t Words12[] = "--- BOOT ---\nRestoring...\nDo not power off.";
            LCDDrawWords(0,0,Words12,43,0xf800,0x0000);
            FlashErasePage(BootKeyAddress);
            for(uint32_t Addr = 0; Addr < 8; Addr += 1){
                FlashWriteData(BootKeyAddress + Addr, BootCheckKey[Addr]);
            }
            LCDClear(0x0000);
            uint8_t Words13[] = "--- BOOT ---\nCompleted!\nPlease turn off the power to restart.";
            LCDDrawWords(0,0,Words13,61,0x07E0,0x0000);
            while(1);
        }
    }
    while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
    LCDClear(0x0000);
    uint8_t Words14[] = "--- BOOT ---\nThis is the last page\nIf your issue remains unresolved\nplease contact the developer via\nQQ:1641323619\nwechat:1641323619";
    LCDDrawWords(0,0,Words14,132,0xffff,0x0000);
    while(1){
        
    };
}