#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"

#define  TIM_period_num  (u16)(65535)

 void encoder_Init_TIM3(void);
 void encoder_Init_TIM4(void);
 void encoder_Init_TIM8(void);
 int Read_Encoder(u8 TIMX);
 int Read_Position(u8 TIMX);

#endif
