#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"

typedef enum 
{
	THROW_DONE,
	THROW_FAILED,
	TAKEBALL,
}AR_State;

void Servo_Task(void);

void TIM1_CH1_PWM_Init(u32 arr,u32 psc);
void TIM2_CH2_PWM_Init(u32 arr,u32 psc);

#endif
