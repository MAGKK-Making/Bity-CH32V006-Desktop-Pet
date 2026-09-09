#ifndef __AnimationFunc
#define __AnimationFunc

void AnimationFuncBootAni(void);
void AnimationFuncTransitionAni(void);
void AnimationFuncWaitingForConnectAni(void);

uint8_t AnimationFuncManage(uint8_t AniSeq);

void AnimationFuncPetAniBox(void);
/*void AnimationFuncPetAniNormal(void);
void AnimationFuncPetAniEating(void);
void AnimationFuncPetAniWow(void);
void AnimationFuncPetAniUgh(void);
void AnimationFuncPetAniHungry(void);
void AnimationFuncPetAniWink(void);
void AnimationFuncPetAniAngry(void);
void AnimationFuncPetAniHide(void);
void AnimationFuncPetAniAppear(void);*/

void AnimationFuncMenuInit(void);
void AnimationFuncMenuChange(uint16_t TargetY);
void AnimationFuncMenuShowFoods(uint8_t Seq);
void AnimationFuncMenuShowFoodsBar(uint8_t Seq);
uint8_t AnimationFuncMenuFoodSelect(uint16_t *InputCoinsVal, uint8_t Selection);
uint8_t AnimationFuncMenuFoodSelectCalculation(uint8_t Prefer1, uint8_t Prefer2, uint8_t Prefer3, uint8_t Selection);
void AnimationFuncMenuShowActions(uint8_t Seq);

void AnimationFuncUITimeChange(uint8_t ImageIndex);
void PetStateMessageManage(float *PetValLike, float *PetValEnergy, uint8_t *PetIsBusy);

void AnimationFuncDrawPressMidButton(void);
void AnimationFuncDrawTextEndThisDay(void);
void AnimationFuncDrawTextRestartThisDay(void);

void AnimationFuncInitialDialog(void);
void AnimationFuncMonthDialog(void);

#endif