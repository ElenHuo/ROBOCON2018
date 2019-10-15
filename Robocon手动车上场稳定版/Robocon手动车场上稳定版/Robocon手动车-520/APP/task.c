#include "main.h"
#define _PS2_ 0
#define DEBUG 1




/*************************************************************************
                         主要任务：
												 底盘行走任务、
												 对位任务
												 点对点任务
												 取球-交接任务
												 特殊情况任务(尚未完成)

*************************************************************************/

#define BOTH_LED_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_9);GPIO_ToggleBits(GPIOF, GPIO_Pin_10)


uint8_t Bsp_Int_Ok = 0;
uint8_t Relay_Count = 0;


/*************************************************************************
							机器人状态                   点对点
	
	PREPARE_STATE,                       STARTZONE_TO_TAKE_BALL
	STZ_TO_TAKE,                         TAKEBALL_TO_Tag1
	TAKE_TO_TAG1,                        Tag1_TO_TAKEBALL
	TAG1_TO_TAKE,                        TAKEBALL_TO_Tag2
	TAKE_TO_TAG2,
	
	ALIGN_STATE1
	
	RELAY_STATE1, //对接状态1
	RELAY_STATE2,
*************************************************************************/


ROBOT_WORKING_STATE 		NOW_STATE = PREPARE_STATE;

ROBOT_WORKING_STATE     LAST_STATE =PREPARE_STATE;

Tracking_STATE 					TRACKING_STATE = TRACKING_UNKNOWN;

TakeBall_STATE 					TAKEBALL_STATE = TAKING_UNKOWN;

Align_STATE  						ALIGN_STATE = ALIGN_UNKNOWN;

Relay_STATE		 					RELAY_STATE = RELAY_UNKNOWN;

POINT 									*NOW_TRAJECTORY;//当前轨迹












void STATE_MACHINE_TASK(void)
{

	
				
			switch (NOW_STATE)
			{
				case PREPARE_STATE:
				{
					if(Bsp_Int_Ok == 1)  
					{
						NOW_STATE = STZ_TO_TAKE;
						NOW_TRAJECTORY = &STARTZONE_TO_TAKE_BALL;  //初始化轨迹
						TRACKING_STATE = TRACKING_GOING;
					}
				}break;
				
				
				case STZ_TO_TAKE:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED)
					{
						if(TZ3_COUNT==0)	NOW_STATE = TAKE_BALL_STATE1;//进入取球状态，等待取球标志
						else
						{					
							NOW_STATE = TAKE_BALL_STATE2;
							TZ3_COUNT=0;
						}
						
						
						TRACKING_STATE = TRACKING_UNKNOWN;
						
//				  	TAKEBALL_STATE =TAKING_GOING;//全自动
						
   						TAKEBALL_STATE=TAKING_UNKOWN;//半自动
//						printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);

					}
					
				}break;
				

				
				
				case TAKE_TO_TAG1:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED) //到达TZ1
					{
						NOW_STATE = ALIGN_STATE1;
						TRACKING_STATE = TRACKING_UNKNOWN;
   					ALIGN_STATE=ALIGN_GOING; //全自动
//						ALIGN_STATE=ALIGN_UNKNOWN;
//printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);
					}

				}break;
				
				case TAG1_TO_TAKE:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED)
					{
						NOW_STATE=TAKE_BALL_STATE2;
						
						TRACKING_STATE = TRACKING_UNKNOWN;
						
//			  	TAKEBALL_STATE =TAKING_GOING;//全自动
						TAKEBALL_STATE=TAKING_UNKOWN;//半自动
//						printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);
					}
					
				}break;
				
				case TAG1_TO_TAKE_Failed:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED)
					{
						NOW_STATE=TAKE_BALL_STATE1;
						
						TRACKING_STATE = TRACKING_UNKNOWN;
						
//			  	TAKEBALL_STATE =TAKING_GOING;//全自动
						TAKEBALL_STATE=TAKING_UNKOWN;//半自动
						Relay_Count=0;
						Distance_Count=0;
						Back_Count=0;
					}
					
				}break;
				
				case TAKE_TO_TAG2:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED)
					{
						NOW_STATE=ALIGN_STATE2;
						TRACKING_STATE = TRACKING_UNKNOWN;
						
  					ALIGN_STATE=ALIGN_GOING; //全自动
						
//						ALIGN_STATE=ALIGN_UNKNOWN;
//						printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);
						
					}
				}break;
				
				case TAG2_TO_TAKE:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED)
					{
						NOW_STATE=TAKE_BALL_STATE2;
						
						TRACKING_STATE = TRACKING_UNKNOWN;
						
//			  	TAKEBALL_STATE =TAKING_GOING;//全自动
						TAKEBALL_STATE=TAKING_UNKOWN;//半自动
//						printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);
					}
				}break;
				
				case TAKE_BALL_STATE1:
				{
					 if(TAKEBALL_STATE == TAKING_DONE )
					 {
						 NOW_STATE=TAKE_TO_TAG1;
						 
//		       TRACKING_STATE=TRACKING_GOING;//自动
						 
						 TRACKING_STATE=TRACKING_UNKNOWN;//半自动
						 
						 NOW_TRAJECTORY = &TAKEBALL_TO_Tag1;//点
						 TAKEBALL_STATE = TAKING_UNKOWN;
						 

					 }

				}break;
				
				case TAKE_BALL_STATE2:
				{
					 if(TAKEBALL_STATE == TAKING_DONE )
					 {
						 NOW_STATE=TAKE_TO_TAG2;
						
//	   			 TRACKING_STATE=TRACKING_GOING;//自动
						 
					   TRACKING_STATE=TRACKING_UNKNOWN;//半自动
						 
						 NOW_TRAJECTORY = &TAKEBALL_TO_Tag2;//点
						 
						 TAKEBALL_STATE = TAKING_UNKOWN;

					 }

					
				}break;
				

				
				case ALIGN_STATE1:
				{
					if(ALIGN_STATE==ALIGN_DONE)
					{
						NOW_STATE=RELAY_STATE1;//进入对接状态1，给球任务
						ALIGN_STATE=ALIGN_UNKNOWN;
						RELAY_STATE= RELAY_GOING;
						
					}
					
				}break;
					
				case ALIGN_STATE2:
				{
					if(ALIGN_STATE==ALIGN_DONE)
					{
						NOW_STATE=RELAY_STATE1; //RELAY_STATE 1
						ALIGN_STATE=ALIGN_UNKNOWN;
						RELAY_STATE= RELAY_GOING;
					}
					
				}break;
					

				
				case RELAY_STATE1:
				{
					if(RELAY_STATE == RELAY_SUCCEEDED) 
					{
						NOW_STATE = RELAY_STATE2;  //等待第二次接球
						RELAY_STATE=RELAY_UNKNOWN; //给球任务，触碰到开关成功，进行下一次交接
					}
					
				}break;
				
				case RELAY_STATE2: //控制第二次交接，
				{
					if(RELAY_STATE==RELAY_SUCCEEDED) //遥控手动确定给球成功，手动控制给球任务状态完成，去取球
					{
						if(Relay_Count==0)
						{
		

						NOW_STATE =TAG1_TO_TAKE;

						NOW_TRAJECTORY=&Tag1_TO_TAKEBALL;

						TRACKING_STATE=TRACKING_GOING;
							
						RELAY_STATE=RELAY_UNKNOWN;
							
						Relay_Count++;  //TZ1完成两次给球任务，去取球进行第二次取球任务
						
						}
						else if(Relay_Count==1) //TZ2给球任务状态成功
						{

							
						NOW_STATE =TAG2_TO_TAKE;

							
						NOW_TRAJECTORY=&Tag2_TO_TAKEBALL;
							
	
						TRACKING_STATE=TRACKING_GOING;
							
						RELAY_STATE=RELAY_UNKNOWN;					
							
						}
						
						
						
					}
					
				}break;
				
				case RELAY_STATE3:
				{
					
						NOW_STATE =TAG1_TO_TAKE_Failed;

						NOW_TRAJECTORY=&Tag1_TO_TAKEBALL;

						TRACKING_STATE=TRACKING_GOING;
							
						RELAY_STATE=RELAY_UNKNOWN;
					
				}break;
				
				default:{}
		
			}
		

}







