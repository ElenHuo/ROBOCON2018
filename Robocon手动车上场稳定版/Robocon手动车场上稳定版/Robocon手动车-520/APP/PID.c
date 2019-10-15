#include "PID.h"	//解算角度与PID调试

PID PID_POS;


//读取大概转5圈后立马减速达到抛射
void PID_Throw(Encoder *p,uint8_t flag)//投射要重新置can_count=0
{
	if(flag==1)
	{
		if(p->round<5)//加速阶段
		{
			PID_Init(&PID_POS,0.02,0,0,2000,2000); // p i d 最大限幅
			//target :2000
			PID_Cal(&PID_POS,2000,CM1Encoder.rpm,POSITION_PID);
			//Set_CM_Speed(PID_POS.pos_out,0,0,0);
		}
		if(p->round==5)
		{
			slowdown();
		}
		if(CM1Encoder.rpm==0)
		{
			//Set_CM_Speed(0,0,0,0);
			delay_ms(100);
			p->round=0;
			flag=0;
			can_count=0;
		}
	}
}


//电机减速
void slowdown()
{
	PID_Init(&PID_POS,0.02,0,0,2000,2000); // p i d 最大限幅
	PID_Cal(&PID_POS,0,CM1Encoder.rpm,POSITION_PID);
//	Set_CM_Speed(PID_POS.pos_out,0,0,0);
}


void PID_Cal(PID *p ,float Target, float Current,short mode)
{ 
	p->err[NOW]=Target-Current;
	
	p->err[SUM]+=p->err[NOW];
	
	p->err[DIFF]=p->err[NOW]-p->err[LAST];
	
	
  if(mode == POSITION_PID)
	{ 
		p->pout= p->Kp * p->err[NOW];
		p->iout= p->Ki * p->err[SUM]; 
		p->dout= p->Kd * p->err[DIFF];
		abs_limit(&(p->iout),p->IntegralLmit);
		p->pos_out=p->pout + p->iout + p->dout;
		abs_limit(&(p->pos_out),p->outputmax);
		p->err[LAST]=p->err[NOW];
	}

  if(mode == DELTA_PID)
	{
		p->pout= p->Kp * p->err[DIFF];
		p->iout= p->Ki * p->err[NOW]; 
		p->dout= p->Kd * (p->err[NOW] - 2*p->err[LAST] + p->err[LLAST]);
		
		abs_limit(&(p->iout),p->IntegralLmit);
		p->delta_u=p->pout + p->iout + p->dout;
		p->delta_out=p->last_delta_out + p->delta_u;
		abs_limit(&(p->delta_out),p->outputmax);
		p->last_delta_out=p->delta_out;
	}
	
  p->err[LLAST]= p->err[LAST];
	p->err[LAST]= p->err[NOW];
}


void PID_Init(PID *p, float Kp, float Ki, float Kd ,float outputmax, float intergral_limit)
{
	p->Kp=Kp , p->Kd=Kd , p->Ki=Ki;
	p->outputmax=outputmax;
	p->IntegralLmit=intergral_limit;
	
	p->err[NOW] = p->err[SUM] =	p->err[DIFF] = p->err[LAST] = p->err[LLAST] = 0;
}


void abs_limit( float *a,float ABS_MAX) 
{
	if(*a>ABS_MAX)	*a= ABS_MAX;
	if(*a<-ABS_MAX)	*a=-ABS_MAX;
}

