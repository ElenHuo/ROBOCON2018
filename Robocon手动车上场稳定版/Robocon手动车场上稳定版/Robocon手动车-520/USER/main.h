#ifndef __MAIN_H
#define __MAIN_H

#include "Servo.h"
#include "gyro_uart.h"
#include "switch.h"
#include "can1.h"
#include "can2.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "PID.h"
#include "math.h"
#include "Chassis.h"
#include "scope.h"
#include "fs_pid.h" 
#include "timer2.h"
#include "led.h" 
#include "task.h"
#include "iwdg.h"

#include "uart4_FireRC.h"
#include "PS2_TASK.h"

#include "pstwo.h"
#include "pstwo_line.h"
#include "Encoder.h"

#include "Ras_usart.h"	
#include "protocol.h"
#include "positioning.h"
#include "kalman.h"
#include "global_localization.h"
#include "point_to_point.h"
#include "REMOTE_TASK.H"
#include "Remote_Control.h"
#include "exti.h"
#include "WFLY_REMOTE.h"


#define abs(x)   ((x>0)? (x):(-x))

#define deceleration_relay 38000
#define deceleration_offset 25000

extern REMOTE_STATE REMOTE;

extern ROBOT_WORKING_STATE LAST_STATE; 
extern ROBOT_WORKING_STATE NOW_STATE;
extern Tracking_STATE TRACKING_STATE;
extern TakeBall_STATE TAKEBALL_STATE;
extern Align_STATE  ALIGN_STATE;
extern Relay_STATE RELAY_STATE;
	


extern POINT STARTZONE_TO_TAKE_BALL;
extern POINT TAKEBALL_TO_Tag1;
extern POINT Tag1_TO_TAKEBALL ;
extern POINT TAKEBALL_TO_Tag2;
extern POINT Tag2_TO_TAKEBALL;
#endif 
