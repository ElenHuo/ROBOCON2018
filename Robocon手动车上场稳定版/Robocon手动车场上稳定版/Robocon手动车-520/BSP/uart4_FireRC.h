#ifndef __UART_FIRERC_H
#define __UART_FIRERC_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h"
	
#define EN_UART4_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

//extern uint16_t LX,LY,RX,RY,AU1,AU2,AU3,KEY_0,KEY_1;
void uart4_Remoter_init(u32 bound);

#endif

