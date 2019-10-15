#include "main.h"
#include "WFLY_REMOTE.h"


uint8_t flag_0=0;
uint8_t flag_1=1;
uint8_t Count=0;
int16_t WFLY_VX,WFLY_VY,WFLY_VZ,K_Speed;



 

void WFLY_Remote_Task(void)
{

	
	
      // A	
			if(PPM_Databuf[7]>1500 || PPM_Databuf[7]>2018)  
			{
				WFLY_Output();
			}

			else if(PPM_Databuf[4]<1200 && (PPM_Databuf[5]>1700 && PPM_Databuf[5] <=2000) && (NOW_STATE==TAKE_BALL_STATE1 || NOW_STATE==TAKE_BALL_STATE2) ) // 2 
			{
					TAKEBALL_STATE =TAKING_GOING;//已进入取球区，进行取球任务
			}


			else if(PPM_Databuf[4]<1200 && (PPM_Databuf[5]>1300 && PPM_Databuf[5] <=1700) && (NOW_STATE==TAKE_TO_TAG1 || NOW_STATE==TAKE_TO_TAG2 )) 
			{

						 
							 if(Count==0)
							 {
//									Calculate_Distance_TZ1();
								 printf("TZ1:%5f \r\n",TAKE_TAG1);
								  
								 Count++;
							 }
							 else if(Count==1)
							 {
//								 Calculate_Distance_TZ2();
								 printf("TZ2:%5f \r\n",TAKE_TAG2);
								 
							 }

								TRACKING_STATE=TRACKING_GOING;
			 }


			else if(PPM_Databuf[4]<1200 && (PPM_Databuf[5]>=1000 && PPM_Databuf[5] <1300) && (NOW_STATE==ALIGN_STATE1 ||  NOW_STATE==ALIGN_STATE2))  //1-2-1-2
			{
					
								ALIGN_STATE=ALIGN_DONE;	
			}
					
			
		  else if(PPM_Databuf[6]<1300 && (PPM_Databuf[5]>=1000 && PPM_Databuf[5] <1300) &&(NOW_STATE==RELAY_STATE1 ||NOW_STATE==RELAY_STATE2)) //C按键打下
		 {

								RELAY_STATE=RELAY_SUCCEEDED;

	  	}
	    else if(PPM_Databuf[6]<1300 && (PPM_Databuf[5]>1300 && PPM_Databuf[5] <=1700) && TRACKING_STATE==TRACKING_GOING) 
				{
					TRACKING_STATE =TRACKING_ARRIVED;
				}
		  else if(PPM_Databuf[6]<1300 && (PPM_Databuf[5]>1700 && PPM_Databuf[5] <=2000) && TAKEBALL_STATE==TAKING_GOING ) 
				{
					TAKEBALL_STATE=TAKING_DONE;
				}
			
			
		
}



void WFLY_Output(void)
{
	if(1300<PPM_Databuf[2]&&PPM_Databuf[2]<1700)	PPM_Databuf[2]=1500;
	if(1300<PPM_Databuf[3]&&PPM_Databuf[3]<1700)	PPM_Databuf[3]=1500;
	if(1300<PPM_Databuf[0]&&PPM_Databuf[0]<1700)  PPM_Databuf[0]=1500;
	
		WFLY_VX=1500-PPM_Databuf[3];
	
		WFLY_VY=PPM_Databuf[2]-1500;
	
		WFLY_VZ=1500-PPM_Databuf[0];
	
		K_Speed=(PPM_Databuf[1]-1000)/60;
	
		Vx=(float)(WFLY_VX*K_Speed);
		Vy=(float)(WFLY_VY*K_Speed);
		Vz=(float)(WFLY_VZ*K_Speed);
		
	  //offset_angle=ROBOT_POSITION.ANGLE_POS;
		
  	
		
}



