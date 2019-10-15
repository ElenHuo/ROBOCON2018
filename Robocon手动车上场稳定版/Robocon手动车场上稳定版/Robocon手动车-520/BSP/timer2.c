#include "main.h"

uint32_t Timer2_Count = 0;//记录Timer3中断次数
uint8_t Count_1ms,Count_2ms,Count_4ms,Count_5ms,Count_20ms,Count_50ms,Count_100ms;
int Count_500ms;
uint16_t Timer2_Frequency;//Timer3中断频率

extern uint8_t Bsp_Int_Ok;


void TIM2_IRQHandler(void)//Timer3中断
{	
	if(TIM2->SR & TIM_IT_Update)
	{     
		TIM2->SR = ~TIM_FLAG_Update;//清除中断标志
		
		if( Bsp_Int_Ok == 0 )	return;//硬件未初始化完成，则返回
		Timer2_Count++;
		Count_1ms++;
		Count_2ms++;
		Count_4ms++;
		Count_5ms++;
		Count_20ms++;
		Count_50ms++;
		Count_100ms++;
		Count_500ms++;
	}
}


void Timer2_Init(uint16_t Handler_Frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	Timer2_Frequency = Handler_Frequency;
	
	TIM_DeInit(TIM2);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000*1000/Timer2_Frequency-1;	//自动重装载值arr
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;												//定时器分频psc
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);	
}
//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/1000=1KHz.

//周期 = (psc+1)*ARR/TIMx时钟
//占空比 = CCRx/ARR
