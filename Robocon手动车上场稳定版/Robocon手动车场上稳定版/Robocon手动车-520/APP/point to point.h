#ifndef __POINT_TO_POINT_H
#define __POINT_TO_POINT_H

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
		
}trapezoid_param;//ÌÝÐÎ²ÎÊý

extern float START_TAKE,TAKE_TAG1,TAG1_TAKE,TAKE_TAG2,TAG2_TAKE;
extern GOAL_ERRORS goal_errors;


void Calculate_Distance_TZ1(void);
void Calculate_Distance_TZ2(void); 
void TRACKING_TASK(POINT *POINTS);
void tracking_init(void);
void track_point(POINT *POINTS);
void  Velocity_Calculate (trapezoid_param *TRAPEZOID,float Distance);
#endif
