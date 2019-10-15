#include "usart2_JY901.h"
#include "sys.h"
#include <string.h>
#include "math.h"
#include "positioning.h"

//float Angle_offset;
//uint8_t flag_count=0;
//static unsigned char TxBuffer[256];
//static unsigned char TxCounter=0;
//static unsigned char count=0; 

//struct SAcc 		stcAcc;
//struct SGyro 		stcGyro;
//struct SMag 		stcMag;
//struct SAngle 	stcAngle;
//struct SQ       stcQ;

//struct SAngle 	stcAngle_offset;	
//struct FAngle 	sensor_Angle;
//struct FAngle 	quaternion_Angle;
//struct SAcc 		sensor_Acc;
//struct SGyro 		sensor_Gyro;
//struct SQ       sensor_Q;


// ==================================================================================
// 描述:
// 必须定义'halfT '为周期的一半，以及滤波器的参数Kp和Ki
// 四元数'q0', 'q1', 'q2', 'q3'定义为全局变量
// 需要在每一个采样周期调用'IMUupdate()'函数
// 陀螺仪数据单位是弧度/秒，加速度计的单位无关重要，因为会被规范化
// ==================================================================================
//#define Kp 	0.2f    // 比例常数
//#define Ki 	0.0001f  // 积分常数
//#define halfT 0.0005f//半周期
////#define T	0.001f  // 周期为1ms
//// ==================================================================================
//// 变量定义
//float q0 = 1, q1 = 0, q2 = 0, q3 = 0;     	// 四元数
//float exInt = 0, eyInt = 0, ezInt = 0;    	// 误差积分累计值  



//uint8_t Yaw_offset;
//uint16_t Yaw_count=0;
//void Serial_Data_Offset(void)
//{
//	
//	static int32_t ANGLE_YAW=0;
//	
//	if(Yaw_offset)
//	{
//		if(Yaw_count == 0)	
//		{
//			stcAngle_offset.Angle[2] = 0;
//			ANGLE_YAW = 0;
//			Yaw_count = 1;
//		}
//		else if( 0<Yaw_count && Yaw_count< 250)
//		{
//			ANGLE_YAW += stcAngle.Angle[2];
//			Yaw_count ++;
//		}
//		else
//		{
//			stcAngle_offset.Angle[2] = ANGLE_YAW / 250;

//			Yaw_count = 0;
//			Yaw_offset = 0;
//			offset_flag=0;
//		}
//	}
//}



//void Serial_Data_Calculation(void)
//{
//	Serial_Data_Offset();
//	if(offset_flag==0)
//{
//	sensor_Acc.a[0] = stcAcc.a[0]/32768.0f*16.0f;
//	sensor_Acc.a[1] = stcAcc.a[1]/32768.0f*16.0f;
//	sensor_Acc.a[2] = stcAcc.a[2]/32768.0f*16.0f;
//	sensor_Acc.T = stcAcc.T/100.0;
//	
//	sensor_Gyro.w[0] = stcGyro.w[0]/32768.0*2000.0*0.0010653f;
//	sensor_Gyro.w[1] = stcGyro.w[1]/32768.0*2000.0*0.0010653f;
//	sensor_Gyro.w[2] = stcGyro.w[2]/32768.0*2000.0*0.0010653f;
//	sensor_Gyro.T = stcGyro.T/100.0;
//	
//	
//	/*----------------------------------------------------------------
//	----	PIRCH：	Angle[0]；-180° ~ 180°；逆时针变大，顺时针变小
//	----	ROLL：	Angle[1]； -90° ~  90°；正右大，正左小，反右小，反左大
//	----	YAW：		Angle[2]；-180° ~ 180°；逆时针增大，顺时针变小
//	------------------------------------------------------------------*/
//	sensor_Angle.Angle[0] = stcAngle.Angle[0]*180.0f/32768.0f;
//	sensor_Angle.Angle[1] = stcAngle.Angle[1]*180.0f/32768.0f;
////	sensor_Angle.Angle[2] = stcAngle.Angle[2]*180.0f/32768.0f;
//	sensor_Angle.Angle[2] = (stcAngle.Angle[2] - stcAngle_offset.Angle[2])*180.f/32768.0f;
//	if(flag_count==0)
//	{
//		Angle_offset=(stcAngle.Angle[2] - stcAngle_offset.Angle[2])*180.f/32768.0f;
//		flag_count++;
//	}
//	if(sensor_Angle.Angle[2] < -180)	sensor_Angle.Angle[2] += 360.0f;	
//	if(sensor_Angle.Angle[2] > 180)		sensor_Angle.Angle[2] -= 360.0f;	
//	sensor_Angle.Yaw_Radian = sensor_Angle.Angle[2]*pi/180.0f;
//	sensor_Angle.T = stcAngle.T/100.0;
//	
//	
//	sensor_Q.q[0] = stcQ.q[0]/32768.0;
//	sensor_Q.q[1] = stcQ.q[1]/32768.0;
//	sensor_Q.q[2] = stcQ.q[2]/32768.0;
//	sensor_Q.q[3] = stcQ.q[3]/32768.0;
//}
//}



