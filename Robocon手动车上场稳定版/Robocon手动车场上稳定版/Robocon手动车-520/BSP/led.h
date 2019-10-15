#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED端口定义
#define LED0 PFout(9)	// SYS_LED
#define LED1 PFout(10)	// SYS_LED

/*F3F5 LED1,LED2*/
/*E2E4 LED3,LED4*/
#define ERROR_LED1 PBout(15)	
#define ERROR_LED2 PAout(15)	 
#define ERROR_LED3 PGout(10)	
#define ERROR_LED4 PDout(7)	 

void Led_State_Test(void);
void LED_Init(void);//初始化		 				    
#endif
