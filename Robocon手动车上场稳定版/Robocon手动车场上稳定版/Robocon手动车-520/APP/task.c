#include "main.h"
#define _PS2_ 0
#define DEBUG 1




/*************************************************************************
                         ��Ҫ����
												 ������������
												 ��λ����
												 ��Ե�����
												 ȡ��-��������
												 �����������(��δ���)

*************************************************************************/

#define BOTH_LED_TOGGLE() GPIO_ToggleBits(GPIOF, GPIO_Pin_9);GPIO_ToggleBits(GPIOF, GPIO_Pin_10)


uint8_t Bsp_Int_Ok = 0;
uint8_t Relay_Count = 0;


/*************************************************************************
							������״̬                   ��Ե�
	
	PREPARE_STATE,                       STARTZONE_TO_TAKE_BALL
	STZ_TO_TAKE,                         TAKEBALL_TO_Tag1
	TAKE_TO_TAG1,                        Tag1_TO_TAKEBALL
	TAG1_TO_TAKE,                        TAKEBALL_TO_Tag2
	TAKE_TO_TAG2,
	
	ALIGN_STATE1
	
	RELAY_STATE1, //�Խ�״̬1
	RELAY_STATE2,
*************************************************************************/


ROBOT_WORKING_STATE 		NOW_STATE = PREPARE_STATE;

ROBOT_WORKING_STATE     LAST_STATE =PREPARE_STATE;

Tracking_STATE 					TRACKING_STATE = TRACKING_UNKNOWN;

TakeBall_STATE 					TAKEBALL_STATE = TAKING_UNKOWN;

Align_STATE  						ALIGN_STATE = ALIGN_UNKNOWN;

Relay_STATE		 					RELAY_STATE = RELAY_UNKNOWN;

POINT 									*NOW_TRAJECTORY;//��ǰ�켣












