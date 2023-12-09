#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include <stdlib.h>
#include <stdio.h> 


char * ptr = "B";
signed char vitesse ;
float rapport = 0.0;

void IT_Func (void) {
	vitesse = (signed char)USART3 -> DR ;//lit ce qui est recu par l'usart2 et le converti en signed char (suffisant car valeur entre -100 et 100)
	rapport = (vitesse)/100.0;
	if (vitesse < 0){
		MyGPIO_Set(GPIOA, 4);//bit de sens à 1 pour indiquer le sens de rotation
		MyTimer_PWM_SetDutyCycle(TIM2, 1, rapport);
	}
	else{
		MyGPIO_Reset(GPIOA, 4);
		MyTimer_PWM_SetDutyCycle(TIM2, 1, rapport);
	}
}

int main (void){
	
	MyUSART_Reception_Init(USART3);//B11
	MyUSART_Transmission_Init(USART3);//B10
	MyUSART_ActiveIT(USART3, 10, IT_Func);
	
	MyGPIO_Init(GPIOA, 4, Out_Ppull);//PLATEAU_DIRECTION PA4 -> 20e pin
	
	MyTimer_Base_Init(TIM2, 1799, 1);//pour un signal de la PWM de fréquence 20 kHz
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(TIM2, 1);//TIM2_CH1 connecté à la pin PA0 -> PLATEAU_PWM*/

	//TEST
	/*MyTimer_Base_Init(TIM2, 1799, 1);
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(TIM2, 1);//TIM2_CH1 connecté à la pin PA0 -> PLATEAU_PWM
	MyTimer_PWM_SetDutyCycle(TIM2, 1, 1);
	
	MyGPIO_Init(GPIOC, 3, Out_Ppull);//PLATEAU_DIRECTION PA4 -> 20e pin
	MyGPIO_Reset(GPIOC, 3);//bit de sens à 1 pour indiquer le sens de rotation
	MyUSART_Send(USART3, ptr);
	MyGPIO_Set(GPIOA, 4);
	MyTimer_PWM_SetDutyCycle(TIM2, 1, 1);*/
	
	MyUSART_Send(USART3, ptr);
	
	do {
		//MyUSART_Send(USART3,ptr);
	} while(1);
}
