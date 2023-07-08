#include "UART5.h"


void UART5_Init(int bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);	 //Enable the gpio clock  //使能GPIO时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); //Enable the Usart clock //使能USART时钟
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;           
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //高速50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //上拉
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);  		          //初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  //UsartNVIC configuration //UsartNVIC配置
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 5;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	//Enable the IRQ channel //IRQ通道使能	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initialize the VIC register with the specified parameters 
	//根据指定的参数初始化VIC寄存器		
	NVIC_Init(&NVIC_InitStructure);
	
  //USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound; //Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //一个停止
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //收发模式
    USART_Init(UART5, &USART_InitStructure);      //Initialize serial port 5 //初始化串口5
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(UART5, ENABLE);                  
}


	
//    if( USART_GetITStatus(UART4, USART_IT_IDLE ) != RESET )	//空闲中断: 接收到一帧数据产生一次中断
//    {
//		//读取DR寄存器 (先读USART_SR，然后读USART_DR即可清除空闲中断标志位IDLE)
//        tem = UART4->SR;  //读取SR寄存器
//        tem = UART4->DR;
//		U4_Data_Len = UART4_RX_STA;
//		UART4_RX_STA = 0;
//    }



void UART5_send(u8 data)
{
	UART5->DR = data;
	while((UART5->SR&0x40)==0);	
}

