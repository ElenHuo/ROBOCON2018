#include "main.h"


u32 TIME_ISR_CNT=0;
unsigned short int PPM_Sample_Cnt=0;
unsigned short int PPM_Isr_Cnt=0;
u32 Last_PPM_Time=0;
u32 PPM_Time=0;
u16 PPM_Time_Delta=0;
u16 PPM_Time_Max=0;
unsigned short int PPM_Start_Time=0;
unsigned short int PPM_Finished_Time=0;
unsigned short int PPM_Is_Okay=0;
unsigned short int PPM_Databuf[8]={0};
extern uint32_t Timer2_Count;






void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
//系统运行时间获取，单位us
		
		/**********************/
    Last_PPM_Time=PPM_Time;
    PPM_Time=1000*Timer2_Count+TIM2->CNT;//us
		/**********************/
		
    PPM_Time_Delta=PPM_Time-Last_PPM_Time;
    //PPM中断进入判断
    if(PPM_Isr_Cnt<100)  PPM_Isr_Cnt++;
   //PPM解析开始
    if(PPM_Is_Okay==1)
    {
    PPM_Sample_Cnt++;
    //对应通道写入缓冲区
    PPM_Databuf[PPM_Sample_Cnt-1]=PPM_Time_Delta;
    //单次解析结束
      if(PPM_Sample_Cnt>=8)
        PPM_Is_Okay=0;
    }
    if(PPM_Time_Delta>=2050)//帧结束电平至少2ms=2000us
    {
      PPM_Is_Okay=1;
      PPM_Sample_Cnt=0;
    }
  }
  EXTI_ClearITPendingBit(EXTI_Line5);
}
	   
//外部中断初始化程序
//初始化PE5
void PPM_EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
}












