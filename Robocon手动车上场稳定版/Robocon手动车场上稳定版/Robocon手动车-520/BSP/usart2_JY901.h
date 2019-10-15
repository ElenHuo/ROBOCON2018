#ifndef __USART2_JY901_H
#define __USART2_JY901_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
	
//	
//#define SAVE 			0x00
//#define CALSW 		0x01
//#define RSW 			0x02
//#define RRATE			0x03
//#define BAUD 			0x04
//#define AXOFFSET	0x05
//#define AYOFFSET	0x06
//#define AZOFFSET	0x07
//#define GXOFFSET	0x08
//#define GYOFFSET	0x09
//#define GZOFFSET	0x0a
//#define HXOFFSET	0x0b
//#define HYOFFSET	0x0c
//#define HZOFFSET	0x0d
//#define D0MODE		0x0e
//#define D1MODE		0x0f
//#define D2MODE		0x10
//#define D3MODE		0x11
//#define D0PWMH		0x12
//#define D1PWMH		0x13
//#define D2PWMH		0x14
//#define D3PWMH		0x15
//#define D0PWMT		0x16
//#define D1PWMT		0x17
//#define D2PWMT		0x18
//#define D3PWMT		0x19
//#define IICADDR		0x1a
//#define LEDOFF 		0x1b
//#define GPSBAUD		0x1c

//#define YYMM				0x30
//#define DDHH				0x31
//#define MMSS				0x32
//#define MS					0x33
//#define AX					0x34
//#define AY					0x35
//#define AZ					0x36
//#define GX					0x37
//#define GY					0x38
//#define GZ					0x39
//#define HX					0x3a
//#define HY					0x3b
//#define HZ					0x3c			
//#define Roll				0x3d
//#define Pitch				0x3e
//#define Yaw					0x3f
//#define TEMP				0x40
//#define D0Status		0x41
//#define D1Status		0x42
//#define D2Status		0x43
//#define D3Status		0x44
//#define PressureL		0x45
//#define PressureH		0x46
//#define HeightL			0x47
//#define HeightH			0x48
//#define LonL				0x49
//#define LonH				0x4a
//#define LatL				0x4b
//#define LatH				0x4c
//#define GPSHeight   0x4d
//#define GPSYAW      0x4e
//#define GPSVL				0x4f
//#define GPSVH				0x50
//#define Q0          0x51
//#define Q1          0x52
//#define Q2          0x53
//#define Q3          0x54
//      
//#define DIO_MODE_AIN 0
//#define DIO_MODE_DIN 1
//#define DIO_MODE_DOH 2
//#define DIO_MODE_DOL 3
//#define DIO_MODE_DOPWM 4
//#define DIO_MODE_GPS 5		

//struct SAcc
//{
//	short a[3];
//	short T;
//};
//extern struct SAcc stcAcc;
//extern struct SAcc sensor_Acc;

//struct SGyro
//{
//	short w[3];
//	short T;
//};
//extern struct SGyro stcGyro;
//extern struct SGyro sensor_Gyro;

//struct SAngle
//{
//	short Angle[3];
//	short T;
//};
//extern struct SAngle stcAngle;
//extern struct SAngle stcAngle_offset;


//struct FAngle
//{
//	float Angle[3];
//	float Yaw_Radian;
//	short T;
//};
//extern struct FAngle quaternion_Angle;
//extern struct FAngle sensor_Angle;

//struct SMag
//{
//	short h[3];
//	short T;
//};
//extern struct SMag stcMag;

//struct SQ
//{ short q[4];
//};
//extern struct SQ  stcQ;
//extern struct SQ  sensor_Q;
// 
//extern uint8_t offset_flag;
//extern float Angle_offset;

#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收

//void Serial_Data_Offset(void);
//void Serial_Data_Calculation(void);
//void uart2_JY901_init(u32 bound);
//void Serial_Quaternion(void);
//void Serial_IMUupdate(void);
//float invSqrt(float x);

#endif

