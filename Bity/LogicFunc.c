#include <ch32v00X.h>
#include "debug.h"
#include "Screen.h"
#include "Flash.h"
#include "UART.h"
#include "Button.h"
#include "Boot.h"
#include "AnimationFunc.h"
#include "Data.h"
#include "Random.h"

#define StateNormal 0
#define StateEating 1
#define StateWow 2
#define StateUgh 3
#define StateHungry 4
#define StateWink 5
#define StateAngry 6
#define StateHide 7
#define StateAppear 8
#define StatePlaying 9
#define StateTouch 10
#define StateAvoid1 11
#define StateAvoid2 12

#define BusyFree 0
#define BusyEating 1
#define BusyPlaying 2
#define BusyHiding 3
#define BusyThinking 4

#define PetWaitingStep 300

//宠物忙碌状态：吃饭、互动或其他不处于待机状态的状态
uint8_t PetIsBusy = BusyFree;
uint8_t PetBusyStep = 0;

uint16_t PetWaitingTime = PetWaitingStep;
uint8_t PetHideStep = 0;

float PetValLike = 50;
float PetValEnergy = 100;

uint8_t PetValPrefer01 = 5;
uint8_t PetValPrefer02 = 9;
uint8_t PetValPrefer03 = 2;

uint8_t PetValDay = 1;
uint8_t PetValIsFirstMonth = 1;

uint16_t PetValCoins = 100;

uint8_t MenuFoodSelect = 0;
uint8_t MenuActionSelect = 0;

void LogicShowDay(void){
    AnimationFuncTransitionAni();
    for(uint8_t Index = 0; Index < 16; Index ++){
        AnimationFuncUITimeChange(Index);
        if(Index == 8){
            uint8_t Word[] = "Day";
            LCDDrawWords(36,36,Word,3,0x0000,0xffff);
        }
        if(Index == 15){
            LCDDrawNum(116,36,(uint16_t)PetValDay,2,0x0000,0xffff);
        }
        Delay_Ms(100);
    }

    do{
        RandomSeedRefresh();
        PetValPrefer01 = RandomNumGet() % 9;
        PetValPrefer02 = RandomNumGet() % 9;
        PetValPrefer03 = RandomNumGet() % 9;
    }while(PetValPrefer01 + PetValPrefer02 + PetValPrefer03 < 5);

    AnimationFuncDrawPressMidButton();

    while(ButtonIsPressedMiddle() == 0)RandomSeedRefresh();
    for(uint8_t Index = 15; Index > 6; Index --){
        AnimationFuncUITimeChange(Index);
        Delay_Ms(100);
    }

    AnimationFuncTransitionAni();
    AnimationFuncPetAniBox();
    AnimationFuncMenuInit();
    AnimationFuncMenuShowFoods(MenuFoodSelect);
}

/**
 * @brief 初始化事件
 * 
 */
void LogicFuncInit(void){
    Delay_Init();
    USART1_Init();
    LCDInit();
    FlashInit();
    ButtonInit();
    LCDClear(0x0000);
    Boot((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0));
    LCDClear(0xffff);
    DataRead(&PetValLike, &PetValEnergy, &PetValDay, &PetValCoins, &PetValIsFirstMonth);

    AnimationFuncBootAni();
    while(ButtonIsPressedMiddle() == 0)RandomSeedRefresh();
    if(PetValDay == 1 && PetValIsFirstMonth == 1){
        AnimationFuncTransitionAni();
        AnimationFuncInitialDialog();
    }
    LogicShowDay();

    do{
        RandomSeedRefresh();
        PetValPrefer01 = RandomNumGet() % 9;
        PetValPrefer02 = RandomNumGet() % 9;
        PetValPrefer03 = RandomNumGet() % 9;
    }while(PetValPrefer01 + PetValPrefer02 + PetValPrefer03 < 5);
    
}

/**
 * @brief 循环步事件
 * 
 */
