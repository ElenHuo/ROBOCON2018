#ifndef __POINT_TO_POINT_H
#define __POINT_TO_POINT_H

#define STZ_UP 1500.0f   //1500
#define STZ_DOWN  1200.0f

#define Speed_UP 1500.0f
#define Speed_DOWN	2200.0f

#define TZ3_UP   1300.0f
#define TZ3_DOWN 2500.0f
extern float K1,K2;
typedef struct POINT{
    float x;
    float y;
    float z;
		//char stop;
}POINT;




typedef struct GOAL_ERRORS{
    float x_error;
    float y_error;
    float xy_error;
	  float distance_error;
		float z_error;
	  float distance_between_2pts;
	  float ran_distance;
	  float running_speed;
}GOAL_ERRORS;

typedef struct trapezoid_param{
	
	float trapezoid_maximum;
	float trapezoid_minimum;
	float accel_coefficient;
		
}trapezoid_param;//梯形参数

extern float START_TAKE,TAKE_TAG1,TAG1_TAKE,TAKE_TAG2,TAG2_TAKE;
extern GOAL_ERRORS goal_errors;


void  Velocity_Calculate_TZ3 (trapezoid_param *TRAPEZOID,float Distance);
void  Velocity_Calculate_STZ (trapezoid_param *TRAPEZOID,float Distance);
void Calculate_Distance(POINT *POINTS,float *distance);   //半自动计算路程
void TRACKING_TASK(POINT *POINTS);
void tracking_init(void);
void track_point(POINT *POINTS);
void  Velocity_Calculate (trapezoid_param *TRAPEZOID,float Distance,POINT *Point);
void PID_Velocity_Calculate(POINT *Point);
#endif
