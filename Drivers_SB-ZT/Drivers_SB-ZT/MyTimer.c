#include "MyTimer.h"

// Fonctions de callback
void (*TIM1_IT_Funct)(void);
void (*TIM2_IT_Funct)(void);
void (*TIM3_IT_Funct)(void);
void (*TIM4_IT_Funct)(void);


void MyTimer_Base_Init ( TIM_TypeDef * Timer, uint16_t arr, uint16_t psc) {
	if (Timer==TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Active l’horloge du Timer 2
	} else if (Timer==TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //Active l’horloge du Timer 3
	} else if (Timer==TIM4) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Active l’horloge du Timer 4
	} else if (Timer==TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //Active l’horloge du Timer 1
	}
	Timer->ARR=arr; //Valeur d'auto-reload
	Timer->PSC=psc; //Valeur de prescaler
}

void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (*IT_Funct)(void) ){
	Timer->DIER |= 0x1; //Active l'interruption
	Timer->SR &= ~(0x1); //Reset le flag d'interruption
	if (Timer==TIM2){
		NVIC->ISER[0]|=(0x1)<<28; //Active l'interruption dans le NVIC
		NVIC->IP[28]=Prio<<4; //Définit la priorité
		TIM2_IT_Funct=(*IT_Funct); //Définit la fonction de callback
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
* @Note Active le channel spécifié sur Timer le timer spécifié
* la gestion de la configuration I/O n’est pas faite dans cette fonction
* ni le réglage de la période de la PWM (ARR, PSC)
*/

void MyTimer_PWM(TIM_TypeDef * Timer, char Channel) {

	if (Timer == TIM1){
		TIM1->BDTR |= (0x1)<<15; // car TIM1 est "différent"
	}
	
	if (Channel == 1) {
		Timer->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //PWM mode 1 sur le channel 1 (OC1M=110)
		Timer->CCER |= TIM_CCER_CC1E; //Active le channel 1
	} else if (Channel == 2) {
		Timer->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; //PWM mode 1 sur le channel 2
		Timer->CCER |= TIM_CCER_CC2E; //Active le channel 2
	} else if (Channel == 3) {
		Timer->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
		Timer->CCER |= TIM_CCER_CC3E;
	} else if (Channel == 4) {
		Timer->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
		Timer->CCER |= TIM_CCER_CC4E;
	}

}

void MyTimer_PWM_SetDutyCycle(TIM_TypeDef * Timer, char Channel, float DutyCycle) {
	if (Channel == 1) {
		Timer->CCR1 = (uint16_t) (Timer->ARR * DutyCycle); //Définit le duty cycle
	} else if (Channel == 2) {
		Timer->CCR2 = (uint16_t) (Timer->ARR * DutyCycle);
	} else if (Channel == 3) {
		Timer->CCR3 = (uint16_t) (Timer->ARR * DutyCycle);
	} else if (Channel == 4) {
		Timer->CCR4 = (uint16_t) (Timer->ARR * DutyCycle);
	}
}
