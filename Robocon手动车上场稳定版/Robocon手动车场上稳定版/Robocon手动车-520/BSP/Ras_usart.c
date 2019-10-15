#include "main.h"

_Remote_ RM;
uint16_t tag;
void uart5_init(u32 bound)
	{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //GPIOA9与GPIOA10  //TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA9，PA10
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOA9与GPIOA10  //RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PA9，PA10
	
	
   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART5, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(UART5, ENABLE);  //使能串口1 
	

	
#if EN_UART5_RX	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif
}


uint16_t UART5_cnt;
void UART5_IRQHandler(void)                	//串口1中断服务程序
{
	static uint8_t ch;
	static union
	{
		uint8_t data[32];//一个字节
		uint16_t ActVal[16];//2个字节
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
float openmv_z=0.0;//深度

int count_cam=0;
extern uint16_t tag;

//void UART5_IRQHandler(void)                	//串口1中断服务程序
//{
//u8 Res;
//	static int i;

//	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//		Res =USART_ReceiveData(UART5);//(USART1->DR);	//读取接收到的数据
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


 



