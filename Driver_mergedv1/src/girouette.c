#include "girouette.h"
#include "Driver_GPIO.h"
#include "Driver_Timer.h"
#include "servo.h"
#include <stdio.h>

float angle;
int test=0;

void GirouetteInit(void){
	// SET GPIO
	MyGPIO_Init(GPIOA, 0, In_Floating);
	MyGPIO_Init(GPIOA, 1, In_Floating);
	
	// TIM
	MyTimer_Base_Init(TIM2, 1440,0);
	TIM2->SMCR &= ~(0x7); //SMS
	TIM2->SMCR |= (0x3);
	TIM2->CR1 |= (0x1); //CEN
	TIM2->CCR1 &= ~(0x3); //CC1S
	TIM2->CCR1 |= (0x1); 
	TIM2->CCR1 &= ~((0x3)<<8); //CC2S
	TIM2->CCR1 |= ((0x1)<<8);
	TIM2->CCR1 &= ~((0xF)<<4); //IC1F
	TIM2->CCR1 &= ~((0xF)<<12); //IC2F
	TIM2->CCER &= ~(0x1<<1); //CC1P
	TIM2->CCER &= ~(0x1<<5); //CC2P
	TIM2->CCER &= ~(0x1<<3); //CC1NP
	TIM2->CCER &= ~(0x1<<7); //CC2NP
	
	// Extern interrup
  MyGPIO_ExtI();
}

void EXTI0_IRQHandler ( void ) {
	test++;
	EXTI->PR |= 0x1;
	TIM2->CNT = 720;
	servoInit();
}

float GirouetteAngle(void){
	angle = ((TIM2->CNT / 4.0)-180)*-1;
	return angle;
}

