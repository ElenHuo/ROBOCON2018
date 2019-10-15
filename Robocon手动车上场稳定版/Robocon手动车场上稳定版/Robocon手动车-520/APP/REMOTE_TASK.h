#ifndef __REMOTE_TASK_H
#define __REMOTE_TASK_H


extern uint8_t TZ3_COUNT;
extern uint8_t OFFSET_STOP;
void RM_TASK(void);
void Auto_Relay(void);
void Mode_Judge(void);
void RM_OFFSET(void);
void RM_Auto_Offset (void);
void RM_Output(void);
void Point_RM_Output(void);
#endif

