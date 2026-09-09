#include <ch32v00X.h>
#include "Screen.h"
#include "Ani.h"
#include "debug.h"
#include "Button.h"

#define Xpos 64
#define Ypos 24
#define PetYpos 41
#define DeltaT 15
#define DeltaTTrans 2

#define MenuBackgroundColor 0xffff//0xfffe

#define AniSeqLen 13
uint8_t SpriteFlag[AniSeqLen];
uint8_t PrevSpriteFlag[AniSeqLen];
uint8_t SpriteIndex[AniSeqLen];

void AnimationFuncBootAni(void){
    LCDDrawMonoBitmapQuick(LogoAni_1, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_2, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_3, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_4, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_5, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_6, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_7, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_8, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_9, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_10, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_11, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_12, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_13, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_14, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_15, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT);//
    LCDDrawMonoBitmapQuick(LogoAni_16, Xpos, Ypos, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT * 20);
    LCDDrawMonoBitmapQuick(LogoAni_16, Xpos - 20, Ypos, 32, 32, 0x0000, 0xffff);
    LCDClearArea(Xpos - 20 + 32, Ypos, Xpos + 32, Ypos + 32, 0xFFFF);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_16, Xpos - 35, Ypos, 32, 32, 0x0000, 0xffff);
    LCDClearArea(Xpos - 35 + 32, Ypos, Xpos + 32, Ypos + 32, 0xFFFF);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_16, Xpos - 40, Ypos, 32, 32, 0x0000, 0xffff);
    LCDClearArea(Xpos - 40 + 32, Ypos, Xpos + 32, Ypos + 32, 0xFFFF);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_16, Xpos - 42, Ypos, 32, 32, 0x0000, 0xffff);
    LCDClearArea(Xpos - 42 + 32, Ypos, Xpos + 32, Ypos + 32, 0xFFFF);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_16, Xpos - 44, Ypos, 32, 32, 0x0000, 0xffff);
    LCDClearArea(Xpos - 44 + 32, Ypos, Xpos + 32, Ypos + 32, 0xFFFF);
    Delay_Ms(DeltaT);
    LCDDrawMonoBitmapQuick(LogoAni_16, Xpos - 45, Ypos, 32, 32, 0x0000, 0xffff);
    LCDClearArea(Xpos - 45 + 32, Ypos, Xpos + 32, Ypos + 32, 0xFFFF);
    Delay_Ms(DeltaT * 5);

    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xf7be, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xef7d, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xe73c, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xdefb, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xd69a, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xce59, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xbdf7, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xb5b6, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0xa554, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0x9cd3, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0x8c71, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0x7bcf, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0x632c, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0x4a49, 0xffff);
    Delay_Ms(DeltaT * 2);
    LCDDrawMonoBitmapQuick(LogoAni_title, 58, 32, 79, 16, 0x0000, 0xffff);
    //Delay_Ms(DeltaT * 50);
}

void AnimationFuncTransitionAni(void){
    for(uint8_t i = 2; i <= 160; i += 2){
        LCDClearArea(i - 2, 0, i, 80, 0x0000);
        Delay_Ms(DeltaTTrans);
    }
    for(uint8_t i = 2; i <= 160; i += 2){
        LCDClearArea(i - 2, 0, i, 80, 0xffff);
        Delay_Ms(DeltaTTrans);
    }
}

void AnimationFuncWaitingForConnectAni(void){
    LCDDrawMonoBitmapQuick(WaitingAni_Text1, 47, 60, 66, 8, 0x0000, 0xffff);

    LCDDrawMonoBitmapQuick(WaitingAni_NoConnection, 76, 14, 8, 8, 0xf800, 0xffff);
    LCDDrawMonoBitmapQuick(WaitingAni_1, 64, 24, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT * 5);
    LCDDrawMonoBitmapQuick(WaitingAni_2, 64, 24, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT * 5);
    LCDDrawMonoBitmapQuick(WaitingAni_3, 64, 24, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT * 5);
    LCDDrawMonoBitmapQuick(WaitingAni_NoConnection, 76, 14, 8, 8, 0xffff, 0xffff);
    LCDDrawMonoBitmapQuick(WaitingAni_4, 64, 24, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT * 5);
    LCDDrawMonoBitmapQuick(WaitingAni_3, 64, 24, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT * 5);
    LCDDrawMonoBitmapQuick(WaitingAni_2, 64, 24, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DeltaT * 5);
}

