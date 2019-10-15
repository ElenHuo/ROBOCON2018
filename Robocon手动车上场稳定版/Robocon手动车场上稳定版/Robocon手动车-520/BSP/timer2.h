#ifndef __TIMER2_H
#define __TIMER2_H
#include "sys.h"

extern uint32_t Timer2_Count;
extern uint16_t Timer2_Frequency;
extern uint8_t Count_1ms,Count_2ms,Count_4ms,Count_5ms,Count_20ms,Count_50ms,Count_100ms;
extern int Count_500ms;

void Timer2_Init(uint16_t Handler_Frequency);

#endif