//void CopeSerial2Data(unsigned char ucData)
//{
//	static unsigned char ucRxBuffer[250];
//	static unsigned char ucRxCnt = 0;	
//	
//	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
//	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
//	{
//		ucRxCnt=0;
//		return;
//	}
//	if (ucRxCnt<11) {return;}//数据不满11个，则返回
//	else
//	{
//		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
//		{
//			//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
//			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
//			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
//			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
//			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
//			case 0x59:	memcpy(&stcQ,&ucRxBuffer[2],8);break;
//		}
//		ucRxCnt=0;//清空缓存区
//	}
//}



//	
//void Serial_Quaternion(void)
//{
//	quaternion_Angle.Angle[0] =  (asin (2.0f*(sensor_Q.q[0]*sensor_Q.q[2] - sensor_Q.q[1]*sensor_Q.q[3])) * 57.295779513082320876798154814105f); //ROLL
//	quaternion_Angle.Angle[1] =  (atan2(2.0f*(sensor_Q.q[0]*sensor_Q.q[1] + sensor_Q.q[2]*sensor_Q.q[3]) ,            sensor_Q.q[0]*sensor_Q.q[0] - sensor_Q.q[1]*sensor_Q.q[1] - sensor_Q.q[2]*sensor_Q.q[2] + sensor_Q.q[3]*sensor_Q.q[3]) * 57.295779513082320876798154814105f);	//PITCH
//	quaternion_Angle.Angle[2] = -atan2f(2.0f*(sensor_Q.q[0]*sensor_Q.q[3] + sensor_Q.q[1]*sensor_Q.q[2]) , 1.0f-2.0f*(sensor_Q.q[2]*sensor_Q.q[2] + sensor_Q.q[3]*sensor_Q.q[3]) ) * 57.295779513082320876798154814105f;	//YAW
//	quaternion_Angle.T = stcAngle.T/100.0f;
//}

//void Serial_IMUupdate(void)
//{
//	float norm;
//	float vx, vy, vz;
//	float ex, ey, ez;
//	
//  //四元数积分，求得当前的姿态
//	float q0_last = q0;	
//	float q1_last = q1;	
//	float q2_last = q2;	
//	float q3_last = q3;	

//	//把加速度计的三维向量转成单位向量
//	norm = invSqrt(sensor_Acc.a[0]*sensor_Acc.a[0] + sensor_Acc.a[1]*sensor_Acc.a[1] + sensor_Acc.a[2]*sensor_Acc.a[2]);
//	sensor_Acc.a[0] = sensor_Acc.a[0] * norm;
//	sensor_Acc.a[1] = sensor_Acc.a[1] * norm;
//	sensor_Acc.a[2] = sensor_Acc.a[2] * norm;

//	//估计重力加速度方向在飞行器坐标系中的表示，为四元数表示的旋转矩阵的第三行
//	vx = 2*(q1*q3 - q0*q2);
//	vy = 2*(q0*q1 + q2*q3);
//	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;

//	//加速度计读取的方向与重力加速度方向的差值，用向量叉乘计算
//	ex = sensor_Acc.a[1]*vz - sensor_Acc.a[2]*vy;
//	ey = sensor_Acc.a[2]*vx - sensor_Acc.a[0]*vz;
//	ez = sensor_Acc.a[0]*vy - sensor_Acc.a[1]*vx;

//	//误差累积，已与积分常数相乘
//	exInt = exInt + ex*Ki;
//	eyInt = eyInt + ey*Ki;
//	ezInt = ezInt + ez*Ki;

//	//用叉积误差来做PI修正陀螺零偏，即抵消陀螺读数中的偏移量	
//	sensor_Gyro.w[0] = sensor_Gyro.w[0] + Kp*ex + exInt;
//	sensor_Gyro.w[1] = sensor_Gyro.w[1] + Kp*ey + eyInt;
//	sensor_Gyro.w[2] = sensor_Gyro.w[2] + Kp*ez + ezInt;


