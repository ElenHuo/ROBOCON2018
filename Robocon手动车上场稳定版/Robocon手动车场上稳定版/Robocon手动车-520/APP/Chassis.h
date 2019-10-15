#ifndef __CHASSIS_H
#define __CHASSIS_H
#include "sys.h"

#define X_PARAM          (0.5f)               
#define Y_PARAM         (0.866f) 
#define R_PARAM     		 (1.0f)
#define PI							(3.14159f)

extern float Vx;
extern float Vy;
extern float Vz;
extern float theta;
extern float offset_angle;

enum{
  A=0,
	B=1,
	C=2
};


typedef struct Motor
{
	float Chassis_Control[3];
}Motor;

void Kinematic_Motor_Control(float Vx, float Vy, float Vz);
void World_Kinematic_Motor_Control(float Vx, float Vy ,float Vz, float theta);
void Chassis_control(float Vx,float Vy,float Vz,float theta);
void Fire_Remote_Output(void);

void Label_Tag(float Tag_Vx,float Tag_Vz,float Tag_Yaw);
void locked_rotor_current_check(void);
void Theta_Hold(void); 
void ALIGN_TASK(void);


#endif

