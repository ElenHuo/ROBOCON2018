#ifndef __RAS_USART_H
#define __RAS_USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h"
#include "stdlib.h"
#define EN_UART5_RX 			1

typedef struct remote
{
	uint16_t thr;
	uint16_t Y;
	uint16_t Z;
	uint16_t X;
	uint16_t KEY1;
	uint16_t KEY2;
	uint16_t KEY3;
	uint16_t KEY4;
	uint16_t KEY5;
	uint16_t KEY6;
	uint16_t KEY7;
	uint16_t KEY8;
	uint16_t KEY9;
	uint16_t KEY10;
	uint16_t KEY11;
	uint16_t KEY12;
	
}_Remote_;

extern uint16_t UART5_cnt;
extern _Remote_ RM;
extern float openmv_x;
extern float openmv_yaw;
extern float openmv_z;
void uart5_init(u32 bound);

#endif

