#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define LED0 PFout(9)	// SYS_LED
#define LED1 PFout(10)	// SYS_LED

/*F3F5 LED1,LED2*/
/*E2E4 LED3,LED4*/
#define ERROR_LED1 PBout(15)	
#define ERROR_LED2 PAout(15)	 
#define ERROR_LED3 PGout(10)	
#define ERROR_LED4 PDout(7)	 

void Led_State_Test(void);
void LED_Init(void);//��ʼ��		 				    
#endif