void LogicFuncStep(void){
    if(PetIsBusy != BusyFree){
        //互动、喂食操作
        if(PetIsBusy == BusyEating){
            if(PetBusyStep == 0){
                PetBusyStep += AnimationFuncManage(StateEating);
            }
            if(PetBusyStep == 1){
                uint8_t PetValLikeAddVal = AnimationFuncMenuFoodSelectCalculation(PetValPrefer01, PetValPrefer02, PetValPrefer03, MenuFoodSelect);
                if(PetValLikeAddVal >= 10){
                    PetValEnergy = 100;
                    if(100 - PetValLike <= PetValLikeAddVal){
                        PetValLike = 100;
                    }
                    else{
                        PetValLike += PetValLikeAddVal;
                    }
                    PetBusyStep = 2;
                }
                else{
                    if(100 - PetValEnergy <= 30){
                        PetValEnergy = 100;
                    }
                    else{
                        PetValEnergy += 30;
                    }
                    if(PetValLike > 20){
                        PetValLike -= 20;
                    }
                    else{
                        PetValLike  = 0;
                    }
                    PetBusyStep = 3;
                }
            }
            if(PetBusyStep == 2){
                PetBusyStep += AnimationFuncManage(StateWow) * 2;
            }
            if(PetBusyStep == 3){
                PetBusyStep += AnimationFuncManage(StateUgh);
            }
            if(PetBusyStep == 4){
                //重置偏好
                do{
                    RandomSeedRefresh();
                    PetValPrefer01 = RandomNumGet() % 9;
                    PetValPrefer02 = RandomNumGet() % 9;
                    PetValPrefer03 = RandomNumGet() % 9;
                }while(PetValPrefer01 + PetValPrefer02 + PetValPrefer03 < 5);

                PetBusyStep = 0;
                PetIsBusy = BusyFree;
            }

        }
        else if(PetIsBusy == BusyPlaying){
            if(MenuActionSelect == 0){
                if(PetValEnergy >= 20){
                    if(PetValLike >= 20){
                        if(AnimationFuncManage(StateTouch) == 1){
                            if(100 - PetValLike <= 5){
                                PetValLike = 100;
                            }
                            else{
                                PetValLike += 5;
                            }
                            if(PetValEnergy <= 2){
                                PetValEnergy = 0;
                            }
                            else{
                                PetValEnergy -= 2;
                            }
                            PetIsBusy = BusyFree;
                        }
                    }
                    else{
                        if(AnimationFuncManage(StateAvoid1) == 1){
                            PetIsBusy = BusyFree;
                        }
                    }
                }
                else{
                    if(AnimationFuncManage(StateAvoid2) == 1){
                        PetIsBusy = BusyFree;
                    }
                }
            }
            if(MenuActionSelect == 1){
                if(PetValEnergy >= 20){
                    if(PetValLike >= 20){
                        if(AnimationFuncManage(StatePlaying) == 1){
                            if(100 - PetValLike <= 10){
                                PetValLike = 100;
                            }
                            else{
                                PetValLike += 10;
                            }
                            if(PetValEnergy <= 10){
                                PetValEnergy = 0;
                            }
                            else{
                                PetValEnergy -= 10;
                            }
                            PetIsBusy = BusyFree;
                        }
                    }
                    else{
                        if(AnimationFuncManage(StateAvoid1) == 1){
                            PetIsBusy = BusyFree;
                        }
                    }
                }
                else{
                    if(AnimationFuncManage(StateAvoid2) == 1){
                        PetIsBusy = BusyFree;
                    }
                }
            }
        }
        else if(PetIsBusy == BusyHiding){
            if(PetWaitingTime == 0){
                if(PetHideStep == 0)PetHideStep += AnimationFuncManage(StateHide);
                if(PetValEnergy > 0){
                    PetValEnergy -= 0.02;
                }
                else{
                    PetValEnergy = 0;
                }
                if(PetValLike > 0){
                    PetValLike -= 0.01;
                }
                else{
                    PetValLike = 0;
                }
                LCDDrawBar(3,61,24,100,(uint8_t)PetValLike,0xffff,0x0000,0xf800);
                LCDDrawBar(3,68,24,100,(uint8_t)PetValEnergy,0xffff,0x0000,0x001f);
            }
            else{
                PetHideStep = 0;
                if(AnimationFuncManage(StateAppear) == 1){
                    PetIsBusy = BusyFree;
                    PetValLike = (uint8_t)PetValLike;
                    PetValEnergy = (uint8_t)PetValEnergy;
                }
            }
        }
    }
    
    else{
        //休眠计时
        if(PetWaitingTime > 0)PetWaitingTime -= 1;
        else PetIsBusy = BusyHiding;
        //正常待机动画
        if(PetValEnergy < 20){
            AnimationFuncManage(StateHungry);
            PetValLike -= 0.02;
        }
        else{
            if(PetValLike < 20){
                AnimationFuncManage(StateAngry);
            }
            else{
                AnimationFuncManage(StateNormal);
            }
        }
        
    }
    if(PetIsBusy == BusyFree){
        LCDDrawBar(42,36,11,9,PetValPrefer01,0xffff,0x0000,0x0280);
        LCDDrawBar(42,46,11,9,PetValPrefer02,0xffff,0x0000,0x8010);
        LCDDrawBar(42,56,11,9,PetValPrefer03,0xffff,0x0000,0xF800);
        LCDDrawNum(45,20,(uint16_t)PetValDay,2,0x0000,0xffff);
        LCDDrawBar(3,61,24,100,(uint8_t)PetValLike,0xffff,0x0000,0xf800);
        LCDDrawBar(3,68,24,100,(uint8_t)PetValEnergy,0xffff,0x0000,0x001f);
    }
    LCDDrawNum(42,65,(uint16_t)PetValCoins,3,0x0000,0xFFFF);

    PetStateMessageManage(&PetValLike, &PetValEnergy, &PetIsBusy);
}

/**
 * @brief 循环快速步事件
 * 
 */
