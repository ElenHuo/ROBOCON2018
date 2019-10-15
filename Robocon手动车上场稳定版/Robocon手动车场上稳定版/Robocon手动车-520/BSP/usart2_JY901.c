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
// ����:
// ���붨��'halfT 'Ϊ���ڵ�һ�룬�Լ��˲����Ĳ���Kp��Ki
// ��Ԫ��'q0', 'q1', 'q2', 'q3'����Ϊȫ�ֱ���
// ��Ҫ��ÿһ���������ڵ���'IMUupdate()'����
// ���������ݵ�λ�ǻ���/�룬���ٶȼƵĵ�λ�޹���Ҫ����Ϊ�ᱻ�淶��
// ==================================================================================
//#define Kp 	0.2f    // ��������
//#define Ki 	0.0001f  // ���ֳ���
//#define halfT 0.0005f//������
////#define T	0.001f  // ����Ϊ1ms
//// ==================================================================================
//// ��������
//float q0 = 1, q1 = 0, q2 = 0, q3 = 0;     	// ��Ԫ��
//float exInt = 0, eyInt = 0, ezInt = 0;    	// �������ۼ�ֵ  



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
//	----	PIRCH��	Angle[0]��-180�� ~ 180�㣻��ʱ����˳ʱ���С
//	----	ROLL��	Angle[1]�� -90�� ~  90�㣻���Ҵ�����С������С�������
//	----	YAW��		Angle[2]��-180�� ~ 180�㣻��ʱ������˳ʱ���С
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
//	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
//	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
//	{
//		ucRxCnt=0;
//		return;
//	}
//	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
//	else
//	{
//		switch(ucRxBuffer[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
//		{
//			//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
//			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
//			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
//			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
//			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
//			case 0x59:	memcpy(&stcQ,&ucRxBuffer[2],8);break;
//		}
//		ucRxCnt=0;//��ջ�����
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
//  //��Ԫ�����֣���õ�ǰ����̬
//	float q0_last = q0;	
//	float q1_last = q1;	
//	float q2_last = q2;	
//	float q3_last = q3;	

//	//�Ѽ��ٶȼƵ���ά����ת�ɵ�λ����
//	norm = invSqrt(sensor_Acc.a[0]*sensor_Acc.a[0] + sensor_Acc.a[1]*sensor_Acc.a[1] + sensor_Acc.a[2]*sensor_Acc.a[2]);
//	sensor_Acc.a[0] = sensor_Acc.a[0] * norm;
//	sensor_Acc.a[1] = sensor_Acc.a[1] * norm;
//	sensor_Acc.a[2] = sensor_Acc.a[2] * norm;

//	//�����������ٶȷ����ڷ���������ϵ�еı�ʾ��Ϊ��Ԫ����ʾ����ת����ĵ�����
//	vx = 2*(q1*q3 - q0*q2);
//	vy = 2*(q0*q1 + q2*q3);
//	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;

//	//���ٶȼƶ�ȡ�ķ������������ٶȷ���Ĳ�ֵ����������˼���
//	ex = sensor_Acc.a[1]*vz - sensor_Acc.a[2]*vy;
//	ey = sensor_Acc.a[2]*vx - sensor_Acc.a[0]*vz;
//	ez = sensor_Acc.a[0]*vy - sensor_Acc.a[1]*vx;

//	//����ۻ���������ֳ������
//	exInt = exInt + ex*Ki;
//	eyInt = eyInt + ey*Ki;
//	ezInt = ezInt + ez*Ki;

//	//�ò���������PI����������ƫ�����������ݶ����е�ƫ����	
//	sensor_Gyro.w[0] = sensor_Gyro.w[0] + Kp*ex + exInt;
//	sensor_Gyro.w[1] = sensor_Gyro.w[1] + Kp*ey + eyInt;
//	sensor_Gyro.w[2] = sensor_Gyro.w[2] + Kp*ez + ezInt;


