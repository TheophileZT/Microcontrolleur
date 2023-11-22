#include "stm32f10x.h"
#include "Driver_USART.h"

char * ptr = "Bonjour";
int main (void)
{
	MyUSART_Reception_Init(USART1);
	MyUSART_Transmission_Init(USART1, ptr);
	do {
	} while(1);
}
