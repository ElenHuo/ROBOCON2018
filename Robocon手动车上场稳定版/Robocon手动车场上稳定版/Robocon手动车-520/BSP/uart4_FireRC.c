#include "main.h"

//uint16_t LX,LY,RX,RY,AU1,AU2,AU3,KEY_0,KEY_1;


//void UART4_IRQHandler(void)                	//串口1中断服务程序
//{
//	static uint8_t ch;
//	static union
//	{
//		uint8_t data[18];//一个字节
//		uint16_t ActVal[9];//4个字节
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
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART4, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(UART4, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_UART4_RX	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif
}

