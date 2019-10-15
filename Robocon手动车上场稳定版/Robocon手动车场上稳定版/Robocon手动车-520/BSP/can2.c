#include "main.h"

/*----CAN2_TX-----PB6----*/
/*----CAN2_RX-----PB12----*/

uint32_t can_count = 0;
float change=22.7555;
Encoder CM1Encoder;
Encoder CM2Encoder;
Encoder CM3Encoder;


void Set_Motor_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq)
{
    CanTxMsg tx_message;
    tx_message.StdId = 0x200;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = (uint8_t)(cm1_iq >> 8);//高8位
    tx_message.Data[1] = (uint8_t)cm1_iq;//低8位
    tx_message.Data[2] = (uint8_t)(cm2_iq >> 8);
    tx_message.Data[3] = (uint8_t)cm2_iq;
    tx_message.Data[4] = (uint8_t)(cm3_iq >> 8);
    tx_message.Data[5] = (uint8_t)cm3_iq;
    tx_message.Data[6] = (uint8_t)(cm4_iq >> 8);
    tx_message.Data[7] = (uint8_t)cm4_iq;
    CAN_Transmit(CANx,&tx_message);
}


/********************************************************************************
																 启动偏差矫正
*********************************************************************************/

void offsetEncoder( Encoder *p,CanRxMsg *msg)
{
	p->offset_raw_value=(msg->Data[0]<<8|msg->Data[1]);
}


/********************************************************************************
																读取电机反馈量
*********************************************************************************/
void getEncoder( Encoder *p,CanRxMsg *msg)
{		
		p->last_raw_value=p->raw_value;
		p->last_rpm=p->rpm;
		p->raw_value=(msg->Data[0]<<8|msg->Data[1]);
		p->rpm=(msg->Data[2]<<8|msg->Data[3]);
		p->current=(msg->Data[4]<<8|msg->Data[5]);
		p->t=(msg->Data[6]);
		p->diff=p->raw_value-p->last_raw_value;
		if(p->diff< -4096)
		{
			p->round++;
			
		}
		else if(p->diff > 4096)p->round--;
		
		p->total_raw=(float)(p->round*8192 + p->raw_value - p->offset_raw_value);//转的总的角度
		p->degree=p->total_raw/change; //°数转换
		
}


void CAN2_RX0_IRQHandler(void)
{
    CanRxMsg rx_message;
    if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET) 
    {
        CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
        CAN_Receive(CAN2, CAN_FIFO0, &rx_message);  
       //电机编码器数据处理
				switch(rx_message.StdId){
					case CAN_BUS2_MOTOR1_FEEDBACK_MSG_ID:
					{
						(can_count++<=50) ? offsetEncoder(&CM1Encoder,&rx_message):getEncoder(&CM1Encoder,&rx_message);
					}break;
					case CAN_BUS2_MOTOR2_FEEDBACK_MSG_ID:
					{
						(can_count++<=50) ? offsetEncoder(&CM2Encoder,&rx_message):getEncoder(&CM2Encoder,&rx_message);
					}break;
					case CAN_BUS2_MOTOR3_FEEDBACK_MSG_ID:
					{
						(can_count++<=50) ? offsetEncoder(&CM3Encoder,&rx_message):getEncoder(&CM3Encoder,&rx_message);
					}break;

					default:{}
				}
    }
}


void CAN2_TX_IRQHandler(void) //CAN TX
{
  if (CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET)    //if transmit mailbox is empty 
  {
	   CAN_ClearITPendingBit(CAN2,CAN_IT_TME);   
  }
}


void CAN2_Configuration(void)
{
    CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;
    NVIC_InitTypeDef       nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2); 

    gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_12 ;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &gpio);

    nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    nvic.NVIC_IRQChannel = CAN2_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    CAN_DeInit(CAN2);
    CAN_StructInit(&can);

    can.CAN_TTCM = DISABLE;
    can.CAN_ABOM = DISABLE;    
    can.CAN_AWUM = DISABLE;    
    can.CAN_NART = DISABLE;    
    can.CAN_RFLM = DISABLE;    
    can.CAN_TXFP = ENABLE;     
    can.CAN_Mode = CAN_Mode_Normal; 
    can.CAN_SJW  = CAN_SJW_1tq;
    can.CAN_BS1 = CAN_BS1_9tq;
    can.CAN_BS2 = CAN_BS2_4tq;
    can.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN2, &can);
    
    can_filter.CAN_FilterNumber=14;// can2设为14
    can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
    can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
    can_filter.CAN_FilterIdHigh=0x0000;
    can_filter.CAN_FilterIdLow=0x0000;
    can_filter.CAN_FilterMaskIdHigh=0x0000;
    can_filter.CAN_FilterMaskIdLow=0x0000;
    can_filter.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
    can_filter.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE);
}