uint16_t CursorY = 0;
void LogicFuncStepFast(void){
    RandomSeedRefresh();

    if(CursorY == 0){
        AnimationFuncMenuShowFoodsBar(MenuFoodSelect);
    }
    else if(CursorY == 1){

    }
    else if(CursorY == 2){

    }
    else{

    }    
    AnimationFuncMenuChange(CursorY * 11 + 13);
    //下键
    if(ButtonIsPressedDown() == 1){
        PetWaitingTime = PetWaitingStep;
        if(PetIsBusy != BusyFree){

        }
        else{
            if(CursorY < 3)CursorY += 1;
            else CursorY = 0;
            LCDClearArea(115, 0, 160, 80, 0xFFFF);
            if(CursorY == 0){
                AnimationFuncMenuShowFoods(MenuFoodSelect);
            }
            else if(CursorY == 1){
                AnimationFuncMenuShowActions(MenuActionSelect);
            }
            else if(CursorY == 2){
                AnimationFuncDrawTextEndThisDay();
            }
            else{
                AnimationFuncDrawTextRestartThisDay();
            }
        }
    }
    //上键
    if(ButtonIsPressedUp() == 1){
        PetWaitingTime = PetWaitingStep;
        if(PetIsBusy != BusyFree){

        }
        else{
            if(CursorY > 0)CursorY -= 1;
            else CursorY = 3;
            LCDClearArea(115, 0, 160, 80, 0xFFFF);
            if(CursorY == 0){
                AnimationFuncMenuShowFoods(MenuFoodSelect);
            }
            else if(CursorY == 1){
                AnimationFuncMenuShowActions(MenuActionSelect);
            }
            else if(CursorY == 2){
                AnimationFuncDrawTextEndThisDay();
            }
            else{
                AnimationFuncDrawTextRestartThisDay();
            }
        }
    }
    //左键
    if(ButtonIsPressedLeft() == 1){
        PetWaitingTime = PetWaitingStep;
        if(PetIsBusy != BusyFree){

        }
        else{
            if(CursorY == 0){
                if(MenuFoodSelect == 0)MenuFoodSelect = 6;
                else MenuFoodSelect -= 1;
                AnimationFuncMenuShowFoods(MenuFoodSelect);
            }
            else if(CursorY == 1){
                if(MenuActionSelect == 0)MenuActionSelect = 1;
                else MenuActionSelect -= 1;
                AnimationFuncMenuShowActions(MenuActionSelect);
            }
            else if(CursorY == 2){

            }
            else{

            }
        }
        
    }
    //中键
    if(ButtonIsPressedMiddle() == 1){
        PetWaitingTime = PetWaitingStep;
        if(PetIsBusy != BusyFree){

        }
        else{
            if(CursorY == 0){
                if(AnimationFuncMenuFoodSelect(&PetValCoins,MenuFoodSelect) == 1){
                    PetIsBusy = BusyEating;
                }
            }
            else if(CursorY == 1){
                PetIsBusy = BusyPlaying;
            }
            else if(CursorY == 2){
                CursorY = 0;
                if(PetValCoins < 900)PetValCoins += 50;
                if(PetValCoins > 900)PetValCoins = 900;
                PetValDay += 1;
                PetValLike -= 20;
                if(PetValLike < 0)PetValLike = 0;
                PetValEnergy -= 40;
                if(PetValEnergy < 0)PetValEnergy = 0;
                if(PetValDay == 31){
                    PetValDay = 1;
                    PetValIsFirstMonth = 0;
                    if(PetValCoins < 900)PetValCoins += 450;
                    if(PetValCoins > 900)PetValCoins = 900;
                    DataSaveAndRead(&PetValLike, &PetValEnergy, &PetValDay, &PetValCoins, &PetValIsFirstMonth);
                    AnimationFuncMonthDialog();
                }
                else{
                    DataSaveAndRead(&PetValLike, &PetValEnergy, &PetValDay, &PetValCoins, &PetValIsFirstMonth);
                }
                LogicShowDay();
            }
            else if(CursorY == 3){
                CursorY = 0;
                DataRead(&PetValLike, &PetValEnergy, &PetValDay, &PetValCoins, &PetValIsFirstMonth);
                LogicShowDay();
            }
        }
        
    }
    //右键
    if(ButtonIsPressedRight() == 1){
        PetWaitingTime = PetWaitingStep;
        if(PetIsBusy != BusyFree){
            
        }
        else{
            if(CursorY == 0){
                if(MenuFoodSelect == 6)MenuFoodSelect = 0;
                else MenuFoodSelect += 1;
                AnimationFuncMenuShowFoods(MenuFoodSelect);
            }
            else if(CursorY == 1){
                if(MenuActionSelect == 1)MenuActionSelect = 0;
                else MenuActionSelect += 1;
                AnimationFuncMenuShowActions(MenuActionSelect);
            }
            else if(CursorY == 2){

            }
            else{

            }
        }
        
    }
}