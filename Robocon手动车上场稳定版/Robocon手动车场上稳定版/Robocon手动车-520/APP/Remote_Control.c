//#include "main.h"
//int16_t VX,VY,VZ;
//float Remote_Vx,Remote_Vy,Remote_Vz;



//uint8_t Remote_Count=0;

//void Remote_Task(void)
//{
//	if(AU1<1600 && KEY_1==0)
//	{
//		REMOTE=AUTO_MODE;//�Ҳఴ��
//	}
//	if(AU1>1600)	
//	{
//		REMOTE=HAND_MODE;
//		Remote_Count=0;
//		
//	}
//	switch(REMOTE)
//	{
//		case AUTO_MODE://0
//		{
//			if(KEY_0==0)
//			{
//				delay_ms(100);
//				if(KEY_0==0)Remote_Count++;

//			}		
//			if(Remote_Count==1)
//			{
//				NOW_STATE=PREPARE_STATE;
//			}
//			else if(Remote_Count==2)
//			{
//				NOW_STATE=TAKE_BALL_STATE1;
//				TAKEBALL_STATE = TAKING_DONE; //��һ����
//				
//			}
//			else if(Remote_Count==3)
//			{
//				NOW_STATE=RELAY_STATE2;
//				RELAY_STATE=RELAY_SUCCEEDED;
//			}	
//			else if(Remote_Count==4)
//			{
//				NOW_STATE=TAKE_BALL_STATE2;
//				TAKEBALL_STATE= TAKING_DONE;
//			}	
//			else if(Remote_Count==5)
//			{
//				NOW_STATE=RELAY_STATE2;
//				RELAY_STATE=RELAY_SUCCEEDED;
//			}
//			//��ѭ��ִ�� 
//    	else if(Remote_Count>5 &&  (Remote_Count % 2)==0 )
//			{
//				NOW_STATE=TAKE_BALL_STATE2;
//				TAKEBALL_STATE= TAKING_DONE;
//			}
//			else if(Remote_Count>5 &&  (Remote_Count % 2)==1 )
//			{
//				NOW_STATE=RELAY_STATE2;
//				RELAY_STATE=RELAY_SUCCEEDED;
//			}
//		}break;
//			
//		case HAND_MODE:
//		{
//			Fire_Remote_Output();
//			
//		}break;
//		default:{}
//		
//	}

//	
//		
//}



//void Fire_Remote_Output(void)
//{	
////	  
////		VX=LX-1500;
////		VY=LY-1500;
////		VZ=RX-1500;
////		if(AU1<1600) //����ģʽ
////		{
////		Remote_Vx = (float)(VX*10);
////		Remote_Vy = (float)(VY*10);
////		}
////		else  //����ģʽ
////		{
////		Remote_Vx = (float)(VX*1.5);
////		Remote_Vy = (float)(VY*1.5);
////		}
////	  
//////		Remote_Vz = (float)(VZ*2);
////		Vx=Remote_Vx;
////		Vy=Remote_Vy;
//////		Vz=Remote_Vz;
////		Theta_Hold();
////		//theta=90+sensor_Angle.Angle[2];//Ĭ��0�㣬��ʱ�����ӣ�˳ʱ�����
////		
//}


