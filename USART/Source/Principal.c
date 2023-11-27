#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_GPIO.h"

char * ptr = "Bonjour";
signed char vitesse ;
int main (void)
{
	//MyUSART_Reception_Init(USART2);
	//MyUSART_Transmission_Init(USART2);
	//MyUSART_Send(USART2, ptr);
	MyUSART_Reception_Init(USART2);
	MyUSART_Transmission_Init(USART2);
	
	vitesse = (signed char) MyGPIO_Read (GPIOA , 3);
	do {
	} while(1);
}
