#ifndef __PS2_TASK_H
#define __PS2_TASK_H

extern uint8_t PS2_Key;

typedef enum
{
	AUTO_MODE = 0,
	HAND_MODE = 1 ,
	
}REMOTE_STATE;


extern int16_t Hand_speed;
extern uint8_t Semi_Count;
extern uint8_t Mode_Count;
extern uint8_t Mode_Change;
extern uint8_t Back_Count;
extern uint8_t Distance_Count;

void Semi_Auto(void);//手动模式下的半自动
void Point_PS2_Output(void);
void PS2_TASK(void);
void PS2_KEY_SCAN(void);
void PS2_Auto_Offset (void);
void PS2_Remote_Output(void);
#endif
