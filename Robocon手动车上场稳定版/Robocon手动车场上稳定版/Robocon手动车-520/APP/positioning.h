#ifndef _POSITIONING_H
#define _POSITIONING_H
#include "sys.h"


//统一单位m
#define		CAR_R 					0.0815f						//8.15cm
#define		WHEEL_D					0.05						//50mm
#define		Encoder_lines		1000						//1000线，编码器线圈数量，转动一圈触发的脉冲数量


#define 	CAR_R_reciprocal  12.26993865f      // 1/CAR_R
#define 	period          		0.02f          //任务周期
#define 	TIM_MAX_COUNTER 			30000    	  	  //编码器向上向下计数的最大计数值（计数值只有正没有负，负数是从最大值向下计算）
																							//给定一个很大的值，使得编码器在短暂时间T内不会超过的，而由于我们此时计数方式为向上向下计数，
																							//所以，这样可以用于判断反转，如果反转的话，计数器便会从这个最大数向下递减计数，所以，此时通过比较中位数就可以判断是正转还是反转
#define 	Half_TIM_MAX_COUNTER  15000     		//编码器向上向下计数的最大计数值的一半（中位数）
#define		mir          		   0.00003926f	    //单位长mir=C/Encoder_lines/pinshu=（pi*d/1000）/4,编码器的每一次脉冲下，轮子的转动距离，注意，由于上下计数算法，因此计算脉冲次数的时候是四分频，所以轮子转一圈，实际测得的脉冲数目为线数*分频数=1000*4


#define 	pi              	3.1415926f 
#define   pi_division_two		0.1570796f
#define 	sqrt3           	1.7320508f       //根号3


struct _car
{
	float a;
	float b;
	float c;
};
extern struct _car V;
extern struct _car S;
extern struct _car test_S;
extern struct _car Pending_S;	//实际距离
extern struct _car kalman_S;
extern struct _car kalman_V;

struct _state
{
	struct _car Ecder_Pos;
	struct _car Ecder_Vel;
	float x;
	float y;
	float theta_c;
	float theta_i;
};
extern struct _state now;
extern struct _state last;
extern struct _state test;
extern struct _state kalman_now;
extern struct _state kalman_last;

void Odometer_Caculation(void);
void Get_Encoder_by_Velocity(void);
void Get_Encoder_by_Position(void);
void Encoder_Caculation(void);

#endif

