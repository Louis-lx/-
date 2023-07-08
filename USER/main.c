#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "usart4.h"
#include "FreeRTOS.h"
#include "task.h"
#include "motor.h"
#include "pwm.h"
#include "encoder.h"
#include "UART.h"
#include "MQTT.h"
#include "SPI.h"
#include "OLED_SPI.h"
#include "semphr.h"
#include "DHT11.h"
#include "UART5.h"
#include "xunji.h"
#include "Servo.h"
#include "wit_c_sdk.h"

/*
		A   右后
		
		B	 左后
		
		C   左前
		
		D	 右前
		

*/

void start_task(void *pvParameters);
void move_task(void *pvParameters);
void oled_task(void *pvParameters);
void KeepLive_task(void* pvParameters);
void SPI_Task(void *pvParameters);
void WiFi_Task(void *pvParameters);
void OLED_Task(void *pvParameters);
void DHT11_Task(void* pvParameters);
void Get_InstructionsFormEMQX_Task(void * pvParameters);
unsigned int StringToDEC(unsigned char* rdata,unsigned char len);

TaskHandle_t MpuTask_Handler;
TaskHandle_t KeepLive_task_Handler ;
TaskHandle_t SPI_Task_Handler ;
TaskHandle_t WiFi_Task_Handler ;
TaskHandle_t OLED_Task_Handler ;
TaskHandle_t DHT11_Task_Handler ;
TaskHandle_t Get_InstructionsFormEMQX_Task_Handler ;

SemaphoreHandle_t WiFi_Semaphore;
SemaphoreHandle_t OLED_Semaphore;

char data[60] ;

u8 Res;
	
u8 USART_RX_BUFF[USART_REC_LEN];

u16 USART_RX_STAA=0;

u8 UART5_BUFF[20] ;

float Now_Yaw ;

int temoooo;


 u16 xunji[2];

char len = 0;
unsigned int  Tof250_dist ;
	
#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
const uint32_t c_uiBaud[10] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
static void CmdProcess(void);
static void AutoScanSensor(void);
static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
static void Delayms(uint16_t ucMs);


float fAcc[3], fGyro[3], fAngle[3];


int k = 0;
char ss[2];

unsigned char buf;

float to_Yaw = 0;
extern unsigned char Dataa[6];




int main(void)
{ 
	unsigned char dataa[] = {0xff,0xaa,0x27,0x3f,0x00};
	int i;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);  //初始化延时函数
//	delay_ms(2000);

	OLED_SPI_Init();
	sprintf((char *)data,"The time is  ");
	OLED_P6x8Str(0,2,data);
	
	MOTOR_GPIO_Init();
	MOTOR_PWM_Init(1000-1,1680-1);
	uart4_init(115200);
	uart_init(9600);
///	TIM2_PWM_Init(200-1,8400-1);
	UART2_Init();
	
//		send_Data(0xff);
//		send_Data(0xaa);
//		send_Data(0x27);
//		send_Data(0x3f);
//		send_Data(0x00);
//		
//		
//		temoooo = Dataa[5]<<8|Dataa[4];
//		Now_Yaw = 1.0*temoooo/32768*180;
//		temoooo = 0 ;
//	
//		sprintf(data,"Now_Yaw = %0.2f",Now_Yaw);
//		OLED_P6x8Str(0,3,data);


//	TIM1_Encoder_Init();

	TIM4_Encoder_Init();
	TIM2_Encoder_Init();
	TIM3_Encoder_Init();
	TIM5_Encoder_Init();
	
//	TIM1_Servo_Init();
//	TIM5_Servo_Init();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	
//	UART5_Init(9600);
	
//	TIM_SetCompare1(TIM5,80);/*爪子     55关	80开*/
//	TIM_SetCompare2(TIM5,50);	/*右 120 抬起来     140*/
//	
//	TIM_SetCompare1(TIM1,200);

//		Uart2Sendd(dataa,5);
		
//		send_Data(0xffaa273f00);

	

//		send_Data(0xff);
//		send_Data(0xaa);
//		send_Data(0x27);
//		send_Data(0x3f);
//		send_Data(0x00);
//		
//		
//		temoooo = Dataa[5]<<8|Dataa[4];
//		Now_Yaw = 1.0*temoooo/32768*180;
//		temoooo = 0 ;
//	
//		sprintf(data,"Now_Yaw = %0.2f",Now_Yaw);
//		OLED_P6x8Str(0,3,data);

		delay_ms(100);
		
		TIM6_INT_Init();
	   
	 