void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}


void BSP_Init(void)
{
	Timer2_Init(1000);
	Nvic_Init();
//	PPM_EXTIX_Init();
//	TIM1_CH1_PWM_Init(20000-1,83);
	
	uart_init(115200);

	uart4_init(115200);
	uart5_init(115200);
	
	LOCALIZATION_INIT();
	tracking_init();
	takeball_init();
	Switch_Init();
	
	PS2_Init();
	PS2_SetInit();
	
	CAN1_Configuration();
	CAN2_Configuration();
	
	CAN_RoboModule_DRV_Reset(0,0);                      //对0组所有驱动器进行复位 
	delay_ms(500); 
	
	CAN_RoboModule_DRV_Config(0,1,100,0);               //0组1号驱动器配置为100ms传回一次数据
	CAN_RoboModule_DRV_Mode_Choice(0,0,Velocity_Mode);  //0组的所有驱动器进入速度模式
	delay_ms(500); 
	
	LED_Init();
	
		


	Bsp_Int_Ok = 1;
	
#if usart1_ANO
	IWDG_Init(2,625); //时间计算(大概):Tout=((4*2^prer)*rlr)/32 (ms).与分频数为64,重载值为500,溢出时间为1s	
	DMA2_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)USART_RX_BUF,USART_REC_LEN);	
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发送
#endif
	
#if usart1_XCOM	
	printf("Init is ok!\n");
#endif

}

void Task_1000HZ(void)
{
	
	STATE_MACHINE_TASK();
	RM_TASK();
	Semi_Auto();//手动模式下的半自动拿球给球动作
	pos_update();
	TRACKING_TASK(NOW_TRAJECTORY);//点对点导航任务
	
	TAKEBALL_TASK();//拿球任务
	
	ALIGN_TASK();//对位任务
	
	RELAY_TASK();//交接任务
	CAN1_REMOTE_CHECK();


	
	
	

}


void Task_500HZ(void)
{

	Take_Motor_Init();
}

void Task_250HZ(void)
{
	
	Chassis_control(Vx,Vy,Vz,theta);
}

void Task_200HZ(void)
{
	
	
	 Switch_scan();
	 Led_State_Test();
	 
}

void Task_50HZ(void)
{


#if DEBUG

	printf("X : %5f  Vx:%5f  POS:%5f \r\n", -ROBOT_POSITION.Y_POS,Vx,Real_Position_Value[0]);

	
#endif
	
	scope(Vx,K1,K2);
		
}

void Task_20HZ(void)
{
	
}

void Task_10HZ(void)
{
#if usart1_ANO
	Prepare_Data_1();
	DMA2_Enable(DMA2_Stream7,40); 
	if(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7)!=RESET)
	{ 
		DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);
	}
	IWDG_Feed();//喂狗
#endif
	
	BOTH_LED_TOGGLE();

}

void Task_2HZ(void)
{
#if usart1_XCOM

#endif

}
