#include "control.h"
#include "pid.h"
#include "datascope.h"
#include "delay.h"
#include "motor.h"
#include "sys.h"
 #include "FreeRTOS.h"
 #include "task.h"
 #include "OLED_SPI.h"
 #include "xunji.h"
 #include "usart.h"
 #include "UART.h"
 
int para_A,para_B,para_C,para_D;//增量
int Motor_A,Motor_B,Motor_C,Motor_D;
int SetRPMA=40,SetRPMB=40,SetRPMC=40,SetRPMD=40;//设置目标值单位RPM

extern float Now_Yaw ;


float Roll;
float Pitch;
float Yaw;
extern 	u16  xunji[2] ;
extern unsigned char Dataa[6];
extern float to_Yaw;
int temp ;


//使用减速比是1：30的减速箱
#define SetPointA SetRPMA*1320/6000//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量
#define SetPointB SetRPMB*1320/6000//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量
#define SetPointC SetRPMC*1320/6000//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量
#define SetPointD SetRPMD*1320/6000//换算成编码器速度，因为最终pid控制的是编码器的脉冲数量

float ForWardUsingWit(float to_yaw){

	static float IIntegral_error,LLast_error;
	float back = 0;
	
	int error = 0;      
	
	float P = 0.1, I = 0,D = 0.15;		
	
	
	error = to_yaw - ( Yaw-180);
	
	IIntegral_error += error;

	back  = (error*P+IIntegral_error*I+(error-LLast_error)*D);
	
	LLast_error = error;
	
	return back;
	
}

float  ForWardUsingWitt(){
	float err ;
	
	float NowYaw ;
	
	NowYaw = Yaw ;
	
	err = ForWardUsingWit(NowYaw);
	
	return err ;
	
}

int myabs(int a){
	int temp;
	if(a < 0) temp = -a;
	else temp = a;
	return temp;
}

