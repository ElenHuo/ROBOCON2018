#include "main.h"

/*****************************/
#define Wheel_Diameter 50.8f //mm
#define Encoder_Resolution 500 //mm
#define Delta_Time 0.005f //mm
#define Distance_per_line (PI*Wheel_Diameter/(Encoder_Resolution*4)) //mm
#define SIN45 0.70710678f //sin(pi/4) cos(pi/4)




#if DEBUG_ENCODER
int t3,t4,t8;
#endif

struct{
	float X_PROPORTION;
	float Y_PROPORTION;
	float ANGLE_OFFSET;
}COORDINATE_OFFSET = { 0.0, 0.0, 0.0};


Atti Attitude;
Enco Orthogonal_encoder;
ENCO_POS ROBOT_ENCO_POS;

/********************************/
ROBOT_POS ROBOT_POSITION = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
ROBOT_POS LIDAR_POSITION = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
//float kalman_x,kalman_y,last_pos_x,delta_x;


void pos_update(void)
{
	Get_Robot_Possiton();
	ROBOT_POSITION.LAST_X_POS = ROBOT_POSITION.X_POS;
	ROBOT_POSITION.LAST_Y_POS = ROBOT_POSITION.Y_POS;
	ROBOT_POSITION.LAST_ANGLE_POS = ROBOT_POSITION.ANGLE_POS;
	
	ROBOT_POSITION.X_POS = -ROBOT_ENCO_POS.X;  //实际安装与原设定坐标旋转了180度，加负号
	ROBOT_POSITION.Y_POS = -ROBOT_ENCO_POS.Y;
	ROBOT_POSITION.ANGLE_POS = ROBOT_ENCO_POS.Z;

	
//	#if LIDAR_ONLY
//	ROBOT_POSITION.X_POS = LIDAR_POSITION.X_POS;   //实际安装与原设定坐标旋转了180度，加负号
//	ROBOT_POSITION.Y_POS = LIDAR_POSITION.Y_POS;
//	ROBOT_POSITION.ANGLE_POS = LIDAR_POSITION.ANGLE_POS;  //使用陀螺仪返回角度
//	#endif
	
	ROBOT_POSITION.X_POS += ROBOT_POSITION.X_POS_OFFSET ;
	ROBOT_POSITION.Y_POS += ROBOT_POSITION.Y_POS_OFFSET ;
	ROBOT_POSITION.ANGLE_POS += ROBOT_POSITION.ANGLE_POS_OFFSET ;
}

/***********************************************************************/
/**************************编码器定位数据*******************************/
/***********************************************************************/

extern struct SGyro 	stcGyro;
extern struct SAngle 	stcAngle;

void LOCALIZATION_INIT()
{
	/**********读取六轴初始化角度*************************/
	int count = 0;
	while(count<100)
	{
		count++;
		delay_ms(5);
	}
	Attitude.YAW_OFFSET = (float)stcAngle.Angle[2]/32768*180;
	encoder_Init_TIM3();
	encoder_Init_TIM4();
	encoder_Init_TIM8();
	/***********读取六轴初始化角度************************/
	
	/**********AR启动区为原点，初始化机器人位置*************/
//	ROBOT_POSITION.X_POS_OFFSET = -565.0;
//	ROBOT_POSITION.Y_POS_OFFSET = 4565.0;
	ROBOT_POSITION.X_POS_OFFSET = 0.0;
	ROBOT_POSITION.Y_POS_OFFSET = 0.0;
	ROBOT_POSITION.ANGLE_POS_OFFSET = 0.0;
	/**********AR启动区为原点，初始化机器人位置*************/
}

