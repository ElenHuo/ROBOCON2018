#include "main.h"
extern PID TAKEBALL_PID;
uint8_t Mode_Count=0;
uint8_t Mode_Change;
uint8_t PS2_Key;
int8_t K=1.5;
uint8_t Semi_Count=0;
uint8_t stop_shreold=0;
int16_t Hand_speed;

REMOTE_STATE REMOTE=HAND_MODE;
uint8_t Distance_Count=0;
uint8_t Back_Count=0;

void PS2_TASK(void)
{
	switch(REMOTE)
	{
		
		case HAND_MODE:
		{
		
			 PS2_Remote_Output();

			 
		   if(Semi_Count==2)
			 {
					 PID_Cal(&TAKEBALL_PID,relay_target_position,Real_Position_Value[0],POSITION_PID);//tar,current ,mode
					
			
				 Speed_Relay=-TAKEBALL_PID.pos_out;
				if(abs((Real_Position_Value[0]-relay_target_position))<deceleration_relay)
				{
					Speed_Relay=1500;
				}
					if(SW_R==1)
					{
						Speed_Relay=0;
						Semi_Count=0;
					}
					CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Speed_Relay);
				}
			 else if(Semi_Count==3)
			 {
				 
				PID_Cal(&TAKEBALL_PID,(offset_position+2000),Real_Position_Value[0],POSITION_PID);//tar,current ,mode
				Speed_Relay=-TAKEBALL_PID.pos_out;
				 if((offset_position-Real_Position_Value[0])<deceleration_offset)
				{
					Speed_Relay=-1500;
				}
				if(SW_L==1)
				{
					Speed_Relay=0;
					offset_position=Real_Position_Value[0];
					Semi_Count=0;
				}
				CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Speed_Relay);
			 }
	//		printf("%5f  %d\r\n",speed,abs((target_position-Real_Position_Value[0])));
			
			
		}break;
		
		
		case AUTO_MODE:
		{
			
			if(PS2_Key==14 && (NOW_STATE==TAKE_BALL_STATE1 || NOW_STATE==TAKE_BALL_STATE2))	//circle key
			{
				TAKEBALL_STATE =TAKING_GOING;
			}
			else if(PS2_Key==13 && (NOW_STATE==TAKE_TO_TAG1 || NOW_STATE==TAKE_TO_TAG2 )) //三角形
			{
			

					if(Distance_Count==0)
				 {
					 Calculate_Distance(&TAKEBALL_TO_Tag1,&TAKE_TAG1);
					 printf("TZ1:%5f \r\n",TAKE_TAG1);
										
					 Distance_Count++;
				
					 
				 }

				 else if(Distance_Count==1)
				 {
				  Calculate_Distance(&TAKEBALL_TO_Tag2,&TAKE_TAG2);
				  printf("TZ2:%5f \r\n",TAKE_TAG2);
				
					
				 }


					TRACKING_STATE=TRACKING_GOING;
			}
			else if(PS2_Key==15 && (NOW_STATE==ALIGN_STATE1 ||  NOW_STATE==ALIGN_STATE2)) //XXX
			{
					ALIGN_STATE=ALIGN_DONE;	
			}
			else if(PS2_Key==16 && (NOW_STATE==RELAY_STATE1 ||NOW_STATE==RELAY_STATE2))///正方形
			{
					
				  if(Back_Count==0)
				 {
					Calculate_Distance(&Tag1_TO_TAKEBALL,&TAG1_TAKE);

					 Back_Count++;
				 }

					if(Back_Count==1)
				 {
					 
					Calculate_Distance(&Tag2_TO_TAKEBALL,&TAG2_TAKE);

									 
				 }
				 RELAY_STATE=RELAY_SUCCEEDED;
			}
			
			//special situation
			else if(PS2_Key==11 && TRACKING_STATE==TRACKING_GOING) //L1
			{
				 TRACKING_STATE =TRACKING_ARRIVED;
			}
			else if(PS2_Key==9  && TAKEBALL_STATE==TAKING_GOING ) //L2
			{
				 TAKEBALL_STATE=TAKING_DONE;
			}
			//throw failed and take ball
			else if(PS2_Key==PSB_R1 && (NOW_STATE==RELAY_STATE1 ||NOW_STATE==RELAY_STATE2))
			{
				
				NOW_STATE=RELAY_STATE3;
				
			}
			
		}break;
		
		default:{}

	}
	

		
		
	
	
	
}

