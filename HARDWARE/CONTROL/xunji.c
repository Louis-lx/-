#include "xunji.h"
#include "OLED_SPI.h"


extern u16 xunji [2];
int Pwm ; 

extern int SetRPMA,SetRPMB,SetRPMC,SetRPMD;


u8 USART_RX_STAAAA[3] = { 0 };       //接收状态标记	  
u8 Num = 0;              //接收数据的当前位置

float error = 0 ;


void Read_Data(u16 *Data)	       
{	
	u8 y=0;
	u16 Receive_data = 0;       //数据缓存区
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, 0x57);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
/////////////////////////数字量数值///////////////////////////////	
	
//	while(Num != 1)
//	{
//		
//		Delay_ms(1);
//		if(y>5)
//		{
//			y=0;
//			break;
//		}
//		y++;
//	}
//	*Data = USART_RX_STA[0];
	
/////////////////////////数字量数值///////////////////////////////	

///////////////////////////偏移量数值///////////////////////////////	
	
	while(Num != 3)
	{
		
		delay_ms(1);
		if(y>100)
		{
			y=0;
			break;
		}
		y++;
	}
	Receive_data = USART_RX_STAAAA[1];
	Receive_data <<= 8;
	Receive_data |= USART_RX_STAAAA[2];

	*Data = USART_RX_STAAAA[0];
	*(Data+1) = Receive_data;
	
///////////////////////////偏移量数值///////////////////////////////	

	Num = 0; 
}


//void track_PID(float speed)
//{
//	float L_Pwm,R_Pwm;
//	
//	unsigned char temp[20];
//	static float Integral_error,Last_error;
//	int error = 0;         //偏差值
//		 //左右轮速度
//	float P = 0.2, I = 0,D = 0.08;		 //积分系数，微分系数
//	
//	Read_Data(xunji);
//	
//	if(xunji[0]==0)
//	{
//		error = -xunji[1];
//	}
//	else
//	{
//		error = xunji[1];
//	}
//	Integral_error += error;
//	sprintf(temp,"err:%d",error);
//	OLED_P6x8Str(0,3,temp);
//	
//	Pwm = (error*P+Integral_error*I+(error-Last_error)*D);
//	
//	
//	Last_error = error;
//	
//	if(Pwm > 0)
//	{
//		if(Pwm > Pwm+10)
//			L_Pwm = (Pwm+10);
//		if(R_Pwm > (Pwm+10))
//			R_Pwm = (Pwm+10);
//		
//		if(L_Pwm <= 15)
//			L_Pwm = 15;
//		if(R_Pwm <= 15)
//			R_Pwm = 15;
//	}
//	
//	SetRPMA = speed -  
//	
//}


void track_PID(int V,float P)
{
 static float Integral_error,Last_error;
 u16 temp_data[2] = { 0 };    
      
 int L_V,R_V;  
 float I = 0,D = 0;  
 
 Read_Data(temp_data);
 
 if(temp_data[0]==0)
 {
  error = -temp_data[1];
 }
 else
 {
  error = temp_data[1];
 }
 

 Integral_error += error;
 
 R_V = (V-(error*P+Integral_error*I+(error-Last_error)*D));
 L_V = (V+(error*P+Integral_error*I+(error-Last_error)*D));
 
 Last_error = error;
 
	 if(V > 0)
	 {
	  if(L_V > (V+80))
	   L_V = (V+80);
	  if(R_V > (V+80))
	   R_V = (V+80);
	  if(L_V <= 40)
	   L_V = 40;
	  if(R_V <= 40)
	   R_V = 40;
	 }
 
	SetRPMA = R_V ;
	
	SetRPMB = L_V;
	 
	SetRPMC = L_V ;
	
	SetRPMD = R_V;
	 
 

}



void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		USART_RX_STAAAA[Num++] =USART_ReceiveData(USART1);	//读取接收到的数据

//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	} 	
}

