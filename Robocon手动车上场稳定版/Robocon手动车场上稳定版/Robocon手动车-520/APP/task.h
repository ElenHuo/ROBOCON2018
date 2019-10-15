#ifndef __TASK_H
#define __TASK_H
#include "sys.h"


extern uint8_t Bsp_Int_Ok; 
extern uint8_t Count_1ms,Count_2ms,Count_4ms,Count_5ms,Count_20ms,Count_50ms,Count_100ms;
extern int Count_500ms;




#define		usart1_XCOM    1
#define		usart1_ANO     0
#define  FIRE 0 


void STATE_MACHINE_TASK(void);
void Nvic_Init(void); 
void BSP_Init(void);
void Task_1000HZ(void);
void Task_500HZ(void);
void Task_250HZ(void);
void Task_200HZ(void);
void Task_50HZ(void);
void Task_20HZ(void);
void Task_10HZ(void);
void Task_2HZ(void);


typedef enum
{
	PREPARE_STATE, //0
	STZ_TO_TAKE,   //1
	TAKE_TO_TAG1,  //2
	TAG1_TO_TAKE,  //3
	TAKE_TO_TAG2,  //4
	TAG2_TO_TAKE,  //5
	
	ALIGN_STATE1, //6
	ALIGN_STATE2,  //7
	
	TAKE_BALL_STATE1,//8
	TAKE_BALL_STATE2,//9
	
	RELAY_STATE1, //¶Ô½Ó×´Ì¬  10
	RELAY_STATE2,//11
	RELAY_STATE3,
	
	TAG1_TO_TAKE_Failed,
	
	Remote_State,//13
}ROBOT_WORKING_STATE;


typedef enum
{
  TRACKING_ARRIVED,
	TRACKING_GOING,
	TRACKING_UNKNOWN,
	
}Tracking_STATE;  //TRACKING_STATE


typedef enum
{
	TAKING_DONE,//0
	TAKING_GOING,//1
	TAKING_UNKOWN,//2
	
}TakeBall_STATE;


typedef enum
{
	ALIGN_DONE,
	ALIGN_GOING,
	ALIGN_UNKNOWN,
}Align_STATE;


typedef enum
{
  RELAY_SUCCEEDED,
	RELAY_FAILED,
	RELAY_UNKNOWN,
	RELAY_GOING,
}Relay_STATE;  //RELAY_STATE


#endif
