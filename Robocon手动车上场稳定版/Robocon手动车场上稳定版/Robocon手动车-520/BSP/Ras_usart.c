#include "main.h"

_Remote_ RM;
uint16_t tag;
void uart5_init(u32 bound)
	{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //GPIOA9��GPIOA10  //TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PA9��PA10
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOA9��GPIOA10  //RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PA9��PA10
	
	
   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(UART5, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(UART5, ENABLE);  //ʹ�ܴ���1 
	

	
#if EN_UART5_RX	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
}


uint16_t UART5_cnt;
void UART5_IRQHandler(void)                	//����1�жϷ������
{
	static uint8_t ch;
	static union
	{
		uint8_t data[32];//һ���ֽ�
		uint16_t ActVal[16];//2���ֽ�
	}Remote;
	static uint8_t count=0;
  static uint8_t i=0;

	if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET)   
	{
		USART_ClearITPendingBit( UART5,USART_IT_RXNE);	
		ch=USART_ReceiveData(UART5);
		
		 switch(count)
		 {
			 case 0:
				 if(ch==0x0a)
					 count++;
				 else
					 count=0;
				 break;
				 
			 case 1:
				 if(ch==0x0a)
				 {
					 i=0;
					 count++;
				 }
				 else if(ch==0x0b);
				 else
					 count=0;
				 break;
				 
			 case 2:
				 Remote.data[i]=ch;
			   i++;
			   if(i>=32)
				 {
					 i=0;
					 count++;
				 }
				 break;
				 
			 case 3:
				 if(ch==0x0b)
					 count++;
				 else
					 count=0;
				 break;
				 
			 case 4:
				 if(ch==0x0b)
				 {
						UART5_cnt=0;
						RM.thr=Remote.ActVal[0];
						RM.Y=Remote.ActVal[1];
						RM.Z=Remote.ActVal[2];
						RM.X=Remote.ActVal[3];
						RM.KEY1=Remote.ActVal[4];
						RM.KEY2=Remote.ActVal[5];
						RM.KEY3=Remote.ActVal[6];
						RM.KEY4=Remote.ActVal[7];
						RM.KEY5=Remote.ActVal[8];
						RM.KEY6=Remote.ActVal[9];
						RM.KEY7=Remote.ActVal[10];
						RM.KEY8=Remote.ActVal[11];
						RM.KEY9=Remote.ActVal[12];
						RM.KEY10=Remote.ActVal[13];
						RM.KEY11=Remote.ActVal[14];
						RM.KEY12=Remote.ActVal[15];
//						printf("%d %d %d %d  \r\n",RM.thr,RM.Y,RM.Z,RM.X);
//						printf("%d %d %d %d %d %d %d %d %d %d %d %d \r\n",RM.KEY1,RM.KEY2,RM.KEY3,RM.KEY4,RM.KEY5,RM.KEY6,RM.KEY7,RM.KEY8,RM.KEY9,RM.KEY10,RM.KEY11,RM.KEY12);
					 
					 
					 
				 }
			   count=0;
				 break;
			 
			 default:
				 count=0;
			   break;		 
		 }
	 }
}









	

char openmv_yaw_data[8];
char openmv_x_data[8];
char openmv_z_data[8];
float openmv_x=0.0;
float openmv_yaw=0.0;
float openmv_z=0.0;//���

int count_cam=0;
extern uint16_t tag;

//void UART5_IRQHandler(void)                	//����1�жϷ������
//{
//u8 Res;
//	static int i;

//	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		Res =USART_ReceiveData(UART5);//(USART1->DR);	//��ȡ���յ�������
//		
//		tag = 2000;
//		switch(count_cam)
//		{
//			
//			case 0:
//			{
//				if(Res==0x0a) count_cam = 1;
//				else if(Res==0x0b) count_cam = 2;
//				else if(Res==0x0c) count_cam = 3;
//			}break;
//			case 1:
//			{
//				openmv_yaw_data[i] = Res;
//				i++;
//				if(i>=6) 
//					{
//						count_cam = 0,i = 0;
//				    openmv_yaw = atof(openmv_yaw_data);
//					}
//			}break;
//			case 2:
//			{
//				openmv_x_data[i] = Res;
//				i++;
//				if(i>=6) 
//					{
//						count_cam = 0,i = 0;
//				    openmv_x = atof(openmv_x_data)*10.0;
//					}
//			}break;
//			case 3:
//			{
//				openmv_z_data[i] = Res;
//				i++;
//				if(i>=6) 
//					{
//						count_cam = 0,i = 0;
//				    openmv_z = atof(openmv_z_data)*10.0;
//					}
//			}break;
//			
//	  }
//		

//	}
//} 


 



