#ifndef __CAN2_H__
#define __CAN2_H__
#include "stm32f4xx.h"

void CAN2_Configuration(void);

#define RATE_BUF_SIZE 6

#define CAN_BUS2_MOTOR1_FEEDBACK_MSG_ID           0x201
#define CAN_BUS2_MOTOR2_FEEDBACK_MSG_ID           0x202 
#define CAN_BUS2_MOTOR3_FEEDBACK_MSG_ID           0x203
#define CAN_BUS2_MOTOR4_FEEDBACK_MSG_ID           0x204

typedef struct{
	int16_t raw_value;
	int16_t rpm;
	int16_t current;
	int16_t t;//ÎÂ¶È
	int16_t last_raw_value;
	int16_t last_rpm;
	int16_t diff;
	int16_t round;
	float total_raw;
	int16_t	offset_raw_value;
	float degree;
}Encoder;


extern Encoder CM1Encoder;
extern Encoder CM2Encoder;
extern Encoder CM3Encoder;

extern uint32_t can_count;

void Set_Motor_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq);
void getEncoder( Encoder *p,CanRxMsg *msg);
void offsetEncoder( Encoder *p,CanRxMsg *msg);
#endif 
