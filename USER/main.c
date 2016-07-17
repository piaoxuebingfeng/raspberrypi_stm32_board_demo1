#include "stm32f10x.h"
#include "delay.h"
#include "rtc.h"
#include "usart.h"
#include "sys.h"

void GPIO_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
}
void LED_test(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	delay_ms(200);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	delay_ms(200);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	delay_ms(200);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	delay_ms(200);
}
int main(void)
{	
	u8 t;
	NVIC_Configuration();	 
	GPIO_init();
	delay_init();
	uart_init(9600);	 	//串口初始化为9600
	while(RTC_Init())		//RTC初始化	，一定要初始化成功
	{ 
		printf("RTC ERROR! \r\n");
		delay_ms(800);
		printf("RTC Trying...\r\n");
	}
	LED_test();
	while(1)
	{								    
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			printf("%d year %d month %d date\r\n",calendar.w_year,calendar.w_month,calendar.w_date);
			switch(calendar.week)
			{
				case 0:
					printf("Sunday\r\n");
					break;
				case 1:
					printf("Monday\r\n");
					break;
				case 2:
					printf("Tuesday\r\n");
					break;
				case 3:
					printf("Wednesday\r\n");
					break;
				case 4:
					printf("Thursday\r\n");
					break;
				case 5:
					printf("Friday\r\n");
					break;
				case 6:
					printf("Saturday\r\n");
					break;  
			}
			printf("%d hour %d min %d sec\r\n",calendar.hour,calendar.min,calendar.sec);
		}	
		delay_ms(10);								  
	} 
}

