#include "MQTT.h"
#include "MQTT_Table.h"
#include "OLED_SPI.h"

extern unsigned char Connect_Data[114];
extern unsigned char Subscribe_reply[61];
extern unsigned char Subscribe_set[56];
extern unsigned char Post_Value[193];

void WiFi_Init(int k)
{
				int i= 0;
				delay_init(168);
	
				for(i = 0; i<=10 ; i++)
				{
					send_String("+++");
					delay_ms(10);
				}
	
				send_String("AT\r\n");
	
				delay_ms(1);
				send_String("AT+CWMODE=1\r\n");
				delay_ms(1);

				send_String("AT+RST\r\n");
//				delay_ms(500);
				vTaskDelay(500);
	
//				send_String("AT+CWJAP=\"Redmi-1201\",\"13975154788\"\r\n");
				send_String("AT+CWJAP=\"Redmi K4000\",\"a7777777\"\r\n");
//				delay_ms(8000);
				vTaskDelay(8000);
	
				send_String("AT+CWAUTOCONN=0\r\n");
				delay_ms(1);
	
				send_String("AT+CIPMUX=0\r\n");
				delay_ms(1);
	
				send_String("AT+CIPMODE=1\r\n");
				delay_ms(1);
				
				if(k==1)
					send_String("AT+CIPSTART=\"TCP\",\"D0001.iot-as-mqtt.cn-D0001.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n");
//				send_String("AT+CIPSTART=\"TCP\",\"192.168.31.136\",8082\r\n");
				else 
					send_String("AT+CIPSTART=\"TCP\",\"www.ouriot.vip\",1883\r\n");
//				delay_ms(1200);
				vTaskDelay(1200);
			
				send_String("AT+CIPSEND\r\n");
				delay_ms(50);
}


void Connect_MQTT_Service()
{
		int i = 0 ;
		for(i = 0 ; i<114 ; i++)
		{
			send_Data(Connect_Data[i]);
		}
		//send_String();
		//delay_ms(500);
		vTaskDelay(500);
		
}

void Keep_live(){
	send_Data(0xc0);
	send_Data(0x00);
}

void Connect_MQTT_Serive_New(char * s)
{
		char length = 0;
		char buf[200] ;
		strcat(buf,s);
		length = strlen(buf);
		send_Data(0x82);
	
		send_Data(length+0x05);
	
		send_Data(0x00);
		send_Data(0x0a);
	
		send_Data(0x00);
	
		send_Data(length);
		send_String(buf);
		send_Data(0x00);
	
//		delay_ms(500);
		vTaskDelay(500);
}


void Subscribe_Set()
{
		int i = 0 ;
		for(i = 0 ; i<56 ; i++)
		{
			send_Data(Subscribe_set[i]);
		}
		//send_String();
//		delay_ms(500);
		vTaskDelay(300);
}

void Subscribe_replay()
{
		int i = 0 ;
		for(i = 0 ; i<61 ; i++)
		{
			send_Data(Subscribe_reply[i]);
		}
		//send_String();
//		delay_ms(500);
		vTaskDelay(300);
}

void Post_ToAliyun()
{
		int i = 0 ;
		for(i = 0 ; i<193 ; i++)
		{
			send_Data(Post_Value[i]);
		}
//		send_String();
//		delay_ms(500);
		vTaskDelay(300);
}

char * Test(char* s )
{
	return s;
}

void ssss()
{
	int size ;
	char *s;
	s = Test("ATT");
	size = sizeof(s);
	send_String(s);
	USART_SendData(USART2,size);
}



void Send_Data_TO_AliYun(char * ss)
{
//	 char Start [10] ={0};
	 unsigned int  i =0;  
	 char length[4]={0};
	 char toWhere[] = "/sys/hlhm4Qhn28O/D0001/thing/event/property/post";
	 char temp [200]="{\"id\":35399323,\"version\":\"1.0\",\"params\":{";
		
		i = strlen(toWhere);
		
		strcat(temp,ss);		
		strcat(temp,"},\"method\":\"thing.event.property.post\"}");
	 
		length[1] = i;
		
		i += strlen(temp);
		
		length[2]= i%128+0x80;
		length[3] = i/128;
		
		send_Data(0x30);
	 	send_Data(length[2]+0x02);
		send_Data(length[3]);
		send_Data(length[0]);
		send_Data(length[1]);
	 	send_String(toWhere);
	    send_String(temp);	 
}


void Send_Data_TO_AliYun_Test(char * ss)
{
//	 char Start [10] ={0};
	 unsigned int  i =0;  
	 char length[4]={0};
	 char toWhere[] = "/hlhm4Qhn28O/D0001/user/Test";
	 char temp [200]="{\"id\":3566666,\"version\":\"1.0\",\"params\":{";
		
		i = strlen(toWhere);
		
		strcat(temp,ss);		
		strcat(temp,"},\"method\":\"thing.event.property.post\"}");
	 
		length[1] = i;
		
		i += strlen(temp);
		
		length[2]= i%128+0x80;
		length[3] = i/128;
		
		send_Data(0x30);
	 	send_Data(length[2]+0x02);
		send_Data(length[3]);
		send_Data(length[0]);
		send_Data(length[1]);
	 	send_String(toWhere);
	    send_String(temp);	 
}


void Connect_EMQX( char *ID ,  char *user ,  char *sec){
	int i = 0;

	char length[5];
	
	unsigned char  kebian[10]={0x00,0x04,0x4d,0x51,0x54,0x54,0x04,0xc2,0x00,0x64};
	
	length[1] = strlen(ID);
	length[2] = strlen(user);
	length[3] = strlen(sec);
	
	
	length[4] = length[1]+length[2]+length[3]+0x0a;
	
	send_Data(0x10);
	
	send_Data(length[4]+0x06);
	
	for(i = 0 ; i<10 ; i++)
	{
		send_Data(kebian[i]);
	}
	

	send_Data(0x00);
	send_Data(length[1]);
	send_String(ID);
	
	send_Data(0x00);
	send_Data(length[2]);
	send_String(user);
	
	send_Data(0x00);
	send_Data(length[3]);
	send_String(sec);
}


void EMQX_SubscribeMessage(char *  New){
	
	char length ;
	
	length = strlen(New);
	
	send_Data(0x82);
	send_Data(length+0x05);
	
	send_Data(0x00);
	send_Data(0x0a);
	
	send_Data(0x00);
	send_Data(length);
	send_String(New);
	send_Data(0x00);

}


void Send_Data_TO_EMQX(char * topic  ,char *msg)
{
//	 char Start [10] ={0};
	 unsigned int  i =0;  
	 char length[4]={0};

	 char temp [200]="{\"Device\":\"Car\",\"params\":{";
		
		i = strlen(topic);
		
		strcat(temp,msg);		
		strcat(temp,"}}");
	 
		length[1] = i;
		
		i += strlen(temp);
		
		length[2]= i%128+0x80;
		length[3] = i/128;
		
		send_Data(0x30);
	 	send_Data(length[2]+0x02);
		send_Data(length[3]);
		send_Data(length[0]);
		send_Data(length[1]);
	 	send_String(topic);
	    send_String(temp);	 
}