//	xTaskCreate((TaskFunction_t )WiFi_Task,            //任务函数
//                (const char*    )"WiFi_Task",          //任务名称
//                (uint16_t       )256,        //任务堆栈大小
//                (void*          )NULL,                  //传递给任务函数的参数
//                (UBaseType_t    )8,       //任务优先级
//                (TaskHandle_t*  )&WiFi_Task_Handler);   //任务句柄    
		
				
//	xTaskCreate((TaskFunction_t )OLED_Task,            //任务函数
//                (const char*    )"OLED_Task",          //任务名称
//                (uint16_t       )512,        //任务堆栈大小
//                (void*          )NULL,                  //传递给任务函数的参数
//                (UBaseType_t    )10,       //任务优先级
//                (TaskHandle_t*  )&OLED_Task_Handler);   //任务句柄    
		
				
//	xTaskCreate((TaskFunction_t )KeepLive_task,            //任务函数
//			(const char*    )"KeepLive_task",          //任务名称
//			(uint16_t       )128,        //任务堆栈大小
//			(void*          )NULL,                  //传递给任务函数的参数
//			(UBaseType_t    )14,       //任务优先级
//			(TaskHandle_t*  )&KeepLive_task_Handler);   //任务句柄    
//	
//	xTaskCreate((TaskFunction_t )DHT11_Task,            //任务函数
//			(const char*    )"DHT11_Task",          //任务名称
//			(uint16_t       )256,        //任务堆栈大小
//			(void*          )NULL,                  //传递给任务函数的参数
//			(UBaseType_t    )11,       //任务优先级
//			(TaskHandle_t*  )&DHT11_Task_Handler);   //任务句柄   
				
//		xTaskCreate((TaskFunction_t )Get_InstructionsFormEMQX_Task,            //任务函数
//                (const char*    )"Get_InstructionsFormEMQX_Task",          //任务名称
//                (uint16_t       )256,        //任务堆栈大小
//                (void*          )NULL,                  //传递给任务函数的参数
//                (UBaseType_t    )13,       //任务优先级
//                (TaskHandle_t*  )&Get_InstructionsFormEMQX_Task_Handler);   //任务句柄   

//		xTaskCreate((TaskFunction_t )SPI_Task,            //任务函数
//                (const char*    )"SPI_Task",          //任务名称
//                (uint16_t       )128,        //任务堆栈大小
//                (void*          )NULL,                  //传递给任务函数的参数
//                (UBaseType_t    )10,       //任务优先级
//                (TaskHandle_t*  )&SPI_Task_Handler);   //任务句柄    
		

//    xTaskCreate((TaskFunction_t )start_task,            //任务函数
//                (const char*    )"start_task",          //任务名称
//                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
//                (void*          )NULL,                  //传递给任务函数的参数
//                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
//                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              

//    vTaskStartScheduler();          //开启任务调度
	
	
	
	 	while(1)
	{                            
//		send_Data(0xff);
//		send_Data(0xaa);
//		send_Data(0x27);
//		send_Data(0x3f);
//		send_Data(0x00);		
//		delay_ms(500);
		
//			Keep_live();
		
		
		
//			track_PID(120.0,0.3);
		
			

		

//		
//		 if(USART_RX_STAA&0x8000)
//        {
//            len=USART_RX_STAA&0x3fff;              
//			Tof250_dist = StringToDEC(&USART_RX_BUFF[0],len); 
////			printf("%u cm\n",Tof250_dist);        
//			sprintf(data,"tof:%u       ",Tof250_dist);
//			OLED_P6x8Str(0,3,data);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
//            USART_RX_STAA=0;                     
//			send_String("HelloWorld");
//		}	
//		
////		sprintf(data,"angleX:%f   ",fAngle[0]);
////		OLED_P6x8Str(0,4,(unsigned char *)data);
////		sprintf(data,"3angleY:%f   ",fAngle[1]);
////		OLED_P6x8Str(0,5,(unsigned char *)data);
////		sprintf(data,"angleZ:%f   ",fAngle[2]);
////		OLED_P6x8Str(0,6,(unsigned char *)data);
//		
////		sprintf(data,"PID_angleZ:%f   ",ForWardUsingWit(0));
////		OLED_P6x8Str(0,7,(unsigned char *)data);
//		to_Yaw = ForWardUsingWit(0);
//		sprintf(data,"PID_angleZ:%0.1f   ",to_Yaw);
//		OLED_P6x8Str(0,7,(unsigned char *)data);
//		delay_ms(15);
//		
////		usart4_send('2');
////		LED0 = 1;
////		LED1 = 0;
//		//usart4_send(6);
//		//delay_ms(1000);
		
	}
		//创建开始任务
