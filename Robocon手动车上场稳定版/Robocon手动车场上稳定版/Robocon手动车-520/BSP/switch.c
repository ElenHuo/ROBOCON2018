#include "main.h"
uint8_t SW_L=0;
uint8_t SW_R=0;
uint8_t SW_S=0;//ֹͣλ
uint8_t Take_Count;
uint8_t Flag_Count;
//PB14,PA5


void Auto_Take_Count(void)
{

	
  if(SW_S==1)
	{
		if(Flag_Count==0)
		Take_Count++;
		Flag_Count=1;
	}
	
	
	
}



void Switch_scan(void)
{
	if(SW_LEFT==1)SW_L=1;
	else SW_L=0;
	if(SW_RIGHT==1)SW_R=1;
	else SW_R=0;
	if(SW_STOP==1)SW_S=1;
	else SW_S=0;
}

void Switch_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//WK_UP��Ӧ����PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA0
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//WK_UP��Ӧ����PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA0
}







