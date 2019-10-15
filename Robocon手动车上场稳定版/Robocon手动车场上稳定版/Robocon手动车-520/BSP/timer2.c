#include "main.h"

uint32_t Timer2_Count = 0;//��¼Timer3�жϴ���
uint8_t Count_1ms,Count_2ms,Count_4ms,Count_5ms,Count_20ms,Count_50ms,Count_100ms;
int Count_500ms;
uint16_t Timer2_Frequency;//Timer3�ж�Ƶ��

extern uint8_t Bsp_Int_Ok;


void TIM2_IRQHandler(void)//Timer3�ж�
{	
	if(TIM2->SR & TIM_IT_Update)
	{     
		TIM2->SR = ~TIM_FLAG_Update;//����жϱ�־
		
		if( Bsp_Int_Ok == 0 )	return;//Ӳ��δ��ʼ����ɣ��򷵻�
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
	TIM_TimeBaseInitStructure.TIM_Period = 1000*1000/Timer2_Frequency-1;	//�Զ���װ��ֵarr
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;												//��ʱ����Ƶpsc
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);	
}
//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/1000=1KHz.

//���� = (psc+1)*ARR/TIMxʱ��
//ռ�ձ� = CCRx/ARR
