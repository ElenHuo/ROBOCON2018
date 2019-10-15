#include "main.h"
#include "path.h"

//               X
//               |
//               |
//������  Y-------
extern PID TAKEBALL_PID;
float K1,K2;
#define pos_stop_threshold    (20.0f) ///�켣����Ŀ��������پ����л���ֵ,STOP

//POINT
//STARTZONE_TO_TAKE_BALL  TAKEBALL_TO_Tag1  Tag1_TO_TAKEBALL TAKEBALL_TO_Tag2
GOAL_ERRORS goal_errors;

PID PTP;//��Ե�PID
float START_TAKE,TAKE_TAG1,TAG1_TAKE,TAKE_TAG2,TAG2_TAKE;
 
struct 
{
	float X;
	float Y;
	
}Robot_POSITION;



//trapezoid_param TRAPEZOID_PARAM;//���α���

trapezoid_param TRAPEZOID_STZ_TAKE={8000.0,900.0,0.15}//�������ֵ����Сֵ�����ٶ�ϵ��
							,TRAPEZOID_TAKE_TAG1={9000.0,700.0,0.1} //700�ٶ��ȶ�
							,TRAPEZOID_TAG1_TAKE={9000.0,700.0,0.1}
							,TRAPEZOID_TAKE_TAG2={9000.0,700.0,0.1}
							,TRAPEZOID_TAG2_TAKE={9000.0,700.0,0.1};

																				

				
void TRACKING_TASK(struct POINT *POINTS)
{

	if(REMOTE==AUTO_MODE)
	{
	if(TRACKING_STATE==TRACKING_GOING)
	{
		switch(NOW_STATE)
	{
		case STZ_TO_TAKE:
		{
		
			track_point(POINTS);//�������

			Velocity_Calculate_STZ(&TRAPEZOID_STZ_TAKE,START_TAKE);
			
		}break;
		case TAKE_TO_TAG1:
		{			
			track_point(POINTS);
			Velocity_Calculate(&TRAPEZOID_TAKE_TAG1,TAKE_TAG1,POINTS);
			if(Robot_POSITION.X>0)
			{

				Speed_Relay=-1500;
				
				if(SW_L==1)
				{

					Speed_Relay=0;
					
					offset_position=Real_Position_Value[0];
					
		
				}
				
				CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Speed_Relay);
			}
			
			
		}break;
		case TAG1_TO_TAKE:
		{
			if(SW_L==1)
			{
			track_point(POINTS);

			Velocity_Calculate(&TRAPEZOID_TAG1_TAKE,TAG1_TAKE,POINTS);
			}
		}break;
		
		case TAG1_TO_TAKE_Failed:
		{
			if(SW_L==1)
			{
			track_point(POINTS);

			Velocity_Calculate(&TRAPEZOID_TAG1_TAKE,TAG1_TAKE,POINTS);
			}
		}break;
		case TAKE_TO_TAG2:
		{
			track_point(POINTS);
			Velocity_Calculate_TZ3(&TRAPEZOID_TAKE_TAG2,TAKE_TAG2);
			
			if(Robot_POSITION.X>0)
			{

				Speed_Relay=-1500;
				
				if(SW_L==1)
				{

					Speed_Relay=0;
					
					offset_position=Real_Position_Value[0];
					
		
				}
				
				CAN_RoboModule_DRV_Velocity_Mode(0,1,5000,Speed_Relay);
			}
		}break;
		
		case TAG2_TO_TAKE:
		{
		  if(SW_L==1)
			{
			track_point(POINTS);
			Velocity_Calculate(&TRAPEZOID_TAG2_TAKE,TAG2_TAKE,POINTS);

			}
			
		}break;
		

	  default:{};
		
	}

}
	}
}


//               X               Y
//               |               |
//               |               |
//������  Y-------			��������ϵ  ��������X

void  Velocity_Calculate_TZ3 (trapezoid_param *TRAPEZOID,float Distance)
{
	
	float V,X;
  Theta_Hold();
	
	X=(Distance-goal_errors.distance_error);
	
	K1 =TRAPEZOID->trapezoid_maximum/sqrt(TZ3_UP)*sqrt(abs(X));
	K2 =0.75f* TRAPEZOID->trapezoid_maximum/sqrt(TZ3_DOWN)*sqrt(abs(goal_errors.x_error));
	
	
	if(goal_errors.distance_error>TZ3_DOWN)
	{
   	V = K1 + TRAPEZOID->trapezoid_minimum;
	  if(V>TRAPEZOID->trapezoid_maximum)V= TRAPEZOID->trapezoid_maximum;
	}		
	else
	{
		
		V = K2 ; //����

	}
	
		if( abs(goal_errors.x_error) < pos_stop_threshold)
	{
				V=0;
				Vz=0;
				TRACKING_STATE =TRACKING_ARRIVED;
//			printf("Arrived\r\n");
	}		

		Point_RM_Output();	
	
	 Vx=V*(goal_errors.x_error/goal_errors.distance_error);; //���̿����ٶ�
}		
			
