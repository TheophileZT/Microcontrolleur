#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
//#include <unistd.h>
#include <stdlib.h>


char * ptr = "€";
signed char vitesse ;
int main (void)
{
	//MyUSART_Reception_Init(USART2);
  //MyUSART_Transmission_Init(USART2);
	//MyUSART_Send(USART2, ptr);
	float rapport = 0.0;
	MyUSART_Reception_Init(USART2);
	MyUSART_Transmission_Init(USART2);
	
	MyGPIO_Init(GPIOA, 4, Out_Ppull);//PLATEAU_DIRECTION PA4 -> 20e pin
	
	MyTimer_Base_Init(TIM2, 1799, 1);//pour un signal de la PWM de fréquence 20 kHz
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(TIM2, 1);//TIM2_CH1 connecté à la pin PA0
	do {
		//MyUSART_Send(USART2, ptr);
		vitesse = (signed char) MyGPIO_Read (GPIOA, 3); //lit ce qui est recu par l'usart2 et le converti en signed char (suffisant car valeur entre -100 et 100)
		rapport = abs(vitesse)/255;
	if (vitesse < 0){
		MyGPIO_Set(GPIOA, 4);//bit de sens à 1 pour indiquer le sens de rotation
		MyTimer_PWM_SetDutyCycle(TIM2, 1, rapport);
	}
	else{
		MyGPIO_Reset(GPIOA, 4);
		MyTimer_PWM_SetDutyCycle(TIM2, 1, rapport);
	}
	//usleep(31000);//sleep pendant 31 ms*/
	} while(1);
}
