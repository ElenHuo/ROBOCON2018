#include "main.h"


float Vx,Vy,Vz,theta;
float offset_angle=0;
Motor Motor_Control;


float Speed[3];
float Tag_Threshold;
PID Theta;


uint8_t mode=1;//
/* 电机PID */
 pid_control_type motor_pid=
{
	.error_big_pid    = {.p=10.0f, .i=1, .d=0},
	.error_medium_pid = {.p= 10.0f, .i=1, .d=0},
	.error_small_pid	=	{.p= 10.0f, .i=0.5, .d=0},
	.control_cycle		=  1,
	.error_threshold_big   = 500, /* 大误差阈值 */
	.error_threshold_small = 100, /* 小误差阈值 */
	.error_dead_space 	   = 0, /* 死区误差 */
	.output_limit_abs			 = 10000
};


/* 对位PID */
 pid_control_type tag_pid=
{
	.error_big_pid    = {.p=1.0f, .i=0, .d=0},
	.error_medium_pid = {.p= 0.8f, .i=0, .d=0},
	.error_small_pid	=	{.p= 0.6f, .i=0, .d=0},
	.control_cycle		=  1,
	.error_threshold_big   = 520, /* 大误差阈值 */
	.error_threshold_small = 240, /* 小误差阈值 */
	.error_dead_space 	   = 0, /* 死区误差 */
	.output_limit_abs			 = 500 /* 不限制输出 */
};

/*************************************************************************
									对位任务

*************************************************************************/
void ALIGN_TASK(void)
{ 
	if(REMOTE==AUTO_MODE)
	{
		if(ALIGN_STATE==ALIGN_GOING)
		{
			switch(NOW_STATE)
			{
				case ALIGN_STATE1:
				{
//					PS2_Auto_Offset();
					RM_Auto_Offset();
				}break;
				case ALIGN_STATE2:
				{
//					PS2_Auto_Offset();
					
					RM_Auto_Offset();
				}
				default:{};
				
			}		
		}
	}
	
	
	
}

//需要注意，摄像头为世界坐标系120，X轴与标志同向，Y轴与标志反向
void Label_Tag(float Tag_Vx,float Tag_Vz,float Tag_Yaw) //theta默认为120°
{
	float Vx_Tag,Vz_Tag;
	float Vz_Contrast;
	float Std_X,Std_Deepth;
	
	Std_X=2.5;
	
	Std_Deepth=350;
	
	Tag_Threshold= 5;
	
//	printf("Tag:%5f %5f %5f \r\n",Tag_Vx,Tag_Vz,Tag_Yaw);
	if(Tag_Vz>560)
	{
	PID_Init(&PID_POS,4.0,0,0,1000,0); //最大输出1000
  PID_Cal(&PID_POS,560,Tag_Vz,0);
	Vz_Tag=PID_POS.pos_out;
	}
	if(410<Tag_Vz && Tag_Vz<560)
	{
	PID_Init(&PID_POS,2.0,0,0,1000,0); 
	PID_Cal(&PID_POS,410,Tag_Vz,0);
	Vz_Tag=PID_POS.pos_out;
	}
	if(350<Tag_Vz && Tag_Vz<410)
	{
	PID_Init(&PID_POS,2.0,0,0,1000,0); 
	PID_Cal(&PID_POS,350,Tag_Vz,0);
	Vz_Tag=PID_POS.pos_out;
	}
	if(Tag_Vz<350)
	{
	PID_Init(&PID_POS,2.0,0,0,1000,0); 
	PID_Cal(&PID_POS,Std_Deepth,Tag_Vz,0);
	Vz_Tag=PID_POS.pos_out;
	}
//	}
//	Error_Vz=Tag_Vz-303;
//	Vz_Tag=pid_control(&tag_pid,Error_Vz);
	
	
	PID_Init(&PID_POS,4,0,0,600,0); 
	PID_Cal(&PID_POS,Std_X,Tag_Vx,0);
	Vx_Tag=PID_POS.pos_out;
	
	Vx=-Vx_Tag;//需要观察Vx，如果在标志右边，输出值为正,则输出Vx为正数，但机器人必须为反向移动
	          //反之，相反
	
	Vy=Vz_Tag;//深度值越变越小，
//	Theta_Hold();//给车体自转速度，保证航向角不变
	theta=120;
	Vz_Contrast=Tag_Vz-Std_Deepth;
	Vz_Contrast=abs(Vz_Contrast);
	
	if(Vz_Contrast<=Tag_Threshold)
	{
		ALIGN_STATE=ALIGN_DONE;
	}
//	printf("Speed:%5f %5f %5f \r\n",Vx,Vy,Vz);
	
	
	
}


	/***************稳定航向角90°***************/