void Semi_Auto(void)//手动模式下的半自动
{
	
	if(REMOTE==HAND_MODE && (RM.KEY12==0))Semi_Count=1;
  else if(REMOTE==HAND_MODE && (PS2_Key==16|| RM.KEY1==0))Semi_Count=2;
	
	else if(REMOTE==HAND_MODE && (PS2_Key==14||RM.KEY2==0))Semi_Count=3;

	
}

void PS2_Auto_Offset (void)
{
		uint8_t LX,RX,LY,RY;
		LX=PS2_AnologData(PSS_LX);
		RX=PS2_AnologData(PSS_RX);
		LY=PS2_AnologData(PSS_LY);
		RY=PS2_AnologData(PSS_RY); //0-255
		if(LX==0 && RX==0 && LY==0 && RY==0)
		{
			Vx=Vy=0;
		}
		else if(LX==0 && LY==0) LX=LY=128;
		else
		{
			Vx=(LX-128)*8.0f; 
			Vy=(128-LY)*8.0f;
			Vz=(RX-128)*2.5f;
		}
		
		offset_angle=ROBOT_POSITION.ANGLE_POS;
		
		
		
	
	
}

void PS2_Remote_Output(void) //1500 3000 500
{
	
		uint8_t LX,RX,LY,RY;
	


//	 if(PS2_Key==14)Vz=300;
//	 else if(PS2_Key==16)
//	{
//		Vz=-300;
//	}
	 if(PS2_Key==13)
	{
		Hand_speed=3500;
		if(abs((Real_Position_Value[0]-relay_target_position))<deceleration_relay)
		{
			Hand_speed=1500;
		}
		
	}
	else if(PS2_Key==15)
	{
		Hand_speed=-3500;
		if((offset_position-Real_Position_Value[0])<deceleration_offset)
		{
			Hand_speed=-1500;
		}
	}
	else
	{
		Hand_speed=0;
	}
	

		LX=PS2_AnologData(PSS_LX);
		RX=PS2_AnologData(PSS_RX);
		LY=PS2_AnologData(PSS_LY);
		RY=PS2_AnologData(PSS_RY); //0-255
	
		if(LX==0 && RX==0 && LY==0 && RY==0)
		{
			Vx=Vy=0;
		}
		else if(LX==0 && LY==0) LX=LY=128;
		else
		{
			if(stop_shreold==0)
			{	
				Vx=K*(LX-128)*6.25f;
				Vy=K*(128-LY)*6.25f;
			}
			

		}
		Theta_Hold();
		
//	theta=90+ROBOT_POSITION.ANGLE_POS;
			
			
		if(Init_flag==0 &&Semi_Count==0)	CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Hand_speed);
		
		
//	printf("%5f Vx: %5f\r\n",Vz,Vx);
//	printf("%d\r\n",PS2_Key);
//	printf("%d %d %d %d \r\n",LX,RX,LY,RY);

	
}

void Point_PS2_Output(void)
{
	uint8_t LY;
	PS2_ClearData();
	PS2_ReadData();
	LY=PS2_AnologData(PSS_LY);
	Vy=(128-LY)*15.0f;
	
}

void PS2_KEY_SCAN(void)
{
	PS2_Key=PS2_DataKey();
	if(PS2_Key==10)
	{
		
		Mode_Count++;
		delay_ms(200);
		stop_shreold=1;
		
	}
	else if(PS2_Key==9) //逐渐加减速
	{
		K+=2;
		if(K>4)K=4;
		delay_ms(300);
		stop_shreold=1;
	}
	else if(PS2_Key==11)
	{
		K-=2;
		if(K<1)K=1;
		delay_ms(300);
	}
	else if(PS2_Key==3)//最高速
	{
		K=4;
	}
	else if(PS2_Key==2)//最低速
	{
		K=1;
	}
  else 
	{
		stop_shreold=0;
	}
	
	Mode_Change=Mode_Count%2;

	if(Mode_Change==0)
	{
		REMOTE=HAND_MODE;
	}
	else if(Mode_Change==1)
	{
		REMOTE=AUTO_MODE;
	}
		
	
}