void Get_Robot_Possiton()
{
	//Get_Enconder();
	#if DEBUG_ENCODER
	t3 += Read_Encoder(3);
	t4 += Read_Encoder(4);
	t8 += Read_Encoder(8);
	printf("t3:%d  t4:%d  t8:%d  \r\n",t3,t4,t8);
	#else
	Orthogonal_encoder.ENCONDER_SPEED_A = Read_Encoder(4);
	Orthogonal_encoder.ENCONDER_SPEED_B = -Read_Encoder(8);
	#endif
	
	Orthogonal_encoder.ENCONDER_POS_A += Orthogonal_encoder.ENCONDER_SPEED_A;
	Orthogonal_encoder.ENCONDER_POS_B += Orthogonal_encoder.ENCONDER_SPEED_B;
	Orthogonal_encoder.REAL_DELTA_POS_A = Orthogonal_encoder.ENCONDER_SPEED_A * Distance_per_line ;
	Orthogonal_encoder.REAL_DELTA_POS_B = Orthogonal_encoder.ENCONDER_SPEED_B * Distance_per_line ;
	
	//Attitude_Update();
	Attitude.RAW_YAW = (float)stcAngle.Angle[2]/32768*180;
	
	Attitude.YAW = Attitude.RAW_YAW - Attitude.YAW_OFFSET;
	
	Calculat_Odometry();
	//Orthogonal_Calculat_Odometry();
	
//	printf("%d \r\n",Encoder.ENCONDER_SPEED_A);
//	printf("%d \r\n",Encoder.ENCONDER_SPEED_B);
}



void Calculat_Odometry()
{
	ROBOT_ENCO_POS.Z  = Attitude.YAW; //convert to radian
	ROBOT_ENCO_POS.X += SIN45*cos(ROBOT_ENCO_POS.Z/180.0f*PI)*(Orthogonal_encoder.REAL_DELTA_POS_B - Orthogonal_encoder.REAL_DELTA_POS_A) -
											SIN45*sin(ROBOT_ENCO_POS.Z/180.0f*PI)*(Orthogonal_encoder.REAL_DELTA_POS_B + Orthogonal_encoder.REAL_DELTA_POS_A);
	ROBOT_ENCO_POS.Y += SIN45*sin(ROBOT_ENCO_POS.Z/180.0f*PI)*(Orthogonal_encoder.REAL_DELTA_POS_B - Orthogonal_encoder.REAL_DELTA_POS_A) +
											SIN45*cos(ROBOT_ENCO_POS.Z/180.0f*PI)*(Orthogonal_encoder.REAL_DELTA_POS_B + Orthogonal_encoder.REAL_DELTA_POS_A);
	
	
//	kalman_x += SIN45*cos(ROBOT_ENCO_POS.Z/180.0f*PI)*(Encoder.REAL_DELTA_POS_B - Encoder.REAL_DELTA_POS_A) -
//											SIN45*sin(ROBOT_ENCO_POS.Z/180.0f*PI)*(Encoder.REAL_DELTA_POS_B + Encoder.REAL_DELTA_POS_A);
//	kalman_y += SIN45*sin(ROBOT_ENCO_POS.Z/180.0f*PI)*(Encoder.REAL_DELTA_POS_B - Encoder.REAL_DELTA_POS_A) +
//											SIN45*cos(ROBOT_ENCO_POS.Z/180.0f*PI)*(Encoder.REAL_DELTA_POS_B + Encoder.REAL_DELTA_POS_A);
	
}

void Orthogonal_Calculat_Odometry()
{
	ROBOT_ENCO_POS.Z  = Attitude.YAW; //convert to radian
	ROBOT_ENCO_POS.X += Orthogonal_encoder.REAL_DELTA_POS_B*cos(ROBOT_ENCO_POS.Z/180.0f*PI) - Orthogonal_encoder.REAL_DELTA_POS_A*sin(ROBOT_ENCO_POS.Z/180.0f*PI);
	ROBOT_ENCO_POS.Y += Orthogonal_encoder.REAL_DELTA_POS_B*sin(ROBOT_ENCO_POS.Z/180.0f*PI) + Orthogonal_encoder.REAL_DELTA_POS_A*cos(ROBOT_ENCO_POS.Z/180.0f*PI);
}


/***********************************************************************/
/**************************编码器定位数据*******************************/
/***********************************************************************/
