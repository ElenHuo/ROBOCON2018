#ifndef _POSITIONING_H
#define _POSITIONING_H
#include "sys.h"


//ͳһ��λm
#define		CAR_R 					0.0815f						//8.15cm
#define		WHEEL_D					0.05						//50mm
#define		Encoder_lines		1000						//1000�ߣ���������Ȧ������ת��һȦ��������������


#define 	CAR_R_reciprocal  12.26993865f      // 1/CAR_R
#define 	period          		0.02f          //��������
#define 	TIM_MAX_COUNTER 			30000    	  	  //�������������¼�����������ֵ������ֵֻ����û�и��������Ǵ����ֵ���¼��㣩
																							//����һ���ܴ��ֵ��ʹ�ñ������ڶ���ʱ��T�ڲ��ᳬ���ģ����������Ǵ�ʱ������ʽΪ�������¼�����
																							//���ԣ��������������жϷ�ת�������ת�Ļ������������������������µݼ����������ԣ���ʱͨ���Ƚ���λ���Ϳ����ж�����ת���Ƿ�ת
#define 	Half_TIM_MAX_COUNTER  15000     		//�������������¼�����������ֵ��һ�루��λ����
#define		mir          		   0.00003926f	    //��λ��mir=C/Encoder_lines/pinshu=��pi*d/1000��/4,��������ÿһ�������£����ӵ�ת�����룬ע�⣬�������¼����㷨����˼������������ʱ�����ķ�Ƶ����������תһȦ��ʵ�ʲ�õ�������ĿΪ����*��Ƶ��=1000*4


#define 	pi              	3.1415926f 
#define   pi_division_two		0.1570796f
#define 	sqrt3           	1.7320508f       //����3


struct _car
{
	float a;
	float b;
	float c;
};
extern struct _car V;
extern struct _car S;
extern struct _car test_S;
extern struct _car Pending_S;	//ʵ�ʾ���
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

