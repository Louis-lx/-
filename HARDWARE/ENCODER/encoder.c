#include "encoder.h"

#include "delay.h"


//***************************定时器5初始化 ，使用编码器功能***************************//
//复用TIM5
//PA0----接 编码器A相 或者电机驱动的BM2A标识
//PA1----接 编码器B相 或者电机驱动的BM2B标识
void TIM5_Encoder_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//使能定时器4的时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//端口配置
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //根据设定参数初始化GPIOA

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //复用为TIM5 编码器接口
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //复用为TIM5 编码器接口
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数  
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
   TIM_SetCounter(TIM5,0);
  TIM_Cmd(TIM5, ENABLE); 
}

//***************************定时器2初始化 ，使用编码器功能***************************//
//左电机编码器计数
//PA15----接 编码器A相 或者电机驱动的BM1A标识
//PB3----接 编码器B相 或者电机驱动的BM1B标识
void TIM2_Encoder_Init(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //使能定时器
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);  //使用A B口
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  //PA15
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  //PB3
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource15,GPIO_AF_TIM2);   //复用为TIM2 编码器接口
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);   //复用为TIM2 编码器接口
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							// No prescaling     //不分频
  TIM_TimeBaseStructure.TIM_Period = 65535;  //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数    
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  //初始化定时器
  
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM2,0);
  TIM_Cmd(TIM2, ENABLE); 
}

//***************************定时器3初始化 ，使用编码器功能***************************//
//左电机编码器计数
//PA6----接 编码器A相 或者电机驱动的BM2B标识
//PA7----接 编码器B相 或者电机驱动的BM2A标识
void TIM3_Encoder_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //使能定时器
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //使用A口

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  //PA6 PA7
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);   //复用为TIM2 编码器接口
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);   //复用为TIM2 编码器接口
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							// No prescaling     //不分频
  TIM_TimeBaseStructure.TIM_Period = 65535;  //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数    
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  //初始化定时器
  
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);  
	
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM3,0);
  TIM_Cmd(TIM3, ENABLE);  
	
	
}

//***************************定时器4初始化 ，使用编码器功能***************************//
//复用TIM4
//PB6----接 编码器A相 或者电机驱动的BM1A标识
//PB7----接 编码器B相 或者电机驱动的BM1B标识
void TIM4_Encoder_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能PB端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//端口配置
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);   //根据设定参数初始化GPIOB

  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); //复用为TIM4 编码器接口
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); //复用为TIM4 编码器接口
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}


void TIM1_Encoder_Init(void)
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//使能定时器4的时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能PE端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;//端口配置
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);   //根据设定参数初始化GPIOB

  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //复用为TIM4 编码器接口
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); //复用为TIM4 编码器接口
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM1,0);
  TIM_Cmd(TIM1, ENABLE); 
}

//***************************定时器6初始化 系统每100ms处理一次中断，更新数据，更新pwm等***************************//
void TIM6_INT_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 99;//99自动重新装载寄存器周期的值澹ㄥ计数值澹)
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;//16800时钟分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//对外部时钟进行采样的时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);//参数初始化

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM6, ENABLE);//启动定时器 
}