void STATE_MACHINE_TASK(void)
{

	
				
			switch (NOW_STATE)
			{
				case PREPARE_STATE:
				{
					if(Bsp_Int_Ok == 1)  
					{
						NOW_STATE = STZ_TO_TAKE;
						NOW_TRAJECTORY = &STARTZONE_TO_TAKE_BALL;  //��ʼ���켣
						TRACKING_STATE = TRACKING_GOING;
					}
				}break;
				
				
				case STZ_TO_TAKE:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED)
					{
						if(TZ3_COUNT==0)	NOW_STATE = TAKE_BALL_STATE1;//����ȡ��״̬���ȴ�ȡ���־
						else
						{					
							NOW_STATE = TAKE_BALL_STATE2;
							TZ3_COUNT=0;
						}
						
						
						TRACKING_STATE = TRACKING_UNKNOWN;
						
//				  	TAKEBALL_STATE =TAKING_GOING;//ȫ�Զ�
						
   						TAKEBALL_STATE=TAKING_UNKOWN;//���Զ�
//						printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);

					}
					
				}break;
				

				
				
				case TAKE_TO_TAG1:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED) //����TZ1
					{
						NOW_STATE = ALIGN_STATE1;
						TRACKING_STATE = TRACKING_UNKNOWN;
   					ALIGN_STATE=ALIGN_GOING; //ȫ�Զ�
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
						
//			  	TAKEBALL_STATE =TAKING_GOING;//ȫ�Զ�
						TAKEBALL_STATE=TAKING_UNKOWN;//���Զ�
//						printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);
					}
					
				}break;
				
				case TAG1_TO_TAKE_Failed:
				{
					if(TRACKING_STATE == TRACKING_ARRIVED)
					{
						NOW_STATE=TAKE_BALL_STATE1;
						
						TRACKING_STATE = TRACKING_UNKNOWN;
						
//			  	TAKEBALL_STATE =TAKING_GOING;//ȫ�Զ�
						TAKEBALL_STATE=TAKING_UNKOWN;//���Զ�
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
						
  					ALIGN_STATE=ALIGN_GOING; //ȫ�Զ�
						
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
						
//			  	TAKEBALL_STATE =TAKING_GOING;//ȫ�Զ�
						TAKEBALL_STATE=TAKING_UNKOWN;//���Զ�
//						printf("X : %5f Y: %5f \r\n", -ROBOT_POSITION.Y_POS, ROBOT_POSITION.X_POS);
					}
				}break;
				
				case TAKE_BALL_STATE1:
				{
					 if(TAKEBALL_STATE == TAKING_DONE )
					 {
						 NOW_STATE=TAKE_TO_TAG1;
						 
//		       TRACKING_STATE=TRACKING_GOING;//�Զ�
						 
						 TRACKING_STATE=TRACKING_UNKNOWN;//���Զ�
						 
						 NOW_TRAJECTORY = &TAKEBALL_TO_Tag1;//��
						 TAKEBALL_STATE = TAKING_UNKOWN;
						 

					 }

				}break;
				
				case TAKE_BALL_STATE2:
				{
					 if(TAKEBALL_STATE == TAKING_DONE )
					 {
						 NOW_STATE=TAKE_TO_TAG2;
						
//	   			 TRACKING_STATE=TRACKING_GOING;//�Զ�
						 
					   TRACKING_STATE=TRACKING_UNKNOWN;//���Զ�
						 
						 NOW_TRAJECTORY = &TAKEBALL_TO_Tag2;//��
						 
						 TAKEBALL_STATE = TAKING_UNKOWN;

					 }

					
				}break;
				

				
				case ALIGN_STATE1:
				{
					if(ALIGN_STATE==ALIGN_DONE)
					{
						NOW_STATE=RELAY_STATE1;//����Խ�״̬1����������
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
						NOW_STATE = RELAY_STATE2;  //�ȴ��ڶ��ν���
						RELAY_STATE=RELAY_UNKNOWN; //�������񣬴��������سɹ���������һ�ν���
					}
					
				}break;
				
				case RELAY_STATE2: //���Ƶڶ��ν��ӣ�
				{
					if(RELAY_STATE==RELAY_SUCCEEDED) //ң���ֶ�ȷ������ɹ����ֶ����Ƹ�������״̬��ɣ�ȥȡ��
					{
						if(Relay_Count==0)
						{
		

						NOW_STATE =TAG1_TO_TAKE;

						NOW_TRAJECTORY=&Tag1_TO_TAKEBALL;

						TRACKING_STATE=TRACKING_GOING;
							
						RELAY_STATE=RELAY_UNKNOWN;
							
						Relay_Count++;  //TZ1������θ�������ȥȡ����еڶ���ȡ������
						
						}
						else if(Relay_Count==1) //TZ2��������״̬�ɹ�
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
	
	CAN_RoboModule_DRV_Reset(0,0);                      //��0���������������и�λ 
	delay_ms(500); 
	
	CAN_RoboModule_DRV_Config(0,1,100,0);               //0��1������������Ϊ100ms����һ������
	CAN_RoboModule_DRV_Mode_Choice(0,0,Velocity_Mode);  //0������������������ٶ�ģʽ
	delay_ms(500); 
	
	LED_Init();
	
		


	Bsp_Int_Ok = 1;
	
#if usart1_ANO
	IWDG_Init(2,625); //ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).���Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s	
	DMA2_Config(DMA2_Stream7,DMA_Channel_4,(u32)&USART1->DR,(u32)USART_RX_BUF,USART_REC_LEN);	
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����
#endif
	
#if usart1_XCOM	
	printf("Init is ok!\n");
#endif

}

void Task_1000HZ(void)
{
	
	STATE_MACHINE_TASK();
	RM_TASK();
	Semi_Auto();//�ֶ�ģʽ�µİ��Զ����������
	pos_update();
	TRACKING_TASK(NOW_TRAJECTORY);//��Ե㵼������
	
	TAKEBALL_TASK();//��������
	
	ALIGN_TASK();//��λ����
	
	RELAY_TASK();//��������
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
	IWDG_Feed();//ι��
#endif
	
	BOTH_LED_TOGGLE();

}

void Task_2HZ(void)
{
#if usart1_XCOM

#endif

}