//	//һ�׽����㷨
//	q0 = q0_last + (-q1_last*sensor_Gyro.w[0] - q2_last*sensor_Gyro.w[1] - q3_last*sensor_Gyro.w[2])*halfT;
//	q1 = q1_last + ( q0_last*sensor_Gyro.w[0] + q2_last*sensor_Gyro.w[2] - q3_last*sensor_Gyro.w[1])*halfT;
//	q2 = q2_last + ( q0_last*sensor_Gyro.w[1] - q1_last*sensor_Gyro.w[2] + q3_last*sensor_Gyro.w[0])*halfT;
//	q3 = q3_last + ( q0_last*sensor_Gyro.w[2] + q1_last*sensor_Gyro.w[1] - q2_last*sensor_Gyro.w[0])*halfT; 

////	//���׽����㷨
////	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
////	q0 = q0_last*(1-delta2/8) + (-q1_last*gx - q2_last*gy - q3_last*gz)*halfT;
////	q1 = q1_last*(1-delta2/8) + ( q0_last*gx + q2_last*gz - q3_last*gy)*halfT;
////	q2 = q2_last*(1-delta2/8) + ( q0_last*gy - q1_last*gz + q3_last*gx)*halfT;
////	q3 = q3_last*(1-delta2/8) + ( q0_last*gz + q1_last*gy - q2_last*gx)*halfT;

////	//���׽����㷨
////	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
////	q0 = q0_last*(1-delta2/8) + (-q1_last*gx - q2_last*gy - q3_last*gz)*T*(0.5 - delta2/48);
////	q1 = q1_last*(1-delta2/8) + ( q0_last*gx + q2_last*gz - q3_last*gy)*T*(0.5 - delta2/48);
////	q2 = q2_last*(1-delta2/8) + ( q0_last*gy - q1_last*gz + q3_last*gx)*T*(0.5 - delta2/48);
////	q3 = q3_last*(1-delta2/8) + ( q0_last*gz + q1_last*gy - q2_last*gx)*T*(0.5 - delta2/48);

////	//�Ľ׽����㷨
////	float delta2 = (gx*gx + gy*gy + gz*gz)*T*T;
////	q0 = q0_last*(1 - delta2/8 + delta2*delta2/384) + (-q1_last*gx - q2_last*gy - q3_last*gz)*T*(0.5 - delta2/48);
////	q1 = q1_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gx + q2_last*gz - q3_last*gy)*T*(0.5 - delta2/48);
////	q2 = q2_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gy - q1_last*gz + q3_last*gx)*T*(0.5 - delta2/48);
////	q3 = q3_last*(1 - delta2/8 + delta2*delta2/384) + ( q0_last*gz + q1_last*gy - q2_last*gx)*T*(0.5 - delta2/48);
//			
//	//��Ԫ���淶��
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


#if EN_USART2_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   

//��ʼ��IO ����1 
//bound:������
void uart2_JY901_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��P2��PA3

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART2_RX	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =4;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
#endif

}


void USART2_IRQHandler(void)                	//����2�жϷ������
{
//	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
//  {   
//    USART_SendData(USART2, TxBuffer[TxCounter++]); 
//    USART_ClearITPendingBit(USART2, USART_IT_TXE);
//    if(TxCounter == count) USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
//  }
//	else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//  {
//		CopeSerial2Data((unsigned char)USART2->DR);//��������
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//  }
//	
//	USART_ClearITPendingBit(USART2,USART_IT_ORE);
}


#endif	


// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
// ���ټ��㿪���ŵĵ���
//float invSqrt(float x)
//{
//  float halfx = 0.5f * x;
//  float y = x;
//  long i = *(long*)&y;  // &y��ʾȡy�ĵ�ַ��(long*)�ǰ������ַת����long��ָ�룬��ȡ*���ǵõ������ַ��ֵ������ǵ�ַָ���ֵ	
//  i = 0x5f3759df - (i>>1);
//  y = *(float*)&i;
//  y = y * (1.5f - (halfx * y * y));
//  return y;
//}
