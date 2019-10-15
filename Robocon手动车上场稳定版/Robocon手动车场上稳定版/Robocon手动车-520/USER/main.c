#include "main.h"
#include "task.h"
#include "delay.h"


int main(void)
{ 



	delay_init(168);  //初始化延时函数
	BSP_Init();
	
		
	while(1) 
	{
		if(Count_1ms>=1)
		{	
			Count_1ms = 0;
			Task_1000HZ();                                  //执行1000赫兹频率的任务
		}
		if(Count_2ms>=2)
		{
			Count_2ms = 0;
			Task_500HZ();                                   //执行 500赫兹频率的任务																	
		}
		if(Count_4ms>=4)
		{
			Count_4ms = 0;
			Task_250HZ();
		}
		if(Count_5ms>=5)
		{
			Count_5ms = 0;
			Task_200HZ();
		}
		if(Count_20ms>=20)
		{
			Count_20ms = 0;
			Task_50HZ();
		}
		if(Count_50ms>=50)
		{
			Count_50ms = 0;
			Task_20HZ();
		}
		if(Count_100ms>=100)
		{
			Count_100ms = 0;
			Task_10HZ();
		}
		if(Count_500ms>=500)
		{
			Count_500ms = 0;
			Task_2HZ();
		}
	}
}
