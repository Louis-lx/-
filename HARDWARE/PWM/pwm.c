#include "pwm.h"

void MOTOR_PWM_Init(u16 arr,u16 psc)
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	
//	TIM_TimeBaseStructure.TIM_Period = arr;
//	TIM_TimeBaseStructure.TIM_Prescaler = psc;
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
//	
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
////	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
////	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
//	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
//	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
//	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
//	TIM_Cmd(TIM8, ENABLE);
//	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	  //TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTC时钟	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;   //GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PC口
	
	//Sets the value of the auto-reload register cycle for the next update event load activity
	//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	//Sets the pre-divider value used as the TIMX clock frequency divisor
	//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	//Set the clock split :TDTS = Tck_tim
	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = 1; 
	//Up counting mode 
	//向上计数模式  
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//Initializes the timebase unit for TIMX based on the parameter specified in TIM_TIMEBASEINITSTRUCT
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 

  //Select Timer mode :TIM Pulse Width Modulation mode 1
  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	//Compare output enablement
	//比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  //Output polarity :TIM output polarity is higher	
  //输出极性:TIM输出比较极性高	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     
	TIM_OCInitStructure.TIM_Pulse = 2000;
	//TIM_OCInitStructure.TIM_Pulse = 500;
	//TIM_OCInitStructure.TIM_Pulse = 8000;
	//Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); 
	
	// Advanced timer output must be enabled
	//高级定时器输出必须使能这句		
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
	//CH1 is pre-loaded and enabled
	//CH1预装载使能	 
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  

  // Enable the TIMX preloaded register on the ARR
  //使能TIMx在ARR上的预装载寄存器	
	TIM_ARRPreloadConfig(TIM8, ENABLE); 
	
	//Enable TIM8
	//使能TIM8
	TIM_Cmd(TIM8, ENABLE);  

}