//    xTaskCreate((TaskFunction_t )start_task,            //任务函数
//                (const char*    )"start_task",          //任务名称
//                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
//                (void*          )NULL,                  //传递给任务函数的参数
//                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
//                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
//    vTaskStartScheduler();          //开启任务调度

}


void KeepLive_task(void* pvParameters){
		
		int k = 1;
		char msg [20]; 

		while(1){
			if(xSemaphoreTake(WiFi_Semaphore,100)==pdTRUE){			
				Keep_live();
				xSemaphoreGive(WiFi_Semaphore);
				
				sprintf((char *)msg,"KeepLive     %d   ",k);
				OLED_P6x8Str(0,3,(unsigned char *)msg);
				k++;
				
//				tem = USART_ReceiveData(UART4);

//				sprintf(sss,"%dss",tem);
//				OLED_P6x8Str(0,5,sss);
		//position_out = Position_PD_ABCD(adc_data,0);
		
				vTaskDelay(5000);
			}else{
				vTaskDelay(1000);
			}
		}
}


void WiFi_Task(void *pvParameters){
	
	xSemaphoreTake(WiFi_Semaphore,100);
	while(1){
		WiFi_Init(2);
		//Connect_MQTT_Service();
		Connect_EMQX("Car","WoShiOP","123456");
		vTaskDelay(500);
		//EMQX_SubscribeMessage("ouriot/kongwenxin/Car");
		//Connect_MQTT_Serive_New("/hlhm4Qhn28O/D0001/user/Test");
		xSemaphoreGive(WiFi_Semaphore);
		vTaskDelete(NULL);
	}
}


void USART2_IRQHandler(void)
{
	unsigned char ucTemp;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		ucTemp = USART_ReceiveData(USART2);
		My_WitSerialDataIn(ucTemp);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}


void Uart2Send(unsigned char *p_data, unsigned int uiSize)
{	
	unsigned int i;
	for(i = 0; i < uiSize; i++)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART2, *p_data++);		
	}
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}


void SPI_Task(void* pvParameters){
		int i = 0 ;
		while(1){
			My_SPI_WriteData(i,0);
			i++;
			vTaskDelay(500);
		}
}


//void OLED_Task(void * pvParameters){
//	int k = 0;
//	 unsigned char msg[40];

//	xSemaphoreTake(OLED_Semaphore,100);
//	OLED_SPI_Init();
//	DHT11_Init();
//	xSemaphoreGive(OLED_Semaphore);
//	while(1){
//		sprintf((char *)msg,"The time is  %d    %d",k,Res);
////		OLED_Fill(0x00);
//		OLED_P6x8Str(0,2,msg);
//		k++;
//		vTaskDelay(1000);
//	}
//}


void DHT11_Task(void* pvParameters){
	unsigned  char temp;
	unsigned  char humi ;
	unsigned char data []= {"ssC  ss%"};
	char msg[90];
	while(1){
		if(xSemaphoreTake(OLED_Semaphore,100)==pdTRUE){
			DHT11_Read_Data(&temp,&humi);
			data[0] = temp/10+0x30;
			data[1] = temp%10+0x30;
			data[5] = humi/10+0x30;
			data[6] = humi%10+0x30;
			OLED_P6x8Str(0,5,data);
			sprintf(msg,"\"CurrentHumidity\":%d,\"CurrentTemperature\":%d,\"PowerSwitch\":1",humi,temp);
//			Send_Data_TO_AliYun(msg);
			Send_Data_TO_EMQX("ouriot/kongwenxin/Car",msg);
			xSemaphoreGive(OLED_Semaphore);
			vTaskDelay(5000);
		}else{
			vTaskDelay(1000);
		}
	}
}


void Get_InstructionsFormEMQX_Task(void * pvParameters){
	
	char msgg [40];

	while(1){
		//UART5_send(UART5_BUFF);
		
		if(xSemaphoreTake(OLED_Semaphore,100)==pdTRUE){		
			UART5_Init(9600);
			while(1){
					if(USART_RX_STAA&0x8000)
					{
						len=USART_RX_STAA&0x3fff;          
						Tof250_dist = StringToDEC(&USART_RX_BUFF[0],len+1);
						sprintf(msgg,"%u cm      ",Tof250_dist);         
						OLED_P6x8Str(0,7,(unsigned char *)msgg);
						USART_RX_STAA=0;                
					}
	//			Tof250_dist=StringToDEC(USART_RX_BUF,USART_RX_STAA&0X3FFF);
	//			sprintf(msg,"%d %d %d %d %d %d %d",USART_RX_BUFF[0],USART_RX_BUFF[1],USART_RX_BUFF[2],USART_RX_BUFF[3],USART_RX_BUFF[4],USART_RX_BUFF[5],USART_RX_STAA&0X3FFF);
	//			sprintf(msg,"%d",Tof250_dist);
	//			OLED_P6x8Str(0,6,(unsigned char *)msg);
	//			USART_RX_STAA = 0;
					xSemaphoreGive(OLED_Semaphore);
					vTaskDelay(500);
				}
		}else{
		vTaskDelay(500);
		}
	}
}

