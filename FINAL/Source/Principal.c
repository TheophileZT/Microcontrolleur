#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "servo.h"
#include "girouette.h"
#include <stdlib.h>
#include <stdio.h> 


char * ptr = "Bonjour";
signed char vitesse ;
float rapport = 0.0;

void IT_Func (void) {
	vitesse = (signed char)USART3 -> DR ;//lit ce qui est recu par l'usart2 et le converti en signed char (suffisant car valeur entre -100 et 100)
	rapport = (vitesse)/100.0;
	if (vitesse < 0){
		MyGPIO_Set(GPIOA, 4);//bit de sens à 1 pour indiquer le sens de rotation
		MyTimer_PWM_SetDutyCycle(TIM4, 1, rapport);
	}
	else{
		MyGPIO_Reset(GPIOA, 4);
		MyTimer_PWM_SetDutyCycle(TIM4, 1, rapport);
	}
}

int main (void){
	
	GirouetteInit();
	
	MyUSART_ActiveIT(USART3, 10, IT_Func);
	MyUSART_Reception_Init(USART3);//B11
	MyUSART_Transmission_Init(USART3);//B10
	
	MyGPIO_Init(GPIOA, 4, Out_Ppull);//PLATEAU_DIRECTION PA4 -> 20e pin
	
	MyTimer_Base_Init(TIM4, 1799, 1);//pour un signal de la PWM de fréquence 20 kHz
	MyTimer_Base_Start(TIM4);
	MyTimer_PWM(TIM4, 1);//TIM4_CH1 connecté à la pin PB6 -> PLATEAU_PWM*/
	
	MyUSART_Send(USART3, ptr);
	
	do {
		bordage();
	} while(1);
}
