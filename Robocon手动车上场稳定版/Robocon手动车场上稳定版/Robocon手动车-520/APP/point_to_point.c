#include "main.h"
#include "path.h"

//               X
//               |
//               |
//编码器  Y-------
extern PID TAKEBALL_PID;
float K1,K2;
#define pos_stop_threshold    (20.0f) ///轨迹跟踪目标点曼哈顿距离切换阈值,STOP

//POINT
//STARTZONE_TO_TAKE_BALL  TAKEBALL_TO_Tag1  Tag1_TO_TAKEBALL TAKEBALL_TO_Tag2
GOAL_ERRORS goal_errors;

PID PTP;//点对点PID
float START_TAKE,TAKE_TAG1,TAG1_TAKE,TAKE_TAG2,TAG2_TAKE;
 
struct 
{
	float X;
	float Y;
	
}Robot_POSITION;



//trapezoid_param TRAPEZOID_PARAM;//梯形变速

trapezoid_param TRAPEZOID_STZ_TAKE={8000.0,900.0,0.15}//梯形最大值，最小值，加速度系数
							,TRAPEZOID_TAKE_TAG1={9000.0,700.0,0.1} //700速度稳定
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
		
			track_point(POINTS);//计算误差

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
//编码器  Y-------			世界坐标系  ————X

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
		
		V = K2 ; //减速

	}
	
		if( abs(goal_errors.x_error) < pos_stop_threshold)
	{
				V=0;
				Vz=0;
				TRACKING_STATE =TRACKING_ARRIVED;
//			printf("Arrived\r\n");
	}		

		Point_RM_Output();	
	
	 Vx=V*(goal_errors.x_error/goal_errors.distance_error);; //底盘控制速度
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
		
		V = K2 ; //减速

	}
	
		if( abs(goal_errors.x_error) < pos_stop_threshold)
	{
				V=0;
				Vz=0;
				TRACKING_STATE =TRACKING_ARRIVED;
//			printf("Arrived\r\n");
	}		

		Point_RM_Output();	
	
	 Vx=V*(goal_errors.x_error/goal_errors.distance_error);; //底盘控制速度
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
		
		V = K2 ; //减速

	}
	
		if( abs(goal_errors.x_error) < pos_stop_threshold)
	{
				V=0;
				Vz=0;
				TRACKING_STATE =TRACKING_ARRIVED;
//			printf("Arrived\r\n");
	}		

		Point_RM_Output();	
	
	 Vx=V*(goal_errors.x_error/goal_errors.distance_error);; //底盘控制速度
}




void PID_Velocity_Calculate(POINT *Point)
{
	
	PID_Cal(&PTP,Point->x,Robot_POSITION.X,POSITION_PID);
	Vx=PTP.pos_out;

	
}


			
void Calculate_Distance(POINT *POINTS,float *distance)  //半自动计算路程
{
	track_point(POINTS);
	*distance=goal_errors.distance_error;
}			


void track_point(POINT *POINTS) //RM沿边控制Y轴速度
{
	Robot_POSITION.X = -ROBOT_POSITION.Y_POS; 

		/**********计算误差********/
	goal_errors.x_error=POINTS->x-Robot_POSITION.X;//点与机器人当前位置的误差 RROBOT_POSITION.X为机器人编码器X输出
	goal_errors.y_error=0; //Y轴误差最多
	goal_errors.distance_error=sqrt(goal_errors.x_error*goal_errors.x_error + goal_errors.y_error*goal_errors.y_error);//与目标点的距离
	goal_errors.xy_error = abs(goal_errors.x_error) + abs(goal_errors.y_error); //曼哈顿距离

}







void tracking_init(void) //计算两点间的距离
{
		/********************计算各目标点之间的距离****************************/
	PID_Init(&PTP,10.0,0.5,0.2,4000,2000); //p i d输出最大限幅 积分限幅
	Robot_POSITION.X=0;
	Robot_POSITION.Y=0;
	START_TAKE=2720.0; //起始点到拿球点的距离
//	TAKE_TAG1=8115.0; //拿球点到TZ1停止点的距离
//	TAG1_TAKE=8115.0;
//	TAKE_TAG2=10100.0;//拿球点到TZ2停止点的距离
//	TAG2_TAKE=10100.0;
}
