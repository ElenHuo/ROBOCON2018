#ifndef __SWITCH_H__
#define __SWTICH_H__

#include "stdint.h"
#define SW_LEFT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) //PB14
#define SW_RIGHT GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//PA5
#define SW_STOP  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//PC9

extern  uint8_t SW_L;
extern  uint8_t SW_R;
extern  uint8_t SW_S;
extern  uint8_t Take_Count;

void Auto_Take_Count(void);
void Switch_Init(void);
void Switch_scan(void);

#endif

