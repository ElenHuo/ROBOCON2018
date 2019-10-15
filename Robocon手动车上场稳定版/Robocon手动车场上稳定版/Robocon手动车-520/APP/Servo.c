#include "Servo.h"

uint16_t Angle;

//   0.5ms--------------0�ȣ�
//   1.0ms------------45�ȣ�
//   1.5ms------------90�ȣ� 1500
//   2.0ms-----------135�ȣ�
//   2.5ms-----------180�ȣ�
//0.5ms-2.5ms

AR_State AR_STATE;

void Servo_Task(void) //20ms
{
	switch(AR_STATE)
	{
		case TAKEBALL:
		{			
		
			TIM_SetCompare1(TIM1,1500);
		}break;
		case THROW_DONE :
		{
			TIM_SetCompare1(TIM1,2500);
		}break;
		case THROW_FAILED:
		{
			TIM_SetCompare1(TIM1,500);
		}break;
	}
	
}



//PA8  TIM1-CH1
//PWM�����ʼ��  
//arr���Զ���װֵ  
//psc��ʱ��Ԥ��Ƶ��  
void TIM1_CH1_PWM_Init(u32 arr,u32 psc)
{		 					 

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM14ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); //GPIOB3����Ϊ��ʱ��14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PB3
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
	
	//��ʼ��TIM2 Channe2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC2

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR2�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM2
 
										  
}  



