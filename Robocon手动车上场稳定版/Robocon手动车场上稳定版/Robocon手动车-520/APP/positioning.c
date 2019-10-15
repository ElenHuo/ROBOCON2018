//#include "main.h"

//struct _car S;			   //距离
//struct _car test_S;
//struct _car Pending_S;	//待处理距离
//struct _car V;			  //速度
//struct _car kalman_S;
//struct _car kalman_V;

//struct _state now;
//struct _state last;
//struct _state test;
//struct _state kalman_now;
//struct _state kalman_last;

//float theta_c_degree;
//float theta_i_degree;

//extern float X[2][1];


///**************************************************************************
//函数功能：计算定位模块的实时位姿
//入口参数：三个从动轮的瞬时速度，        //数据采集频率（可以直接使用编码器的刷新时间，也可以使用其整数倍时间）
//返回  值：实时位姿，（以全局变量的形式更新位姿）
//**************************************************************************/
//void Encoder_Caculation(void)
//{
//	float SIN,COS;
//	SIN = sin(last.theta_i);
//	COS = cos(last.theta_i);
//	
//	//实际小车摆放位置的（x，y）递推公式--递推方式为重推正运动学公式，从一开始换用新位置的矩阵，逆时针命名为ABC
// 	now.x = last.x + (COS*(2*V.a-V.b-V.c)+SIN*sqrt3*(V.c-V.b))*period/3;	//[(1/3)cos*(2a-b-c)+(根号3/3）sin*（c-b)]/TIME-->TIME/3=num5,
//  now.y = last.y + (SIN*(2*V.a-V.b-V.c)+COS*sqrt3*(V.b-V.c))*period/3;	
//  //now.theta_c = last.theta_c + (V.a+V.b+V.c)*CAR_R_reciprocal*period/3;		
//	now.theta_i = sensor_Angle.Yaw_Radian;
//	//now.theta_i = 0;

//	last.x = now.x;
//  last.y = now.y;
//  //last.theta_c = now.theta_c;
//	last.theta_i = now.theta_i;

// // theta_c_degree = last.theta_c*180/pi;	
////*	theta_i_degree = last.theta_i*180/pi;	
//	
//	
////	float SIN2,COS2;
////	SIN2 = sin(kalman_last.theta_i);
////	COS2 = cos(kalman_last.theta_i);
////	
//// 	kalman_now.x = kalman_last.x + (COS2*(2*kalman_V.a-kalman_V.b-kalman_V.c)+SIN2*sqrt3*(kalman_V.c-kalman_V.b))*period/3;	
////  kalman_now.y = kalman_last.y + (SIN2*(2*kalman_V.a-kalman_V.b-kalman_V.c)+COS2*sqrt3*(kalman_V.b-kalman_V.c))*period/3;		
////	kalman_now.theta_i = sensor_Angle.Yaw_Radian;
////	
////	kalman_last.x = kalman_now.x;
////  kalman_last.y = kalman_now.y;
////  
////	kalman_last.theta_i = kalman_now.theta_i;
//}


//void Get_Encoder_by_Velocity(void)
//{
//	//读取三个编码器在T时间内转动的时候的脉冲数数，也就是在T时间内，编码器的光电门被触发了多少次，从而得出编码器的附带着的轮子的瞬时速度
//	//装轮子的时候，B和C是反的
//	now.Ecder_Vel.a=Read_Velocity(3);//PA6PA7		 
//	now.Ecder_Vel.b=Read_Velocity(4);//PB6PB7
//	now.Ecder_Vel.c=Read_Velocity(8);//PC6PC7
//	
//#if usart1_XCOM
////	printf("Read_Velocity(3):%d\r\n",Read_Velocity(3));
////	printf("Read_Velocity(4):%d\r\n",Read_Velocity(4));
////	printf("Read_Velocity(8):%d\r\n",Read_Velocity(8));
//#endif
//	
//	//如果在T时间内，编码器采集的脉冲数超过了设置的计数最大值的一半，说明此事编码器是反转，也就是计数是从最大值递减
//	if(now.Ecder_Vel.a>Half_TIM_MAX_COUNTER)  now.Ecder_Vel.a -= TIM_MAX_COUNTER;
//	if(now.Ecder_Vel.b>Half_TIM_MAX_COUNTER)  now.Ecder_Vel.b -= TIM_MAX_COUNTER;
//	if(now.Ecder_Vel.c>Half_TIM_MAX_COUNTER)  now.Ecder_Vel.c -= TIM_MAX_COUNTER;
//	
//	//各个从动轮的瞬时移动距离	
//	S.a = now.Ecder_Vel.a*mir;
//	S.b = now.Ecder_Vel.b*mir;
//	S.c = now.Ecder_Vel.c*mir;
//	
////	kalman(S.a);
////	kalman_S.a = X[0][0];
////	kalman(S.b);
////	kalman_S.b = X[0][0];
////	kalman(S.c);
////	kalman_S.c = X[0][0];
//	
//	//各个从动轮的瞬时速度	
//	V.a = S.a/period;
//	V.b = S.b/period;
//	V.c = S.c/period;
//	
////	kalman_V.a = kalman_S.a/period;
////	kalman_V.b = kalman_S.b/period;
////	kalman_V.c = kalman_S.c/period;
//	
//	Encoder_Caculation();
//}