/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int Read_Encoder(u8 x)
{
   int Encoder_TIM;    
   switch(x)
	 {
		 case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=0;break;
		 case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4-> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}


int Encoder_A,Encoder_B,Encoder_C,Encoder_D;  //编码器脉冲数
int Send_Count,i;
//extern int adc_data;
int position_out = 0;
int ac_speed_b;
int bigout_B;
char sss[10];
//Time6定时器6中断服务函数
char tem ;
unsigned char USART_RX_BUFFF[200];
int USART_RX_STAAA;
int k210;
char lenn ;
char msgg[20];

int StringToDECC(unsigned char* rdata,unsigned char len)
{
    unsigned char  i;
    int wdata = 0;
    unsigned char temp[4];
	char f = 0 ;

	if(rdata[0]=='-')
		f= 1;

	
    for(i = 0; i<len-2; i++)
    {
        if((*(rdata+i) >= '0') && (*(rdata+i) <= '9')) temp[i] =  *(rdata+i) - '0'; 
    }
    switch(i) {
    case 1:
        wdata = temp[i-1];
        break;
    case 2:
        wdata = temp[i-2]*10 + temp[i-1];
        break;
    case 3:
        wdata = temp[i-3]*100 + temp[i-2]*10 + temp[i-1];
        break;
    case 4:
        wdata = temp[i-4]*1000 + temp[i-3]*100 + temp[i-2]*10 + temp[i-1];
        break;
    default:
        break;
    }
	if(f==1){
		if(wdata>10&&wdata<20)
			wdata = wdata%10;
		else
			wdata = wdata%100;
		wdata =  -wdata ;
	}
    return wdata;
}

extern int Pwm;

void TIM6_DAC_IRQHandler(void)
{

	unsigned char buf [20];
	

	int k ;
		Read_Data(xunji);
	
		send_Data(0xff);
		send_Data(0xaa);
		send_Data(0x27);
		send_Data(0x3f);
		send_Data(0x00);
		
		
		temp = Dataa[5]<<8|Dataa[4];
		Yaw = 1.0*temp/32768*180;
		temp = 0 ;
	
	
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET) //时间到了
	{
			
//				k = ForWardUsingWit(90);
//				
//				sprintf(buf,"K = %0.2f",k);
//				OLED_P6x8Str(0,4,buf);
//		
//				SetRPMA=50 - k;
//				SetRPMB=50 + k;
//				SetRPMC=50 +k;
//				SetRPMD=50 - k;
		
				
				SetRPMA=50 ;
				SetRPMB=50 ;
				SetRPMC=50 ;
				SetRPMD=50 ;
		

		
//				SetRPMA=80-Pwm;
//				SetRPMB=80+Pwm;
//				SetRPMC=80+Pwm;
//				SetRPMD=80-Pwm;
		

		
		}		
		Encoder_A=Read_Encoder(5);                //读取编码器 			PA0 PA1
		Encoder_B=Read_Encoder(2);                //读取编码器			PA15 PB3 
		Encoder_C=Read_Encoder(3);                //读取编码器 
		Encoder_D=Read_Encoder(4);                //读取编码器

		
		para_A=SPEED_PID_A(Encoder_A,SetPointA);//左前电机，计数得到增量式PID的增量数值 
		para_B=SPEED_PID_B(Encoder_B,SetPointB);//右前电机，计数得到增量式PID的增量数值
		para_C=SPEED_PID_C(Encoder_C,SetPointC);//右后电机，计数得到增量式PID的增量数值
		para_D=SPEED_PID_D(Encoder_D,SetPointD);	//左后电机，计数得到增量式PID的增量数值
		
	
		
////////////////////////	
		if((para_A<-3)||(para_A>3)) // 中间的小部分区域不做 PID 调整，避免误差较小时频繁调节引起震荡。
		{
			Motor_A +=para_A;  
		} 
		if(Motor_A>7000)Motor_A=7000;//限幅
		if(Motor_A<-7000)Motor_A=-7000;

		//更新pwm
		
		if(Motor_A > 0){
			AIN1 = 1;		
			AIN2 = 0;
//		MotorA1 = 1;
//		MotorA2 = 0;//正
		}else{
			AIN1 = 0;		
			AIN2 = 1;
//		MotorA1 = 0;
//		MotorA2 = 1;//反
		}
		
		TIM8->CCR1 = myabs(Motor_A);
////////////////////////		
		if((para_B<-3)||(para_B>3)) // 中间的小部分区域不做 PID 调整，避免误差较小时频繁调节引起震荡。
		{
			Motor_B +=para_B;  
		} 

		bigout_B=Motor_B+position_out;
		if(bigout_B>7000)bigout_B=7000;
		if(bigout_B<-7000)bigout_B=-7000;
		if(bigout_B > 0){

			BIN1 = 1;	
			BIN2 = 0;
		}else{

			BIN1 = 0;	
			BIN2 = 1;
		}
		TIM8->CCR2 = myabs(bigout_B);
////////////////////////		
		if((para_C<-3)||(para_C>3)) // 中间的小部分区域不做 PID 调整，避免误差较小时频繁调节引起震荡。
		{
			Motor_C +=para_C;  
		} 
		if(Motor_C>7000)Motor_C=7000;//限幅
		if(Motor_C<-7000)Motor_C=-7000;

		//更新pwm
		
//		if(Motor_C > 0){
//		CIN1 = 0;
//		CIN2 = 1;//正
//		}else{
//		CIN1 = 1;
//		CIN2 = 0;//反
//		}
		
		if(Motor_C > 0){
		CIN1 = 1;		
		CIN2 = 0;
		}else{
		CIN1 = 0;		
		CIN2 = 1;
		}
		
		TIM8->CCR3 = Motor_C;
////////////////////////
		if((para_D<-3)||(para_D>3)) // 中间的小部分区域不做 PID 调整，避免误差较小时频繁调节引起震荡。
		{
			Motor_D +=para_D;  
		} 
		if(Motor_D>7000)Motor_D=7000;//限幅
		if(Motor_D<-7000)Motor_D=-7000;

		//更新pwm
		
		if(Motor_D > 0){

		DIN1 = 0;	
		DIN2 = 1;
		}else{
	
		DIN1 = 1;
		DIN2 = 0;
		}

		TIM8->CCR4 = Motor_D;
		//myabs(Motor_D);
////////////////////////		

//		printf("a = %d\r\n",Encoder_A);
//		printf("b = %d\r\n",Encoder_B);
//		printf("c = %d\r\n",Encoder_C);
//		printf("d = %d\r\n",Encoder_D);
	
	

//	DataScope_Get_Channel_Data(Encoder_A*6000/1320, 1 );
//	DataScope_Get_Channel_Data(Encoder_B*6000/1320, 2 );
//	DataScope_Get_Channel_Data(Encoder_C*6000/1320, 3 );
//	DataScope_Get_Channel_Data(Encoder_D*6000/1320, 4 );
		
//	DataScope_Get_Channel_Data(Encoder_A, 1 );
//	DataScope_Get_Channel_Data(Encoder_B, 2 );
//	DataScope_Get_Channel_Data(Encoder_C, 3 );
//	DataScope_Get_Channel_Data(Encoder_D, 4 );

//	DataScope_Get_Channel_Data(100, 5);
//	DataScope_Get_Channel_Data(40, 6);
//	Send_Count=DataScope_Data_Generate(6);
//	
//	for( i = 0 ; i < Send_Count; i++)
//	{
//		while((UART4->SR&0X40)==0);
//		UART4->DR = DataScope_OutPut_Buffer[i];
//	}

//	temp = Dataa[1]<<8|Dataa[0];
//	Roll = 1.0*temp/32768*180;
//	temp = 0 ;
//	
//	temp = Dataa[3]<<8|Dataa[2];
//	Pitch = 1.0*temp/32768*180;
//	temp = 0 ;
//	

	
//	DataScope_Get_Channel_Data(Roll, 1 );
//	DataScope_Get_Channel_Data(Pitch, 2 );
//	DataScope_Get_Channel_Data(Yaw, 3 );
//	DataScope_Get_Channel_Data(k, 4 );
//	
//	DataScope_Get_Channel_Data(Encoder_C*6000/1320, 5 );
//	DataScope_Get_Channel_Data(Encoder_D*6000/1320, 6 );

//	DataScope_Get_Channel_Data(Dataa[3], 4 );
//	DataScope_Get_Channel_Data(Dataa[4], 5 );
//	DataScope_Get_Channel_Data(Dataa[5], 6 );
//	DataScope_Get_Channel_Data(Encoder_C, 3 );
//	DataScope_Get_Channel_Data(Encoder_D, 4 );

//	DataScope_Get_Channel_Data(100, 7);
//	DataScope_Get_Channel_Data(40, 6);

//	DataScope_Get_Channel_Data(xunji[1], 1 );
//	DataScope_Get_Channel_Data(50, 2 );
//	Send_Count=DataScope_Data_Generate(2);
//	
//	for( i = 0 ; i < Send_Count; i++)
//	{
//		while((UART4->SR&0X40)==0);
//		UART4->DR = DataScope_OutPut_Buffer[i];
//	}

	TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);     //清中断
	
//	CPU_CRITICAL_EXIT();
//	OSIntExit();
}


//void UART4_IRQHandler( void )
//{
//	u8 Res;
//	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) 
//	{

//		Res =USART_ReceiveData(UART4);
//		if((USART_RX_STAAA&0x8000)==0)
//		{
//			if(USART_RX_STAAA&0x4000)
//			{
//				if(Res!=0x0a)USART_RX_STAAA=0;
//				else USART_RX_STAAA|=0x8000;	
//			}
//			else
//			{	
//				if(Res==0x0d)USART_RX_STAAA|=0x4000;
//				else
//				{
//					USART_RX_BUFFF[USART_RX_STAAA&0X3FFF]=Res ;
//					USART_RX_STAAA++;
//					if(USART_RX_STAAA>(200-1))USART_RX_STAAA=0;  
//				}		 
//			}
//		}   		 
//  } 
//}
