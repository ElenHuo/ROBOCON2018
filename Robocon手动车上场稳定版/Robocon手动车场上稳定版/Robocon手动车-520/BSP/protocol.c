#include "main.h"


extern u8 USART_RX_BUF[USART_REC_LEN];

void Prepare_Data_1(void)
{
//	int16_t send_data;
//	unsigned char sum = 0;
//	
//	USART_RX_BUF[0] = 0XAA;
//	sum += USART_RX_BUF[0];
//	USART_RX_BUF[1] = 0XAA;
//	sum += USART_RX_BUF[1];	
//	USART_RX_BUF[2] = 0X01;
//	sum += USART_RX_BUF[2];
//	USART_RX_BUF[3] = 0X0C;
//	sum += USART_RX_BUF[3];
//	
//	send_data = stcAngle.Angle[0]*2/3;  //ROLL
//	USART_RX_BUF[4] = (send_data>>8);
//	sum += USART_RX_BUF[4];
//	USART_RX_BUF[5] = send_data;
//	sum += USART_RX_BUF[5];	
//	send_data = stcAngle.Angle[1]*2/3;	//PITCH
//	USART_RX_BUF[6] = (send_data>>8);
//	sum += USART_RX_BUF[6];
//	USART_RX_BUF[7] = send_data;
//	sum += USART_RX_BUF[7];	
//	send_data = stcAngle.Angle[2]*2/3;	//YAW
//	USART_RX_BUF[8] = (send_data>>8);
//	sum += USART_RX_BUF[8];
//	USART_RX_BUF[9] = send_data;
//	sum += USART_RX_BUF[9];
//	
//	USART_RX_BUF[10] = 0;
//	USART_RX_BUF[11] = 0;
//	USART_RX_BUF[12] = 0;
//	USART_RX_BUF[13] = 0;
//	USART_RX_BUF[14] = 0;
//	USART_RX_BUF[15] = 0;
//	
//	USART_RX_BUF[16] = sum;
//	sum = 0;
//	
//	USART_RX_BUF[17] = 0XAA;
//	sum += USART_RX_BUF[17];
//	USART_RX_BUF[18] = 0XAA;
//	sum += USART_RX_BUF[18];	
//	USART_RX_BUF[19] = 0X02;
//	sum += USART_RX_BUF[19];
//	USART_RX_BUF[20] = 0X12;
//	sum += USART_RX_BUF[20];
//	
//	send_data = now.Ecder_Pos.a;               //ACC_X	 //������Aλ��ģʽ��һ����
//	USART_RX_BUF[21] = (send_data>>8);
//	sum += USART_RX_BUF[21];
//	USART_RX_BUF[22] = send_data;
//	sum += USART_RX_BUF[22];	
//	send_data = now.Ecder_Pos.b;								//ACC_Y	 //������Bλ��ģʽ��һ����
//	USART_RX_BUF[23] = (send_data>>8);
//	sum += USART_RX_BUF[23];
//	USART_RX_BUF[24] = send_data;
//	sum += USART_RX_BUF[24];
//	send_data = now.Ecder_Pos.c;								//ACC_Z	 //������Cλ��ģʽ��һ����
//	USART_RX_BUF[25] = (send_data>>8);
//	sum += USART_RX_BUF[25];
//	USART_RX_BUF[26] = send_data;
//	sum += USART_RX_BUF[26];
//	send_data = V.a;													//GYRO_X	//������A���ٶ�
//	USART_RX_BUF[27] = (send_data>>8);
//	sum += USART_RX_BUF[27];
//	USART_RX_BUF[28] = send_data;
//	sum += USART_RX_BUF[28];
//	send_data = V.b;													//GYRO_Y	//������B���ٶ�
//	USART_RX_BUF[29] = (send_data>>8);
//	sum += USART_RX_BUF[29];
//	USART_RX_BUF[30] = send_data;
//	sum += USART_RX_BUF[30];
//	send_data = V.c;													//GYRO_Z	//������C���ٶ�
//	USART_RX_BUF[31] = (send_data>>8);
//	sum += USART_RX_BUF[31];
//	USART_RX_BUF[32] = send_data;
//	sum += USART_RX_BUF[32];
//	send_data = last.x;										//MAG_X		//������������������X����ƶ�����
//	USART_RX_BUF[33] = (send_data>>8);
//	sum += USART_RX_BUF[33];
//	USART_RX_BUF[34] = send_data;
//	sum += USART_RX_BUF[34];
//	send_data = last.y;										//MAG_Y		//������������������Y����ƶ�����
//	USART_RX_BUF[35] = (send_data>>8);
//	sum += USART_RX_BUF[35];
//	USART_RX_BUF[36] = send_data;
//	sum += USART_RX_BUF[36];
//	send_data = last.theta_c;								//MAG_Z		//�����������������Z�����ת�Ƕ�
//	USART_RX_BUF[37] = (send_data>>8);
//	sum += USART_RX_BUF[37];
//	USART_RX_BUF[38] = send_data;
//	sum += USART_RX_BUF[38];
//	
//	USART_RX_BUF[39] = sum;
//	sum = 0;
}


void DMA2_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx,u32 par,u32 mar,u16 ndtr)
{ 
	DMA_InitTypeDef  DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
	
  DMA_DeInit(DMA_Streamx);
	
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = chx;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = par;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = mar;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize = ndtr;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(DMA_Streamx, &DMA_InitStructure);//��ʼ��DMA Stream
} 

//����һ��DMA����
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:���ݴ�����  
void DMA2_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	DMA_Cmd(DMA_Streamx, DISABLE);                      //�ر�DMA���� 

	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//ȷ��DMA���Ա�����  

	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //���ݴ�����  

	DMA_Cmd(DMA_Streamx, ENABLE);                      //����DMA���� 
}	 