void Theta_Hold(void) 
{	

	  PID_Init(&Theta,0.5,0,0.05,5,0); 

		PID_Cal(&Theta,offset_angle,ROBOT_POSITION.ANGLE_POS,0);
		Vz=Theta.pos_out*105;//底盘逆时针为正向-
		theta=90+ROBOT_POSITION.ANGLE_POS-offset_angle;//-offset补偿角度
	// printf("theta: %5f \r\n",theta);
 
}




//void Fire_Remote_Output(void)
//{	
//		VX=LX-1500;
//		VY=LY-1500;
//		VZ=RX-1500;

//		Remote_Vx = (float)(VX*6);
//		Remote_Vy = (float)(VY*6);
//		Remote_Vz = (float)(VZ*2);
//		Kinematic_Motor_Control(Remote_Vx,Remote_Vy,Remote_Vz);
//	//World_Kinematic_Motor_Control(Remote_Vx,Remote_Vy,Remote_Vz,90);
//}


void Chassis_control(float Vx,float Vy,float Vz,float theta)
{	

	
	World_Kinematic_Motor_Control(Vx,Vy,Vz,theta);

		/**************电调默认方向与运动学设定正方向相反****************/
	Motor_Control.Chassis_Control[A]=-Motor_Control.Chassis_Control[A];
	Motor_Control.Chassis_Control[B]=-Motor_Control.Chassis_Control[B];
	Motor_Control.Chassis_Control[C]=-Motor_Control.Chassis_Control[C];
	
	float Error[3];
	Error[A]=Motor_Control.Chassis_Control[A] -  CM1Encoder.rpm;
	Error[B]=Motor_Control.Chassis_Control[B] -  CM2Encoder.rpm;
	Error[C]=Motor_Control.Chassis_Control[C] -  CM3Encoder.rpm;
	
	Speed[A]=pid_control(&motor_pid,Error[A]);
	Speed[B]=pid_control(&motor_pid,Error[B]);
	Speed[C]=pid_control(&motor_pid,Error[C]);
	
	
	Set_Motor_Speed(CAN2,Speed[A],Speed[B],Speed[C],0);
//	locked_rotor_current_check();

	//printf("SHOW: %f %f %f \r\n",Motor_Control.Chassis_Control[A],Motor_Control.Chassis_Control[B],Motor_Control.Chassis_Control[C]);
	
}


///********************************************************************************
//																世界坐标系正运动学
//*********************************************************************************/
//void World_Forward_Kinematic_Analysis(float theta)  //theta 机器人坐标系x轴与世界坐标系x轴夹角
//{
//	PVx = wheel_speed[0]*2*cos(theta)/3.0f - wheel_speed[1]*(cos(theta)+sqrt(3.0f)*sin(theta))/3.0f - wheel_speed[2]*(cos(theta)-sqrt(30)*sin(theta))/3.0f ;
//	PVy = wheel_speed[0]*2*sin(theta)/3.0f - wheel_speed[1]*(sin(theta)-sqrt(3.0f)*cos(theta))/3.0f - wheel_speed[2]*(sin(theta)+sqrt(30)*cos(theta))/3.0f ;
//	PVz = wheel_speed[0]/(3.0f*Radius)     + wheel_speed[1]/(3.0f*Radius)                           + wheel_speed[2]/(3.0f*Radius);
//}


/********************************************************************************
																世界坐标系逆运动学
*********************************************************************************/
void World_Kinematic_Motor_Control(float Vx, float Vy ,float Vz, float theta)
{
	theta=PI*theta/180.0f;
	Motor_Control.Chassis_Control[A] =          cos(theta)*Vx +         sin(theta)*Vy +  R_PARAM*Vz;
	Motor_Control.Chassis_Control[B] = -cos(PI/3.0f-theta)*Vx + sin(PI/3.0f-theta)*Vy + R_PARAM*Vz;
	Motor_Control.Chassis_Control[C] = -cos(PI/3.0f+theta)*Vx - sin(PI/3.0f+theta)*Vy + R_PARAM*Vz;
}


/********************************************************************************
																机器人坐标系逆运动学
*********************************************************************************/
void Kinematic_Motor_Control(float Vx, float Vy, float Vz)
{
	Motor_Control.Chassis_Control[A] =	Vx                          + R_PARAM * Vz;
	Motor_Control.Chassis_Control[B] = -Vx * X_PARAM + Vy * Y_PARAM + R_PARAM * Vz;
	Motor_Control.Chassis_Control[C] = -Vx * X_PARAM - Vy * Y_PARAM + R_PARAM * Vz;
}

void locked_rotor_current_check()
{
	if(CM1Encoder.current>15000||CM2Encoder.current>15000||CM3Encoder.current>15000)
	{
		Set_Motor_Speed(CAN2, 0 , 0, 0, 0);
		return ;
	}
}





