#ifndef __PID_H
#define __PID_H

#include "can1.h"
#include "can2.h"
#include "delay.h"

#define POSITION_PID 0
#define DELTA_PID 1
enum {
	LLAST=0,
	LAST=1,
	NOW=2,
	DIFF=3,  //此次误差与上一次误差
	SUM=4
	
};
typedef struct PID{
	float Kp;
	float Kd;
	float Ki;
	float err[5];
	float pos_out;
	float delta_u;
	float delta_out;
	float last_delta_out;
	float outputmax;//输出限幅
	float last_output;
	float pout;
	float iout;
	float dout;
	float	IntegralLmit;
	
	
}PID;

extern PID PID_POS;
void abs_limit( float *a,float ABS_MAX);

void PID_Cal(PID *p ,float Target, float Current,short mode);
void PID_Init(PID *p, float Kp, float Ki, float Kd ,float outputmax ,float intergral_limit);
void slowdown(void);
void PID_Throw(Encoder *p,uint8_t flag);


#endif
