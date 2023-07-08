#include "Servo.h"
void TIM1_Servo_Init()
{
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //ʹ�ܶ�ʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);  //ʹ��A B��
 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);   //����ΪTIM2 �������ӿ�
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //PE8
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);  
	
	
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 1680-1; 							// No prescaling     //����Ƶ
  TIM_TimeBaseStructure.TIM_Period = 2000-1;  //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���    
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  //��ʼ����ʱ��
  

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 0 ;
	
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  		
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  	

				

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);

  
	  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	  TIM_SetCounter(TIM1,0);
	  TIM_Cmd(TIM1, ENABLE);     

	  TIM_CtrlPWMOutputs(TIM1,ENABLE);			
  
}  

void 	TIM5_Servo_Init(){

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��PA�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//�˿�����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //�����趨������ʼ��GPIOA

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //����ΪTIM5 �������ӿ�
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //����ΪTIM5 �������ӿ�
  

  TIM_TimeBaseStructure.TIM_Prescaler = 840-1; // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 2000-1; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM���ϼ���  
  
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 		
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;							
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		
	
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  				
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);  	

	TIM_CtrlPWMOutputs(TIM5,ENABLE);							

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable); 
	
	TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPE??
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
  
	TIM_SetCounter(TIM5,0);
	TIM_Cmd(TIM5, ENABLE); 

}

