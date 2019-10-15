#include "main.h"

//uint16_t LX,LY,RX,RY,AU1,AU2,AU3,KEY_0,KEY_1;


//void UART4_IRQHandler(void)                	//����1�жϷ������
//{
//	static uint8_t ch;
//	static union
//	{
//		uint8_t data[18];//һ���ֽ�
//		uint16_t ActVal[9];//4���ֽ�
//	}Remote;
//	static uint8_t count=0;
//  static uint8_t i=0;

//	if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET)   
//	{
//		USART_ClearITPendingBit( UART4,USART_IT_RXNE);	
//		ch=USART_ReceiveData(UART4);
//		
//		 switch(count)
//		 {
//			 case 0:
//				 if(ch==0x0a)
//					 count++;
//				 else
//					 count=0;
//				 break;
//				 
//			 case 1:
//				 if(ch==0x0a)
//				 {
//					 i=0;
//					 count++;
//				 }
//				 else if(ch==0x0b);
//				 else
//					 count=0;
//				 break;
//				 
//			 case 2:
//				 Remote.data[i]=ch;
//			   i++;
//			   if(i>=18)
//				 {
//					 i=0;
//					 count++;
//				 }
//				 break;
//				 
//			 case 3:
//				 if(ch==0x0b)
//					 count++;
//				 else
//					 count=0;
//				 break;
//				 
//			 case 4:
//				 if(ch==0x0b)
//				 {
//						LY=Remote.ActVal[0];
//						RY=Remote.ActVal[1];
//						LX=Remote.ActVal[2];
//						RX=Remote.ActVal[3];
//						AU1=Remote.ActVal[4];
//						AU2=Remote.ActVal[5];
//						AU3=Remote.ActVal[6];
//						KEY_0=Remote.ActVal[7];
//						KEY_1=Remote.ActVal[8];
//				//		printf("%d %d %d %d %d %d %d %d %d \r\n",LX,LY,RX,RY,AU1,AU2,AU3,KEY_0,KEY_1);
//				 }
//			   count=0;
//				 break;
//			 
//			 default:
//				 count=0;
//			   break;		 
//		 }
//	 }
//}


void uart4_Remoter_init(u32 bound)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(UART4, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_UART4_RX	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
}

