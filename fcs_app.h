#ifndef FCS_APP_H_
#define FCS_APP_H_

#include "FCS.h"
#include "sensors.h"
#include "lora.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

void FCS_APP_Task(void);
void FCS_APP_SetMotors(void);
void FCS_APP_UpdateInputs(void);//krok w petli 200Hz
void FCS_APP_BuzzerUpdate(void);

#endif