//void Get_Encoder_by_Position(void)
//{
//	//读取三个编码器转动的时候的脉冲数数，从而得出编码器的行走了的距离，在T时间内走的距离从而得出此段的平均速度
//	now.Ecder_Pos.a = Read_Position(3);
//	now.Ecder_Pos.b = Read_Position(4);
//	now.Ecder_Pos.c = Read_Position(8);
//	
//#if usart1_XCOM
//	printf("Read_Position(3):%d\r\n",Read_Position(3));
////	printf("Read_Position(4):%d\r\n",Read_Position(4));
////	printf("Read_Position(8):%d\r\n",Read_Position(8));
//#endif
//	
//	Pending_S.a = now.Ecder_Pos.a - last.Ecder_Pos.a;
//	Pending_S.b = now.Ecder_Pos.b - last.Ecder_Pos.b;
//	Pending_S.c = now.Ecder_Pos.c - last.Ecder_Pos.c;
//	
//	last.Ecder_Pos.a = now.Ecder_Pos.a;
//	last.Ecder_Pos.b = now.Ecder_Pos.b;
//	last.Ecder_Pos.c = now.Ecder_Pos.c;
//	
//	S.a = Pending_S.a*mir;
//	S.b = Pending_S.b*mir;
//	S.c = Pending_S.c*mir;
//	
//	V.a = S.a / period;
//	V.b = S.b / period;
//	V.c = S.c / period;
//	
//	Encoder_Caculation();
//}



///*-----------------------计算轮子行走的里程----------------
//-----	编码器线数：Encoder_lines
//-----	轮子的直径：WHEEL_D
//-----	关系：
//-----	统一单位：m
//--------------------------------------------------------*/
//void Odometer_Caculation(void)
//{
////***************  ①
//	test.Ecder_Vel.a = Read_Velocity(3);
//	test.Ecder_Vel.b = Read_Velocity(4);
//	test.Ecder_Vel.c = Read_Velocity(8);

//	if(test.Ecder_Vel.a>Half_TIM_MAX_COUNTER)	test.Ecder_Vel.a -=  TIM_MAX_COUNTER;
//	if(test.Ecder_Vel.b>Half_TIM_MAX_COUNTER)	test.Ecder_Vel.b -=  TIM_MAX_COUNTER;
//	if(test.Ecder_Vel.c>Half_TIM_MAX_COUNTER)	test.Ecder_Vel.c -=  TIM_MAX_COUNTER;

//	test_S.a += test.Ecder_Vel.a*mir;
//	test_S.b += test.Ecder_Vel.b*mir;
//	test_S.c += test.Ecder_Vel.c*mir;
//	
////***************  ②
////	test.Ecder_Pos.a = Read_Position(3);
////	test.Ecder_Pos.b = Read_Position(4);
////	test.Ecder_Pos.c = Read_Position(8);
////	
////	test_S.a = test.Ecder_Pos.a*mir;
////	test_S.b = test.Ecder_Pos.b*mir;
////	test_S.c = test.Ecder_Pos.c*mir;
//}