//	//一阶近似算法
//	q0 = q0_last + (-q1_last*sensor_Gyro.w[0] - q2_last*sensor_Gyro.w[1] - q3_last*sensor_Gyro.w[2])*halfT;
//	q1 = q1_last + ( q0_last*sensor_Gyro.w[0] + q2_last*sensor_Gyro.w[2] - q3_last*sensor_Gyro.w[1])*halfT;
//	q2 = q2_last + ( q0_last*sensor_Gyro.w[1] - q1_last*sensor_Gyro.w[2] + q3_last*sensor_Gyro.w[0])*halfT;
//	q3 = q3_last + ( q0_last*sensor_Gyro.w[2] + q1_last*sensor_Gyro.w[1] - q2_last*sensor_Gyro.w[0])*halfT; 

////	//二阶近似算法
////	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
////	q0 = q0_last*(1-delta2/8) + (-q1_last*gx - q2_last*gy - q3_last*gz)*halfT;
////	q1 = q1_last*(1-delta2/8) + ( q0_last*gx + q2_last*gz - q3_last*gy)*halfT;
////	q2 = q2_last*(1-delta2/8) + ( q0_last*gy - q1_last*gz + q3_last*gx)*halfT;
////	q3 = q3_last*(1-delta2/8) + ( q0_last*gz + q1_last*gy - q2_last*gx)*halfT;

////	//三阶近似算法
////	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
////	q0 = q0_last*(1-delta2/8) + (-q1_last*gx - q2_last*gy - q3_last*gz)*T*(0.5 - delta2/48);
////	q1 = q1_last*(1-delta2/8) + ( q0_last*gx + q2_last*gz - q3_last*gy)*T*(0.5 - delta2/48);
////	q2 = q2_last*(1-delta2/8) + ( q0_last*gy - q1_last*gz + q3_last*gx)*T*(0.5 - delta2/48);
////	q3 = q3_last*(1-delta2/8) + ( q0_last*gz + q1_last*gy - q2_last*gx)*T*(0.5 - delta2/48);

////	//四阶近似算法
////	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
////	q0 = q0_last*(1 - delta2/8 + delta2*delta2/384) + (-q1_last*gx - q2_last*gy - q3_last*gz)*T*(0.5 - delta2/48);
////	q1 = q1_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gx + q2_last*gz - q3_last*gy)*T*(0.5 - delta2/48);
////	q2 = q2_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gy - q1_last*gz + q3_last*gx)*T*(0.5 - delta2/48);
////	q3 = q3_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gz + q1_last*gy - q2_last*gx)*T*(0.5 - delta2/48);
//			
//	//四元数规范化
//	norm = invSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
//	q0 = q0 * norm;
//	q1 = q1 * norm;
//	q2 = q2 * norm;
//	q3 = q3 * norm;
//	
//	sensor_Angle.Angle[2]  =  -atan2f( 2.0f*(q0*q3+q1*q2) , 1.0f-2.0f*(q2*q2+q3*q3) ) * 57.295779513082320876798154814105f;
//	sensor_Angle.Angle[1]  =  (atan2(2.0f*(q0*q1 + q2*q3),q0*q0 - q1*q1 - q2*q2 + q3*q3)*57.295779513082320876798154814105f);
//  sensor_Angle.Angle[0]  =  (asin (2.0f*(q0*q2 - q1*q3))*57.295779513082320876798154814105f);//-8.1;
//}


#if EN_USART2_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   

//初始化IO 串口1 
//bound:波特率
void uart2_JY901_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//USART2端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化P2，PA3

   //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART2_RX	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =4;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
#endif

}


void USART2_IRQHandler(void)                	//串口2中断服务程序
{
//	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
//  {   
//    USART_SendData(USART2, TxBuffer[TxCounter++]); 
//    USART_ClearITPendingBit(USART2, USART_IT_TXE);
//    if(TxCounter == count) USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
//  }
//	else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//  {
//		CopeSerial2Data((unsigned char)USART2->DR);//处理数据
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//  }
//	
//	USART_ClearITPendingBit(USART2,USART_IT_ORE);
}


#endif	


// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
// 快速计算开根号的倒数
//float invSqrt(float x)
//{
//  float halfx = 0.5f * x;
//  float y = x;
//  long i = *(long*)&y;  // &y表示取y的地址，(long*)是把这个地址转换成long型指针，再取*就是得到这个地址的值，最后还是地址指向的值	
//  i = 0x5f3759df - (i>>1);
//  y = *(float*)&i;
//  y = y * (1.5f - (halfx * y * y));
//  return y;
//}
