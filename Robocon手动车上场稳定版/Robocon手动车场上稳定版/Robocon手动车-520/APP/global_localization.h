#ifndef __GLOBAL_LOCALIZATON_H
#define __GLOBAL_LOCALIZATON_H

typedef struct ROBOT_POS{
  float  X_POS;
  float  Y_POS;     
  float  ANGLE_POS;
	float  LAST_X_POS;
	float  LAST_Y_POS;     
  float  LAST_ANGLE_POS;
  float  X_POS_OFFSET;
  float  Y_POS_OFFSET;     
  float  ANGLE_POS_OFFSET;
	
}ROBOT_POS;

typedef struct Enco
{
	int ENCONDER_SPEED_A;
	int ENCONDER_SPEED_B;
	long int ENCONDER_POS_A;
	long int ENCONDER_POS_B;
	float REAL_SPEED_A;
	float REAL_SPEED_B;
	float REAL_DELTA_POS_A;
	float REAL_DELTA_POS_B;
	float REAL_POS_A;
	float REAL_POS_B;
}Enco;

typedef struct Atti
{
	float GYRO;
	float YAW;
	float RAW_YAW;
	float YAW_OFFSET;
}Atti;

typedef struct ENCO_POS
{
	float X;
	float Y;
	float Z;
}ENCO_POS;

extern ROBOT_POS ROBOT_POSITION;
extern ENCO_POS ROBOT_ENCO_POS;
void Calculat_Odometry(void);
void Get_Robot_Possiton(void);
void LOCALIZATION_INIT(void);
void Orthogonal_Calculat_Odometry(void);
void pos_update(void);

#endif

