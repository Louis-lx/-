#ifndef __SERVO_H

#define __SERVO_H


#include "sys.h"
void TIM2_PWM_Init(u32 arr,u32 psc);
void TIM5_Servo_Init(void);
void TIM1_Servo_Init(void);
#endif