//开始任务任务函数
//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();           //进入临界区
//    //创建中断测试任务
//    xTaskCreate((TaskFunction_t )move_task,             
//                (const char*    )"move_task",           
//                (uint16_t       )MOVE_STK_SIZE,        
//                (void*          )NULL,                  
//                (UBaseType_t    )MOVE_TASK_PRIO,        
//                (TaskHandle_t*  )&MoveTask_Handler); 
//								
//		xTaskCreate((TaskFunction_t )oled_task,             
//                (const char*    )"oled_task",           
//                (uint16_t       )OLED_STK_SIZE,        
//                (void*          )NULL,                  
//                (UBaseType_t    )OLED_TASK_PRIO,        
//                (TaskHandle_t*  )&OledTask_Handler); 
//	vTaskDelete(StartTask_Handler); //删除开始任务
//    taskEXIT_CRITICAL();            //退出临界区
//}

//void move_task(void *pvParameters)
//{
//	
//	while(1){

//	}

//}

//void oled_task(void *pvParameters)
//{
//	
//	while(1){
//	//Movecar(-100);
//		//track_show();
//		//MPU_show();
//		
//	}

//}

//中断测试任务函数 
//void interrupt_task(void *pvParameters)
//{
//	static u32 total_num=0;
//    while(1)
//    {
//		total_num+=1;
//		if(total_num==5) 
//		{
//			printf("关闭中断.............\r\n");
//			portDISABLE_INTERRUPTS();				//关闭中断
//			delay_xms(5000);						//延时5s
//			printf("打开中断.............\r\n");	//打开中断
//			portENABLE_INTERRUPTS();
//		}
//        LED0=~LED0;
//        vTaskDelay(1000);
//    }
//}  


unsigned int StringToDEC(unsigned char* rdata,unsigned char len)
{
    unsigned char  i;
    unsigned int wdata = 0;
    unsigned char temp[4];

    for(i=0; i<len; i++)
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
    return wdata;
}



	
void UART5_IRQHandler(void){


	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) 
	{

		Res =USART_ReceiveData(UART5);
		if((USART_RX_STAA&0x8000)==0)
		{
			if(USART_RX_STAA&0x4000)
			{
				if(Res!=0x0a)USART_RX_STAA=0;
				else USART_RX_STAA|=0x8000;	
			}
			else
			{	
				if(Res==0x0d)USART_RX_STAA|=0x4000;
				else
				{
					USART_RX_BUFF[USART_RX_STAA&0X3FFF]=Res ;
					USART_RX_STAA++;
					if(USART_RX_STAA>(USART_REC_LEN-1))USART_RX_STAA=0;  
				}		 
			}
		}   		 
  } 

} 


void CopeCmdData(unsigned char ucData)
{
	static unsigned char s_ucData[50], s_ucRxCnt = 0;
	
	s_ucData[s_ucRxCnt++] = ucData;
	if(s_ucRxCnt<3)return;										//Less than three data returned
	if(s_ucRxCnt >= 50) s_ucRxCnt = 0;
	if(s_ucRxCnt >= 3)
	{
		if((s_ucData[1] == '\r') && (s_ucData[2] == '\n'))
		{
			s_cCmd = s_ucData[0];
			memset(s_ucData,0,50);//
			s_ucRxCnt = 0;
		}
		else 
		{
			s_ucData[0] = s_ucData[1];
			s_ucData[1] = s_ucData[2];
			s_ucRxCnt = 2;
			
		}
	}

}
static void ShowHelp(void)
{
	printf("\r\n************************	 WIT_SDK_DEMO	************************");
	printf("\r\n************************          HELP           ************************\r\n");
	printf("UART SEND:a\\r\\n   Acceleration calibration.\r\n");
	printf("UART SEND:m\\r\\n   Magnetic field calibration,After calibration send:   e\\r\\n   to indicate the end\r\n");
	printf("UART SEND:U\\r\\n   Bandwidth increase.\r\n");
	printf("UART SEND:u\\r\\n   Bandwidth reduction.\r\n");
	printf("UART SEND:B\\r\\n   Baud rate increased to 115200.\r\n");
	printf("UART SEND:b\\r\\n   Baud rate reduction to 9600.\r\n");
	printf("UART SEND:R\\r\\n   The return rate increases to 10Hz.\r\n");
	printf("UART SEND:r\\r\\n   The return rate reduction to 1Hz.\r\n");
	printf("UART SEND:C\\r\\n   Basic return content: acceleration, angular velocity, angle, magnetic field.\r\n");
	printf("UART SEND:c\\r\\n   Return content: acceleration.\r\n");
	printf("UART SEND:h\\r\\n   help.\r\n");
	printf("******************************************************************************\r\n");
}

