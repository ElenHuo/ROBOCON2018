#include "main.h"

extern PID TAKEBALL_PID;
uint8_t TZ1_Count;
uint8_t  TZ3_COUNT;
uint8_t OFFSET_STOP;

void RM_TASK(void)
{
	//模式转换判断
	Mode_Judge();
	Auto_Relay();
	switch(REMOTE)
	{
		
		case HAND_MODE:
		{
		
			 RM_Output();
			 if(Semi_Count==1)
			 {
				PID_Cal(&TAKEBALL_PID,target_position,Real_Position_Value[0],POSITION_PID);//tar,current ,mode
				speed=-TAKEBALL_PID.pos_out;
				if(speed>2000)speed=2000;
				if(abs((Real_Position_Value[0]-target_position))<10000)
				{
					speed=1500;
				}
			  if(abs((target_position-Real_Position_Value[0]))<take_shreshold) //需要测试当前的位置量
				{
					speed=0;
					Semi_Count=0;
				}
				CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,speed);
			}
			 
		   else if(Semi_Count==2)
			 {
					 PID_Cal(&TAKEBALL_PID,relay_target_position,Real_Position_Value[0],POSITION_PID);//tar,current ,mode
					
			
				 Speed_Relay=-TAKEBALL_PID.pos_out;
//				 if(Speed_Relay>2000)Speed_Relay=2000;
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
//	  		 if(Speed_Relay>2000)Speed_Relay=2000;
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
			
			if(RM.KEY1==0&& (NOW_STATE==TAKE_BALL_STATE1 || NOW_STATE==TAKE_BALL_STATE2))	//circle key
			{
				TAKEBALL_STATE =TAKING_GOING;
			}
			else if(RM.KEY2==0 && (NOW_STATE==TAKE_TO_TAG1 || NOW_STATE==TAKE_TO_TAG2 )) //三角形
			{
			

					if(Distance_Count==0)
				 {
					 Calculate_Distance(&TAKEBALL_TO_Tag1,&TAKE_TAG1);

										
					 Distance_Count++;
				
					 
				 }

				 else if(Distance_Count==1)
				 {
				  Calculate_Distance(&TAKEBALL_TO_Tag2,&TAKE_TAG2);
			
					
				 }


					TRACKING_STATE=TRACKING_GOING;
			}
			else if(RM.KEY3==0 && (NOW_STATE==ALIGN_STATE1 ||  NOW_STATE==ALIGN_STATE2)) //XXX
			{
					ALIGN_STATE=ALIGN_DONE;	
			}
			else if(RM.KEY4==0 && (NOW_STATE==RELAY_STATE2))///正方形
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

			else if(RM.KEY6==0 && TAKEBALL_STATE==TAKING_GOING ) 
			{
				 TAKEBALL_STATE=TAKING_DONE;
			}
			//throw failed and take ball
			
			else if(RM.KEY12==0 && (NOW_STATE==RELAY_STATE1 ||NOW_STATE==RELAY_STATE2))
			{
					Calculate_Distance(&Tag1_TO_TAKEBALL,&TAG1_TAKE);
					NOW_STATE=RELAY_STATE3;
				
			}
			
			else if(RM.KEY1==0 && (NOW_STATE==ALIGN_STATE1 ||  NOW_STATE==ALIGN_STATE2))
			{
				TZ1_Count=1;
				
			}
			else if(RM.KEY2==0 && (NOW_STATE==ALIGN_STATE1 ||  NOW_STATE==ALIGN_STATE2))
			{
				TZ1_Count=2;
			}			
			else if(RM.KEY12==0 && (TRACKING_STATE==TRACKING_GOING))
			{
				TRACKING_STATE =TRACKING_ARRIVED;
				Vx=Vy=0;
			}
		}break;
		
		default:{}

	}
	

}


void Auto_Relay(void)
{
	
	 if(TZ1_Count==1)
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
			  	TZ1_Count=0;
				}
		 CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Speed_Relay);
	 }
	 else if(TZ1_Count==2)
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
					TZ1_Count=0;
				}
				CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Speed_Relay);		 
	 }
}


void Mode_Judge(void)
{
	if(RM.KEY11==0)
	{
		Mode_Count++;
		delay_ms(200);
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


void RM_OFFSET(void)//thr 1000-2020, Y 1000-2000 set 1528, X 1000-2000 Z 1000-2000	
{
	if(RM.thr<1050)RM.thr=1000;
	if(1450<RM.Y && RM.Y<1550)RM.Y=1500;
	if(1450<RM.X && RM.X<1550)RM.X=1500;
	if(1450<RM.Z && RM.Z<1550)RM.Z=1500;
}

void RM_Auto_Offset (void)
{
	static uint8_t K=4.0f;
		RM_OFFSET();
		Vx=(RM.X-1500)*K;
		Vy=(RM.Y-1500)*K;
		Vz=(RM.Z-1500)*1.0f;// 自转速度恒定
		offset_angle=ROBOT_POSITION.ANGLE_POS;
}


void RM_Output(void)
{
	
	float K;
	if(RM.KEY3==0)
	{
		Hand_speed=2800;
		if(abs((Real_Position_Value[0]-relay_target_position))<deceleration_relay)
		{
			Hand_speed=1500;
		}
		
	}
	else if(RM.KEY4==0)
	{
		Hand_speed=-2800;
		if((offset_position-Real_Position_Value[0])<deceleration_offset)
		{
			Hand_speed=-2000;
		}
	}
	
 
	else if(RM.KEY5==0) 
			{
				 NOW_STATE=PREPARE_STATE;
				 Mode_Count++;
				 TZ3_COUNT=1;
				 
				
			}
	else
	{
		Hand_speed=0;
	}
	if(Init_flag==0 &&Semi_Count==0)	CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Hand_speed);
	


	RM_OFFSET();
  K=(RM.thr-1000)*0.012f;//油门打满最高速为5000
	
	Vx=(RM.X-1500)*K;
	Vy=(RM.Y-1500)*K;
	Vz=(RM.Z-1500)*0.7f;// 自转速度恒定
	theta=90+ROBOT_POSITION.ANGLE_POS;	
	
// Theta_Hold();//姿态闭环

}

void Point_RM_Output(void)
{
	RM_OFFSET();
	Vy=(RM.Y-1500)*5.0f;
}