void AnimationFuncPetAniBox(void){
    LCDDrawMonoBitmapQuick(PetAniBox, 62, PetYpos + 16, 36, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniNormal(void){
    if(SpriteIndex[0] == 0)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 1)LCDDrawMonoBitmapQuick(PetAni2, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 2)LCDDrawMonoBitmapQuick(PetAni3, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 3)LCDDrawMonoBitmapQuick(PetAni2, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 4)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 5)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 6)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 7)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 8)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 9)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 10)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[0] == 11)LCDDrawMonoBitmapQuick(PetAni1, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniEating(void){
    if(SpriteIndex[1] == 0)LCDDrawMonoBitmapQuick(PetAni4, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 1)LCDDrawMonoBitmapQuick(PetAni5, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 2)LCDDrawMonoBitmapQuick(PetAni6, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 3)LCDDrawMonoBitmapQuick(PetAni7, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 4)LCDDrawMonoBitmapQuick(PetAni5, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 5)LCDDrawMonoBitmapQuick(PetAni6, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 6)LCDDrawMonoBitmapQuick(PetAni7, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 7)LCDDrawMonoBitmapQuick(PetAni5, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 8)LCDDrawMonoBitmapQuick(PetAni6, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 9)LCDDrawMonoBitmapQuick(PetAni7, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 10)LCDDrawMonoBitmapQuick(PetAni8, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[1] == 11)LCDDrawMonoBitmapQuick(PetAni9, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniWow(void){
    if(SpriteIndex[2] == 0)LCDDrawMonoBitmapQuick(PetAni10, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 1)LCDDrawMonoBitmapQuick(PetAni11, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 2)LCDDrawMonoBitmapQuick(PetAni12, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 3)LCDDrawMonoBitmapQuick(PetAni13, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 4)LCDDrawMonoBitmapQuick(PetAni10, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 5)LCDDrawMonoBitmapQuick(PetAni11, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 6)LCDDrawMonoBitmapQuick(PetAni12, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 7)LCDDrawMonoBitmapQuick(PetAni13, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 8)LCDDrawMonoBitmapQuick(PetAni10, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 9)LCDDrawMonoBitmapQuick(PetAni11, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 10)LCDDrawMonoBitmapQuick(PetAni12, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[2] == 11)LCDDrawMonoBitmapQuick(PetAni13, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniUgh(void){
    if(SpriteIndex[3] == 0)LCDDrawMonoBitmapQuick(PetAni14, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 1)LCDDrawMonoBitmapQuick(PetAni15, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 2)LCDDrawMonoBitmapQuick(PetAni16, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 3)LCDDrawMonoBitmapQuick(PetAni15, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 4)LCDDrawMonoBitmapQuick(PetAni14, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 5)LCDDrawMonoBitmapQuick(PetAni15, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 6)LCDDrawMonoBitmapQuick(PetAni16, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 7)LCDDrawMonoBitmapQuick(PetAni15, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 8)LCDDrawMonoBitmapQuick(PetAni14, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 9)LCDDrawMonoBitmapQuick(PetAni15, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 10)LCDDrawMonoBitmapQuick(PetAni16, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[3] == 11)LCDDrawMonoBitmapQuick(PetAni15, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniHungry(void){
    if(SpriteIndex[4] == 0)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 1)LCDDrawMonoBitmapQuick(PetAni18, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 2)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 3)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 4)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 5)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 6)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 7)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 8)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 9)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 10)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[4] == 11)LCDDrawMonoBitmapQuick(PetAni17, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniWink(void){
    if(SpriteIndex[5] == 0)LCDDrawMonoBitmapQuick(PetAni19, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[5] == 1)LCDDrawMonoBitmapQuick(PetAni20, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[5] == 2)LCDDrawMonoBitmapQuick(PetAni21, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[5] == 3)LCDDrawMonoBitmapQuick(PetAni20, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniAngry(void){
    if(SpriteIndex[6] <= 9)LCDDrawMonoBitmapQuick(PetAni22, 66, PetYpos, 28, 16, 0x0000, 0xffff);//~10
    if(SpriteIndex[6] == 10)LCDDrawMonoBitmapQuick(PetAni23, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniHide(void){
    if(SpriteIndex[7] == 0)LCDDrawMonoBitmapQuick(PetAni24, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[7] == 1)LCDDrawMonoBitmapQuick(PetAni25, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[7] == 2)LCDDrawMonoBitmapQuick(PetAni26, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[7] == 3)LCDDrawMonoBitmapQuick(PetAni27, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[7] == 4)LCDDrawMonoBitmapQuick(PetAni28, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[7] == 5)LCDDrawMonoBitmapQuick(PetAni29, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[7] == 6)LCDDrawMonoBitmapQuick(PetAni30, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniAppear(void){
    if(SpriteIndex[8] == 0)LCDDrawMonoBitmapQuick(PetAni30, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[8] == 1)LCDDrawMonoBitmapQuick(PetAni29, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[8] == 2)LCDDrawMonoBitmapQuick(PetAni28, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[8] == 3)LCDDrawMonoBitmapQuick(PetAni27, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[8] == 4)LCDDrawMonoBitmapQuick(PetAni26, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[8] == 5)LCDDrawMonoBitmapQuick(PetAni25, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[8] == 6)LCDDrawMonoBitmapQuick(PetAni24, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniPlaying(void){
    if(SpriteIndex[9] == 0)LCDDrawMonoBitmapQuick(PetAni31, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 1)LCDDrawMonoBitmapQuick(PetAni32, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 2)LCDDrawMonoBitmapQuick(PetAni33, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 3)LCDDrawMonoBitmapQuick(PetAni34, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 4)LCDDrawMonoBitmapQuick(PetAni35, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 5)LCDDrawMonoBitmapQuick(PetAni36, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 6)LCDDrawMonoBitmapQuick(PetAni37, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 7)LCDDrawMonoBitmapQuick(PetAni38, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 8)LCDDrawMonoBitmapQuick(PetAni39, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 9)LCDDrawMonoBitmapQuick(PetAni40, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 10)LCDDrawMonoBitmapQuick(PetAni39, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 11)LCDDrawMonoBitmapQuick(PetAni38, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 12)LCDDrawMonoBitmapQuick(PetAni39, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 13)LCDDrawMonoBitmapQuick(PetAni40, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 14)LCDDrawMonoBitmapQuick(PetAni39, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 15)LCDDrawMonoBitmapQuick(PetAni38, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 16)LCDDrawMonoBitmapQuick(PetAni39, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 17)LCDDrawMonoBitmapQuick(PetAni40, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 18)LCDDrawMonoBitmapQuick(PetAni39, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 19)LCDDrawMonoBitmapQuick(PetAni38, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 20)LCDDrawMonoBitmapQuick(PetAni39, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 21)LCDDrawMonoBitmapQuick(PetAni40, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 22)LCDDrawMonoBitmapQuick(PetAni41, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 23)LCDDrawMonoBitmapQuick(PetAni42, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 24)LCDDrawMonoBitmapQuick(PetAni43, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 25)LCDDrawMonoBitmapQuick(PetAni44, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 26)LCDDrawMonoBitmapQuick(PetAni45, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[9] == 27)LCDDrawMonoBitmapQuick(PetAni46, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniTouch(void){
    if(SpriteIndex[10] == 0)LCDDrawMonoBitmapQuick(PetAni47, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 1)LCDDrawMonoBitmapQuick(PetAni48, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 2)LCDDrawMonoBitmapQuick(PetAni49, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 3)LCDDrawMonoBitmapQuick(PetAni50, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 4)LCDDrawMonoBitmapQuick(PetAni49, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 5)LCDDrawMonoBitmapQuick(PetAni50, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 6)LCDDrawMonoBitmapQuick(PetAni49, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 7)LCDDrawMonoBitmapQuick(PetAni48, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[10] == 8)LCDDrawMonoBitmapQuick(PetAni47, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniAvoid1(void){
    if(SpriteIndex[11] == 0)LCDDrawMonoBitmapQuick(PetAni51, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[11] == 1)LCDDrawMonoBitmapQuick(PetAni52, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[11] == 2)LCDDrawMonoBitmapQuick(PetAni51, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[11] == 3)LCDDrawMonoBitmapQuick(PetAni52, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[11] == 4)LCDDrawMonoBitmapQuick(PetAni51, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[11] == 5)LCDDrawMonoBitmapQuick(PetAni52, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[11] == 6)LCDDrawMonoBitmapQuick(PetAni51, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[11] == 7)LCDDrawMonoBitmapQuick(PetAni52, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

void AnimationFuncPetAniAvoid2(void){
    if(SpriteIndex[12] == 0)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 1)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 2)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 3)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 4)LCDDrawMonoBitmapQuick(PetAni54, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 5)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 6)LCDDrawMonoBitmapQuick(PetAni54, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 7)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 8)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 9)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 10)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
    if(SpriteIndex[12] == 11)LCDDrawMonoBitmapQuick(PetAni53, 66, PetYpos, 28, 16, 0x0000, 0xffff);
}

/**
 * @brief 内部管理函数，不外用
 * 
 * @param Seq 动画序列号
 * @param MaxIndex 动画最大帧
 */
void AnimationFuncFlagManage(uint8_t Seq, uint8_t MaxIndex){
    //检测动画是否需要重新播放
    if(PrevSpriteFlag[Seq] == 0 && SpriteFlag[Seq] == 1){
        PrevSpriteFlag[Seq] = 1;
        SpriteIndex[Seq] = 0;//动画帧清零
    }
    else if(PrevSpriteFlag[Seq] == 1 && SpriteFlag[Seq] == 1){
        if(SpriteIndex[Seq] < MaxIndex - 1)SpriteIndex[Seq] += 1;
        else SpriteIndex[Seq] = 0;
    }
}

/**
 * @brief 用于统一管理动画的函数
 * 
 * @param AniSeq 动画序列号
 * @return uint8_t 动画末帧标识符
 */
uint8_t AnimationFuncManage(uint8_t AniSeq){
    uint8_t MaxIndex = 0;
    uint8_t IndexEndFlag = 0;//动画末帧标识符

    for(uint8_t i = 0; i < AniSeqLen; i ++){
        SpriteFlag[i] = (i == AniSeq)?1:0;
    }

    switch(AniSeq){
        case 0:{
            MaxIndex = 12;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniNormal();
            break;
        }
        case 1:{
            MaxIndex = 12;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniEating();
            break;
        }
        case 2:{
            MaxIndex = 12;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniWow();
            break;
        }
        case 3:{
            MaxIndex = 12;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniUgh();
            break;
        }
        case 4:{
            MaxIndex = 12;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniHungry();
            break;
        }
        case 5:{
            MaxIndex = 4;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniWink();
            break;
        }
        case 6:{
            MaxIndex = 11;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniAngry();
            break;
        }
        case 7:{
            MaxIndex = 7;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniHide();
            break;
        }
        case 8:{
            MaxIndex = 7;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniAppear();
            break;
        }
        case 9:{
            MaxIndex = 28;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniPlaying();
            break;
        }
        case 10:{
            MaxIndex = 9;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniTouch();
            break;
        }
        case 11:{
            MaxIndex = 8;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniAvoid1();
            break;
        }
        case 12:{
            MaxIndex = 12;
            AnimationFuncFlagManage(AniSeq, MaxIndex);
            AnimationFuncPetAniAvoid2();
            break;
        }
        default:{
            
            break;
        }
    }

    for(uint8_t i = 0; i < AniSeqLen; i ++){
        PrevSpriteFlag[i] = SpriteFlag[i];
    }

    IndexEndFlag = (MaxIndex - 1 == SpriteIndex[AniSeq]);
    return IndexEndFlag;
}

void AnimationFuncMenuInit(void){//0xf7be
    LCDClearArea(3, 8, 27, 59, 0x0000);
    LCDClearArea(4, 9, 26, 58, MenuBackgroundColor);
    LCDDrawMonoBitmapQuick(MenuFood, 8, 13, 13, 8, 0x0000, MenuBackgroundColor);
    LCDDrawMonoBitmapQuick(MenuPlay, 8, 23, 13, 8, 0x0000, MenuBackgroundColor);
    LCDDrawMonoBitmapQuick(MenuEndThisDay, 8, 33, 13, 8, 0x0000, MenuBackgroundColor);
    LCDDrawMonoBitmapQuick(MenuResetSystem, 8, 43, 13, 8, 0x0000, MenuBackgroundColor);
    LCDDrawMonoBitmapQuick(MenuResetSystem, 8, 43, 13, 8, 0x0000, MenuBackgroundColor);
    LCDDrawMonoBitmapQuick(UICoins, 33, 65, 8, 8, 0xFD20, 0xFFFF);
    LCDDrawMonoBitmapQuick(UILike, 33, 55, 8, 8, 0xF800, 0xFFFF);
    LCDDrawMonoBitmapQuick(UILike, 33, 45, 8, 8, 0x8010, 0xFFFF);
    LCDDrawMonoBitmapQuick(UILike, 33, 35, 8, 8, 0x0280, 0xFFFF);
    LCDDrawMonoBitmapQuick(UIDay, 33, 9, 16, 16, 0x0000, 0xFFFF);
    //L41CDDrawMonoBitmapQuick(UICurtain, 60, 8, 40, 8, 0x0000, 0xFFFF);
}

float NowY = 40;
float AttenuationCoefficient = 0.05;
void AnimationFuncMenuChange(uint16_t TargetY){
    NowY += AttenuationCoefficient * (float)(TargetY - NowY);

    LCDClearArea(23, 9, 26, NowY - 1, MenuBackgroundColor);
    LCDClearArea(23, NowY, 26, NowY + 8, 0xf800);
    LCDClearArea(23, NowY + 9, 26, 58, MenuBackgroundColor);
    LCDClearArea(4, 9, 7, NowY - 1, MenuBackgroundColor);
    LCDClearArea(4, NowY, 7, NowY + 8, 0xf800);
    LCDClearArea(4, NowY + 9, 7, 58, MenuBackgroundColor);
}

typedef struct{
    const uint8_t *FoodBitmap;
    uint8_t FoodPrefer1;
    uint8_t FoodPrefer2;
    uint8_t FoodPrefer3;
    uint8_t FoodCost;
} FoodStructTypeDef;

FoodStructTypeDef FoodStruct[] = {
    {.FoodBitmap = UIFoods1,.FoodCost = 10,.FoodPrefer1 = 20,.FoodPrefer2 = 60,.FoodPrefer3 = 10,},
    {.FoodBitmap = UIFoods2,.FoodCost = 5,.FoodPrefer1 = 80,.FoodPrefer2 = 10,.FoodPrefer3 = 20,},
    {.FoodBitmap = UIFoods3,.FoodCost = 35,.FoodPrefer1 = 70,.FoodPrefer2 = 60,.FoodPrefer3 = 60,},
    {.FoodBitmap = UIFoods4,.FoodCost = 10,.FoodPrefer1 = 10,.FoodPrefer2 = 60,.FoodPrefer3 = 10,},
    {.FoodBitmap = UIFoods5,.FoodCost = 5,.FoodPrefer1 = 0,.FoodPrefer2 = 0,.FoodPrefer3 = 60,},
    {.FoodBitmap = UIFoods6,.FoodCost = 5,.FoodPrefer1 = 60,.FoodPrefer2 = 20,.FoodPrefer3 = 10,},
    {.FoodBitmap = UIFoods7,.FoodCost = 15,.FoodPrefer1 = 70,.FoodPrefer2 = 30,.FoodPrefer3 = 15,},
};

float FoodPrefer1Show = 0;
float FoodPrefer2Show = 0;
float FoodPrefer3Show = 0;
const float FoodPreferChangeRate = 0.1;
//速率慢，不能快速连续执行
void AnimationFuncMenuShowFoods(uint8_t Seq){
    if(Seq >= 7)return;
    LCDDrawMonoBitmapQuick(FoodStruct[Seq].FoodBitmap, 115, 20, 32, 32, 0x0000, 0xFFFF);
    LCDDrawMonoBitmapQuick(UICoins, 115, 11, 8, 8, 0xFD20, 0xFFFF);
    uint8_t Words[] = {'-'};
    LCDDrawWords(124, 11, Words, 1, 0xFD20,0xffff);
    LCDDrawNum(128,11,FoodStruct[Seq].FoodCost,2,0xFD20,0xffff);
}
//可以连续执行的动画效果
void AnimationFuncMenuShowFoodsBar(uint8_t Seq){
    if(Seq >= 7)return;
    FoodPrefer1Show = FoodPrefer1Show + ((float)FoodStruct[Seq].FoodPrefer1 - FoodPrefer1Show) * FoodPreferChangeRate;
    FoodPrefer2Show = FoodPrefer2Show + ((float)FoodStruct[Seq].FoodPrefer2 - FoodPrefer2Show) * FoodPreferChangeRate;
    FoodPrefer3Show = FoodPrefer3Show + ((float)FoodStruct[Seq].FoodPrefer3 - FoodPrefer3Show) * FoodPreferChangeRate;
    LCDDrawBar(115,53,32,100,FoodPrefer1Show,0xffff,0x0000,0x0280);
    LCDDrawBar(115,60,32,100,FoodPrefer2Show,0xffff,0x0000,0x8010);
    LCDDrawBar(115,67,32,100,FoodPrefer3Show,0xffff,0x0000,0xF800);
}

uint8_t AnimationFuncMenuFoodSelect(uint16_t *InputCoinsVal, uint8_t Selection){
    if(*InputCoinsVal >= FoodStruct[Selection].FoodCost){
        *InputCoinsVal -= FoodStruct[Selection].FoodCost;
        return 1;
    }
    else{
        LCDDrawMonoBitmapQuick(UINoEnoughMoney, 115, 32, 32, 8, 0xF800, 0xFFFF);
        return 0;
    }
}

uint8_t AnimationFuncMenuFoodSelectCalculation(uint8_t Prefer1, uint8_t Prefer2, uint8_t Prefer3, uint8_t Selection){
    float OutputVal = 0;
    OutputVal = ((float)(FoodStruct[Selection].FoodPrefer1 * Prefer1 + FoodStruct[Selection].FoodPrefer2 * Prefer2 + FoodStruct[Selection].FoodPrefer3 * Prefer3)) / 30;
    return (uint8_t)OutputVal;
}

void AnimationFuncMenuShowActions(uint8_t Seq){
    if(Seq >= 2)return;
    if(Seq == 0){
        /*LCDClearArea(115, 56, 147, 72, 0xFFFF);
        LCDDrawMonoBitmapQuick(UITextTouch, 115, 56, 20, 8, 0x0000, 0xFFFF);*/
        LCDDrawMonoBitmapQuick(UIActions1, 115, 24, 32, 32, 0x0000, 0xFFFF);
    }
    if(Seq == 1){
        /*LCDClearArea(115, 56, 147, 72, 0xFFFF);
        LCDDrawMonoBitmapQuick(UITextPlaying, 115, 56, 27, 16, 0x0000, 0xFFFF);*/
        LCDDrawMonoBitmapQuick(UIActions2, 115, 24, 32, 32, 0x0000, 0xFFFF);
    }
}

#define UITimeChangeX 64
void AnimationFuncUITimeChange(uint8_t ImageIndex){
    if(ImageIndex > 15)return;
    switch(ImageIndex){
        case 0:LCDDrawMonoBitmapQuick(UITimeChange1, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 1:LCDDrawMonoBitmapQuick(UITimeChange2, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 2:LCDDrawMonoBitmapQuick(UITimeChange3, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 3:LCDDrawMonoBitmapQuick(UITimeChange4, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 4:LCDDrawMonoBitmapQuick(UITimeChange5, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 5:LCDDrawMonoBitmapQuick(UITimeChange6, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 6:LCDDrawMonoBitmapQuick(UITimeChange7, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 7:LCDDrawMonoBitmapQuick(UITimeChange8, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 8:LCDDrawMonoBitmapQuick(UITimeChange9, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 9:LCDDrawMonoBitmapQuick(UITimeChange10, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 10:LCDDrawMonoBitmapQuick(UITimeChange11, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 11:LCDDrawMonoBitmapQuick(UITimeChange12, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 12:LCDDrawMonoBitmapQuick(UITimeChange13, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 13:LCDDrawMonoBitmapQuick(UITimeChange14, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 14:LCDDrawMonoBitmapQuick(UITimeChange15, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
        case 15:LCDDrawMonoBitmapQuick(UITimeChange16, UITimeChangeX, 24, 32, 32, 0x0000, 0xFFFF); break;
    }
}

#define PetStateMessageStateFree 0
#define PetStateMessageStateAppear 1
#define PetStateMessageStateHeart 2
#define PetStateMessageStateAngry 3
#define PetStateMessageStateHungry 4
#define PetStateMessageStateKnowledge 5
#define PetStateMessageStateHide 6
#define BusyFree 0
#define BusyEating 1
#define BusyPlaying 2
#define BusyHiding 3
#define BusyThinking 4
#define PetStateMessageX 72
#define PetStateMessageY 23

uint8_t PetStateMessageState = PetStateMessageStateFree;
uint8_t PetStateMessageIndex = 0;

uint8_t PetStateMessage(uint8_t PetStateMessageStateInternal){
    if(PetStateMessageStateInternal == PetStateMessageStateAppear){
        switch(PetStateMessageIndex){
            case 0:{LCDDrawMonoBitmapQuick(UIPetState1, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 1:{LCDDrawMonoBitmapQuick(UIPetState2, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 2:{LCDDrawMonoBitmapQuick(UIPetState3, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 3:{LCDDrawMonoBitmapQuick(UIPetState4, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex = 0; return 1;}
        }
    }
    else if(PetStateMessageStateInternal == PetStateMessageStateHeart){
        switch(PetStateMessageIndex){
            case 0:{LCDDrawMonoBitmapQuick(UIPetState5, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 1:{LCDDrawMonoBitmapQuick(UIPetState6, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 2:{LCDDrawMonoBitmapQuick(UIPetState7, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 3:{LCDDrawMonoBitmapQuick(UIPetState6, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex = 0; return 1;}
        }
    }
    else if(PetStateMessageStateInternal == PetStateMessageStateAngry){
        switch(PetStateMessageIndex){
            case 0:{LCDDrawMonoBitmapQuick(UIPetState8, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 1:{LCDDrawMonoBitmapQuick(UIPetState9, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 2:{LCDDrawMonoBitmapQuick(UIPetState10, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 3:{LCDDrawMonoBitmapQuick(UIPetState9, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex = 0; return 1;}
        }
    }
    else if(PetStateMessageStateInternal == PetStateMessageStateHungry){
        switch(PetStateMessageIndex){
            case 0:{LCDDrawMonoBitmapQuick(UIPetState11, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 1:{LCDDrawMonoBitmapQuick(UIPetState12, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 2:{LCDDrawMonoBitmapQuick(UIPetState13, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 3:{LCDDrawMonoBitmapQuick(UIPetState14, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex = 0; return 1;}
        }
    }
    else if(PetStateMessageStateInternal == PetStateMessageStateKnowledge){
        switch(PetStateMessageIndex){
            case 0:{LCDDrawMonoBitmapQuick(UIPetState15, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 1:{LCDDrawMonoBitmapQuick(UIPetState16, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 2:{LCDDrawMonoBitmapQuick(UIPetState17, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 3:{LCDDrawMonoBitmapQuick(UIPetState18, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex = 0; return 1;}
        }
    }
    else if(PetStateMessageStateInternal == PetStateMessageStateHide){
        switch(PetStateMessageIndex){
            case 0:{LCDDrawMonoBitmapQuick(UIPetState4, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 1:{LCDDrawMonoBitmapQuick(UIPetState3, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 2:{LCDDrawMonoBitmapQuick(UIPetState2, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 3:{LCDDrawMonoBitmapQuick(UIPetState1, PetStateMessageX, PetStateMessageY, 16, 16, 0x0000, 0xFFFF); PetStateMessageIndex ++; return 0;}
            case 4:{LCDClearArea(PetStateMessageX, PetStateMessageY, PetStateMessageX + 16, PetStateMessageY + 16, 0xFFFF); PetStateMessageIndex = 0; return 1;}
        }
    }
    LCDClearArea(PetStateMessageX, PetStateMessageY, PetStateMessageX + 16, PetStateMessageY + 16, 0xFFFF);
    return 0;
}

void PetStateMessageManage(float *PetValLike, float *PetValEnergy, uint8_t *PetIsBusy){
    if(*PetValEnergy < 30){
        if(PetStateMessageState == PetStateMessageStateFree)PetStateMessageState = PetStateMessageStateAppear;
        if(PetStateMessage(PetStateMessageState) == 1){
            PetStateMessageState = PetStateMessageStateHungry;
        }
    }
    else if(*PetValLike > 90){
        if(PetStateMessageState == PetStateMessageStateFree)PetStateMessageState = PetStateMessageStateAppear;
        if(PetStateMessage(PetStateMessageState) == 1){
            PetStateMessageState = PetStateMessageStateHeart;
        }
    }
    else if(*PetValLike < 20){
        if(PetStateMessageState == PetStateMessageStateFree)PetStateMessageState = PetStateMessageStateAppear;
        if(PetStateMessage(PetStateMessageState) == 1){
            PetStateMessageState = PetStateMessageStateAngry;
        }
    }
    else if(*PetIsBusy == BusyHiding){
        if(PetStateMessageState == PetStateMessageStateFree)PetStateMessageState = PetStateMessageStateAppear;
        if(PetStateMessage(PetStateMessageState) == 1){
            PetStateMessageState = PetStateMessageStateKnowledge;
        }
    }
    else{
        if(PetStateMessageState != PetStateMessageStateFree)PetStateMessageState = PetStateMessageStateHide;
        if(PetStateMessage(PetStateMessageState) == 1 && PetStateMessageState == PetStateMessageStateHide){
            PetStateMessageState = PetStateMessageStateFree;
        }
    }
}

void AnimationFuncDrawPressMidButton(void){
    LCDDrawMonoBitmapQuick(UIPressMidButton, 56, 60, 48, 8, 0x0000, 0xFFFF);
}

void AnimationFuncDrawTextEndThisDay(void){
    LCDDrawMonoBitmapQuick(UITextEndThisDay, 115, 24, 32, 32, 0x0000, 0xFFFF);
}

void AnimationFuncDrawTextRestartThisDay(void){
    LCDDrawMonoBitmapQuick(UITextRestartThisDay, 115, 24, 32, 32, 0x0000, 0xFFFF);
}

#define DialogCharPosX 96
#define DialogCharPosY 24
#define DialogOutlinePosX 30
#define DialogOutlinePosY 28
#define DialogDeltaT 35
const uint8_t *DialogArray[] = {
    Dialog1, Dialog2, Dialog3, Dialog4, Dialog5, Dialog6, Dialog7, Dialog8, Dialog9,
    Dialog10, Dialog11, Dialog12, Dialog13, Dialog14, Dialog15, 
};
void AnimationFuncInitialDialog(void){
    LCDClearArea(0, 0, 160, 10, 0x0000);
    LCDClearArea(0, 70, 160, 80, 0x0000);
    Delay_Ms(DialogDeltaT * 4);
    LCDClearArea(0, 10, 160, 15, 0x0000);
    LCDClearArea(0, 65, 160, 70, 0x0000);
    Delay_Ms(DialogDeltaT * 4);
    LCDClearArea(0, 15, 160, 18, 0x0000);
    LCDClearArea(0, 62, 160, 65, 0x0000);
    Delay_Ms(DialogDeltaT * 4);
    LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX + 15, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 47, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX + 10, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 42, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX + 6, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 38, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX + 3, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 35, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX + 1, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 33, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    for(uint8_t DialogX = 0; DialogX < 9; DialogX ++){
        LCDClearArea(DialogOutlinePosX, DialogOutlinePosY, DialogOutlinePosX + 65, DialogOutlinePosY + 24, 0xFFFF);
        LCDDrawMonoBitmapQuick(DialogOutline1, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline2, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline3, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogArray[DialogX], 31, 32, 60, 16, 0x0000, 0xffff);

        while(ButtonIsPressedMiddle() == 0);
        if(DialogX < 7 && DialogX != 3 && DialogX != 7){
            LCDDrawMonoBitmapQuick(DialogCharacter2, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter3, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter4, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter3, DialogCharPosX + 1, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
        }
        if(DialogX == 3){
            LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter3, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter4, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter6, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
        }
        if(DialogX == 7){
            LCDDrawMonoBitmapQuick(DialogCharacter1, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter2, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter4, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter4, DialogCharPosX + 1, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogCharacter5, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
        }
        LCDDrawMonoBitmapQuick(DialogOutline3, DialogOutlinePosX + 1, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline2, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline1, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
    }
    LCDClearArea(DialogOutlinePosX, DialogOutlinePosY, DialogOutlinePosX + 66, DialogOutlinePosY + 24, 0xFFFF);
    Delay_Ms(DialogDeltaT * 2);
}

void AnimationFuncMonthDialog(void){
    AnimationFuncTransitionAni();
    LCDClearArea(0, 0, 160, 10, 0x0000);
    LCDClearArea(0, 70, 160, 80, 0x0000);
    Delay_Ms(DialogDeltaT * 4);
    LCDClearArea(0, 10, 160, 15, 0x0000);
    LCDClearArea(0, 65, 160, 70, 0x0000);
    Delay_Ms(DialogDeltaT * 4);
    LCDClearArea(0, 15, 160, 18, 0x0000);
    LCDClearArea(0, 62, 160, 65, 0x0000);
    Delay_Ms(DialogDeltaT * 4);
    LCDDrawMonoBitmapQuick(DialogPhone1, DialogCharPosX + 15, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 47, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogPhone1, DialogCharPosX + 10, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 42, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogPhone1, DialogCharPosX + 6, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 38, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogPhone1, DialogCharPosX + 3, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 35, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogPhone1, DialogCharPosX + 1, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    LCDClearArea(DialogCharPosX, DialogCharPosY, DialogCharPosX + 33, DialogCharPosY + 32, 0xFFFF);
    LCDDrawMonoBitmapQuick(DialogPhone1, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
    Delay_Ms(DialogDeltaT);
    for(uint8_t DialogX = 10; DialogX < 15; DialogX ++){
        LCDClearArea(DialogOutlinePosX, DialogOutlinePosY, DialogOutlinePosX + 65, DialogOutlinePosY + 24, 0xFFFF);
        LCDDrawMonoBitmapQuick(DialogOutline1, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline2, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline3, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogArray[DialogX], 31, 32, 60, 16, 0x0000, 0xffff);

        while(ButtonIsPressedMiddle() == 0);
        if(DialogX < 14){
            LCDDrawMonoBitmapQuick(DialogPhone2, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogPhone3, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogPhone2, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
            Delay_Ms(DialogDeltaT * 2);
            LCDDrawMonoBitmapQuick(DialogPhone1, DialogCharPosX, DialogCharPosY, 32, 32, 0x0000, 0xffff);
        }
        LCDDrawMonoBitmapQuick(DialogOutline3, DialogOutlinePosX + 1, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline2, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
        LCDDrawMonoBitmapQuick(DialogOutline1, DialogOutlinePosX, DialogOutlinePosY, 65, 24, 0x0000, 0xffff);
        Delay_Ms(DialogDeltaT);
    }
    LCDClearArea(DialogOutlinePosX, DialogOutlinePosY, DialogOutlinePosX + 66, DialogOutlinePosY + 24, 0xFFFF);
    Delay_Ms(DialogDeltaT * 2);
}