static void CmdProcess(void)
{
	switch(s_cCmd)
	{
		case 'a':	
			if(WitStartAccCali() != WIT_HAL_OK) 
				printf("\r\nSet AccCali Error\r\n");
			break;
		case 'm':	
			if(WitStartMagCali() != WIT_HAL_OK) 
				printf("\r\nSet MagCali Error\r\n");
			break;
		case 'e':	
			if(WitStopMagCali() != WIT_HAL_OK)
				printf("\r\nSet MagCali Error\r\n");
			break;
		case 'u':	
			if(WitSetBandwidth(BANDWIDTH_5HZ) != WIT_HAL_OK) 
				printf("\r\nSet Bandwidth Error\r\n");
			break;
		case 'U':	
			if(WitSetBandwidth(BANDWIDTH_256HZ) != WIT_HAL_OK) 
				printf("\r\nSet Bandwidth Error\r\n");
			break;
		case 'B':	
			if(WitSetUartBaud(WIT_BAUD_115200) != WIT_HAL_OK) 
				printf("\r\nSet Baud Error\r\n");
			else 
				UART2_Init	();										
			break;
		case 'b':	
			if(WitSetUartBaud(WIT_BAUD_9600) != WIT_HAL_OK)
				printf("\r\nSet Baud Error\r\n");
			else 
				UART2_Init();												
			break;
		case 'R':	
			if(WitSetOutputRate(RRATE_10HZ) != WIT_HAL_OK) 
				printf("\r\nSet Rate Error\r\n");
			break;
		case 'r':	
			if(WitSetOutputRate(RRATE_1HZ) != WIT_HAL_OK) 
				printf("\r\nSet Rate Error\r\n");
			break;
		case 'C':	
			if(WitSetContent(RSW_ACC|RSW_GYRO|RSW_ANGLE|RSW_MAG) != WIT_HAL_OK) 
				printf("\r\nSet RSW Error\r\n");
			break;
		case 'c':	
			if(WitSetContent(RSW_ACC) != WIT_HAL_OK) 
				printf("\r\nSet RSW Error\r\n");
			break;
		case 'h':
			ShowHelp();
			break;
	}
	s_cCmd = 0xff;
}

static void SensorUartSend(uint8_t *p_data, uint32_t uiSize)
{
	Uart2Send(p_data, uiSize);
}

static void Delayms(uint16_t ucMs)
{
	delay_ms(ucMs);
}

static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
	int i;
    for(i = 0; i < uiRegNum; i++)
    {
        switch(uiReg)
        {
//            case AX:
//            case AY:
            case AZ:
				s_cDataUpdate |= ACC_UPDATE;
            break;
//            case GX:
//            case GY:
            case GZ:
				s_cDataUpdate |= GYRO_UPDATE;
            break;
//            case HX:
//            case HY:
            case HZ:
				s_cDataUpdate |= MAG_UPDATE;
            break;
//            case Roll:
//            case Pitch:
            case Yaw:
				s_cDataUpdate |= ANGLE_UPDATE;
            break;
            default:
				s_cDataUpdate |= READ_UPDATE;
			break;
        }
		uiReg++;
    }
}

static void AutoScanSensor(void)
{
	int i, iRetry;
	
	for(i = 1; i < 10; i++)
	{
		UART2_Init();
		iRetry = 2;
		do
		{
			s_cDataUpdate = 0;
			WitReadReg(AX, 3);
			delay_ms(100);
			if(s_cDataUpdate != 0)
			{
				printf("%d baud find sensor\r\n\r\n", c_uiBaud[i]);
				ShowHelp();
				return ;
			}
			iRetry--;
		}while(iRetry);		
	}
	printf("can not find sensor\r\n");
	printf("please check your connection\r\n");
}