void  Velocity_Calculate_STZ (trapezoid_param *TRAPEZOID,float Distance)
{
	
	float V,X;
  Theta_Hold();
	
	X=(Distance-goal_errors.distance_error);
	
	K1 =TRAPEZOID->trapezoid_maximum/sqrt(STZ_UP)*sqrt(abs(X));
	K2 =0.85f* TRAPEZOID->trapezoid_maximum/sqrt(STZ_DOWN)*sqrt(abs(goal_errors.x_error));
	
	
	if(goal_errors.distance_error>STZ_DOWN)
	{
   	V = K1 + TRAPEZOID->trapezoid_minimum;
	  if(V>TRAPEZOID->trapezoid_maximum)V= TRAPEZOID->trapezoid_maximum;
	}		
	else
	{
		
		V = K2 ; //����

	}
	
		if( abs(goal_errors.x_error) < pos_stop_threshold)
	{
				V=0;
				Vz=0;
				TRACKING_STATE =TRACKING_ARRIVED;
//			printf("Arrived\r\n");
	}		

		Point_RM_Output();	
	
	 Vx=V*(goal_errors.x_error/goal_errors.distance_error);; //���̿����ٶ�
}			


void  Velocity_Calculate (trapezoid_param *TRAPEZOID,float Distance,POINT *Point)
{
	
	float V,X;
  Theta_Hold();
	
	X=(Distance-goal_errors.distance_error);
	
	K1 =TRAPEZOID->trapezoid_maximum/sqrt(Speed_UP)*sqrt(abs(X));
	K2 =0.8f* TRAPEZOID->trapezoid_maximum/sqrt(Speed_DOWN)*sqrt(abs(goal_errors.x_error));
	
	
	if(goal_errors.distance_error>Speed_DOWN)
	{
   	V = K1 + TRAPEZOID->trapezoid_minimum;
	  if(V>TRAPEZOID->trapezoid_maximum)V= TRAPEZOID->trapezoid_maximum;
	}		
	else
	{
		
		V = K2 ; //����

	}
	
		if( abs(goal_errors.x_error) < pos_stop_threshold)
	{
				V=0;
				Vz=0;
				TRACKING_STATE =TRACKING_ARRIVED;
//			printf("Arrived\r\n");
	}		

		Point_RM_Output();	
	
	 Vx=V*(goal_errors.x_error/goal_errors.distance_error);; //���̿����ٶ�
}




void PID_Velocity_Calculate(POINT *Point)
{
	
	PID_Cal(&PTP,Point->x,Robot_POSITION.X,POSITION_PID);
	Vx=PTP.pos_out;

	
}


			
void Calculate_Distance(POINT *POINTS,float *distance)  //���Զ�����·��
{
	track_point(POINTS);
	*distance=goal_errors.distance_error;
}			


void track_point(POINT *POINTS) //RM�ر߿���Y���ٶ�
{
	Robot_POSITION.X = -ROBOT_POSITION.Y_POS; 

		/**********�������********/
	goal_errors.x_error=POINTS->x-Robot_POSITION.X;//��������˵�ǰλ�õ���� RROBOT_POSITION.XΪ�����˱�����X���
	goal_errors.y_error=0; //Y��������
	goal_errors.distance_error=sqrt(goal_errors.x_error*goal_errors.x_error + goal_errors.y_error*goal_errors.y_error);//��Ŀ���ľ���
	goal_errors.xy_error = abs(goal_errors.x_error) + abs(goal_errors.y_error); //�����پ���

}







void tracking_init(void) //���������ľ���
{
		/********************�����Ŀ���֮��ľ���****************************/
	PID_Init(&PTP,10.0,0.5,0.2,4000,2000); //p i d�������޷� �����޷�
	Robot_POSITION.X=0;
	Robot_POSITION.Y=0;
	START_TAKE=2720.0; //��ʼ�㵽�����ľ���
//	TAKE_TAG1=8115.0; //����㵽TZ1ֹͣ��ľ���
//	TAG1_TAKE=8115.0;
//	TAKE_TAG2=10100.0;//����㵽TZ2ֹͣ��ľ���
//	TAG2_TAKE=10100.0;
}
