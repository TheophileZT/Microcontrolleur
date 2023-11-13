#include "Driver_Timer.h"
#include "Driver_GPIO.h"

// Fonctions de callback
void (*TIM1_IT_Funct)(void);
void (*TIM2_IT_Funct)(void);
void (*TIM3_IT_Funct)(void);
void (*TIM4_IT_Funct)(void);


void MyTimer_Base_Init ( TIM_TypeDef * Timer, uint16_t arr, uint16_t psc) {
	if (Timer==TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Active l�horloge du Timer 2
	} else if (Timer==TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //Active l�horloge du Timer 3
	} else if (Timer==TIM4) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Active l�horloge du Timer 4
	} else if (Timer==TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //Active l�horloge du Timer 1
	}
	Timer->ARR=arr; //Valeur d'auto-reload
	Timer->PSC=psc; //Valeur de prescaler
}

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (*IT_Funct)(void) ){
	Timer->DIER |= 0x1; //Active l'interruption
	Timer->SR &= ~(0x1); //Reset le flag d'interruption
	if (Timer==TIM2){
		NVIC->ISER[0]|=(0x1)<<28; //Active l'interruption dans le NVIC
		NVIC->IP[28]=Prio<<4; //D�finit la priorit�
		TIM2_IT_Funct=(*IT_Funct); //D�finit la fonction de callback
	} else if (Timer==TIM3) {
		NVIC->ISER[0]|=(0x1)<<29;
		NVIC->IP[29]=Prio<<4;
		TIM3_IT_Funct=(*IT_Funct);
	} else if (Timer==TIM4) {
		NVIC->ISER[0]|=(0x1)<<30;
		NVIC->IP[30]=Prio<<4;
		TIM4_IT_Funct=(*IT_Funct);
	} else if (Timer==TIM1){
		NVIC->ISER[0]|=(0x1)<<25;
		NVIC->IP[25]=Prio<<4;
		TIM1_IT_Funct=(*IT_Funct);
	}
}


void TIM1_IRQHandler ( void ){
	TIM1->SR &= ~(0x1); //Reset le flag d'interruption
	(*TIM1_IT_Funct)(); //Appelle la fonction de callback
}

void TIM2_IRQHandler ( void ){
	TIM2->SR &= ~(0x1);
	(*TIM2_IT_Funct)();
	
}

void TIM3_IRQHandler ( void ){
	TIM3->SR &= ~(0x1);
	(*TIM3_IT_Funct)();
}

void TIM4_IRQHandler ( void ){
	TIM4->SR &= ~(0x1);
	(*TIM4_IT_Funct)();
}

/**
* @brief
* @param ....
* @Note Active le channel sp�cifi� sur Timer le timer sp�cifi�
* la gestion de la configuration I/O n�est pas faite dans cette fonction
* ni le r�glage de la p�riode de la PWM (ARR, PSC)
*/

void MyTimer_PWM( TIM_TypeDef * Timer, char Channel){
	if (Timer == TIM1){
		TIM1 -> BDTR = (0x1 << 15); //MOE � 1 pour le timer1 
	}
	if (Channel == 1){
		if (Timer==TIM1){
			MyGPIO_Init (GPIOA, 8, AltOut_Ppull);
		}
		if (Timer==TIM2){
			MyGPIO_Init (GPIOA, 0, AltOut_Ppull);
		}
		if (Timer==TIM3){
			MyGPIO_Init (GPIOA, 6, AltOut_Ppull);
		}
		if (Timer==TIM4){
			MyGPIO_Init (GPIOB, 6, AltOut_Ppull);
		}
		Timer -> CCMR1 &= ~(0x7 << 4);
		Timer -> CCMR1 |= (0x6 << 4); //mise en PWM mode 1
		Timer -> CCER &= ~(0x1); //d�sactive CC1 le temps de l'initialisation
		Timer -> CCMR1 &= ~(0x3); // channel 1 en output
		Timer -> CCER |= (0x1); // r�active CC1
	}
	else if (Channel == 2){
		if (Timer==TIM1){
			MyGPIO_Init (GPIOA, 9, AltOut_Ppull);
		}
		if (Timer==TIM2){
			MyGPIO_Init (GPIOA, 1, AltOut_Ppull);
		}
		if (Timer==TIM3){
			MyGPIO_Init (GPIOA, 7, AltOut_Ppull);
		}
		if (Timer==TIM4){
			MyGPIO_Init (GPIOB, 7, AltOut_Ppull);
		}
		Timer -> CCMR1 &= ~(0x7 << 12);
		Timer -> CCMR1 |= (0x6 << 12); //mise en PWM mode 1
		Timer -> CCER &= ~(0x1 << 4); //d�sactive CC2 le temps de l'initialisation
		Timer -> CCMR1 &= ~(0x3 << 8); // channel 2 en output
		Timer -> CCER |= (0x1 << 4); // r�active CC2
	}
	else if (Channel == 3){
		if (Timer==TIM1){
			MyGPIO_Init (GPIOA, 10, AltOut_Ppull);
		}
		if (Timer==TIM2){
			MyGPIO_Init (GPIOA, 2, AltOut_Ppull);
		}
		if (Timer==TIM3){
			MyGPIO_Init (GPIOB, 0, AltOut_Ppull);
		}
		if (Timer==TIM4){
			MyGPIO_Init (GPIOB, 8, AltOut_Ppull);
		}
		Timer -> CCMR2 &= ~(0x7 << 4);
		Timer -> CCMR2 |= (0x6 << 4); //mise en PWM mode 1
		Timer -> CCER &= ~(0x1 << 8); //d�sactive CC3 le temps de l'initialisation
		Timer -> CCMR2 &= ~(0x3); // channel 3 en output
		Timer -> CCER |= (0x1 << 8); // r�active CC3
	}
	else if (Channel == 4){
		if (Timer==TIM1){
			MyGPIO_Init (GPIOA, 11, AltOut_Ppull);
		}
		if (Timer==TIM2){
			MyGPIO_Init (GPIOA, 3, AltOut_Ppull);
		}
		if (Timer==TIM3){
			MyGPIO_Init (GPIOB, 1, AltOut_Ppull);
		}
		if (Timer==TIM4){
			MyGPIO_Init (GPIOB, 9, AltOut_Ppull);
		}
		Timer -> CCMR2 &= ~(0x7 << 12);
		Timer -> CCMR2 |= (0x6 << 12); //mise en PWM mode 1
		Timer -> CCER &= ~(0x1 << 12); //d�sactive CC4 le temps de l'initialisation
		Timer -> CCMR2 &= ~(0x3 << 8); // channel 4 en output
		Timer -> CCER |= (0x1 << 12); // r�active CC4
	}
}

void MyTimer_PWM_SetDutyCycle(TIM_TypeDef * Timer, char Channel, float DutyCycle) {
	if (Channel == 1) {
		Timer->CCR1 = (uint16_t) (Timer->ARR * DutyCycle); //D�finit le duty cycle
	} else if (Channel == 2) {
		Timer->CCR2 = (uint16_t) (Timer->ARR * DutyCycle);
	} else if (Channel == 3) {
		Timer->CCR3 = (uint16_t) (Timer->ARR * DutyCycle);
	} else if (Channel == 4) {
		Timer->CCR4 = (uint16_t) (Timer->ARR * DutyCycle);
	}
}
