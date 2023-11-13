#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"

void (*TIM2_PTR)(void);//déclaration d'une variable gloqbale d'un poiteur de fonction

void MyTimer_Base_Init (TIM_TypeDef * Timer, uint16_t ARR, uint16_t PSC) {
	
	MyTimer_Base_Stop(Timer); //arrête le timer avant de l'initialiser au cas où
	
	if (Timer == TIM1) {
		RCC -> APB2ENR |= (0x01 << 11);
	}
	else if (Timer == TIM2) {
		RCC -> APB1ENR |= (0x01);
	}
	else if (Timer == TIM3) {
		RCC -> APB1ENR |= (0x01 << 1);
	}
	else if (Timer == TIM4) {
		RCC -> APB1ENR |= (0x01 << 2);
	}
	
	Timer -> ARR = ARR;
	Timer -> PSC = PSC;
}

void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_Func)(void)) {
	Timer -> DIER |= (0x01); //UIE
	NVIC -> ISER[0] |= (0x01 << 28);
	NVIC -> IP[28] = Prio << 4;
	TIM2_PTR = IT_Func; //copie de l'adresse de la fonction à exécuter dans la variable globale du pointeur de fonction
}

void TIM2_IRQHandler (void) {
/*completer avec le code de la routine du traitement de l’interruption*/
	
	//MyGPIO_Toggle(GPIOB, 12);
	//TIM2 -> SR &= ~(0x1);
	(*TIM2_PTR)(); //déréférencement puis éxécution du poiteur de fonction
}

void MyTimer_PWM( TIM_TypeDef * Timer, char Channel){
	if (Timer == TIM1){
		TIM1 -> BDTR = (0x1 << 15); //MOE à 1 pour le timer1 
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
		Timer -> CCER &= ~(0x1); //désactive CC1 le temps de l'initialisation
		Timer -> CCMR1 &= ~(0x3); // channel 1 en output
		Timer -> CCER |= (0x1); // réactive CC1
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
		Timer -> CCER &= ~(0x1 << 4); //désactive CC2 le temps de l'initialisation
		Timer -> CCMR1 &= ~(0x3 << 8); // channel 2 en output
		Timer -> CCER |= (0x1 << 4); // réactive CC2
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
		Timer -> CCER &= ~(0x1 << 8); //désactive CC3 le temps de l'initialisation
		Timer -> CCMR2 &= ~(0x3); // channel 3 en output
		Timer -> CCER |= (0x1 << 8); // réactive CC3
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
		Timer -> CCER &= ~(0x1 << 12); //désactive CC4 le temps de l'initialisation
		Timer -> CCMR2 &= ~(0x3 << 8); // channel 4 en output
		Timer -> CCER |= (0x1 << 12); // réactive CC4
	}
}

void MyTimer_PWM_Config (TIM_TypeDef * Timer, char Channel, float Rapport){
	uint16_t ARR = Timer -> ARR;
	uint16_t CCRx = (Rapport/100)*ARR;
	
	if (Channel == 1) {
		Timer -> CCR1 = CCRx;
	}
	else if (Channel == 2) {
		Timer -> CCR2 = CCRx;
	}
	else if (Channel == 3) {
		Timer -> CCR3 = CCRx;
	}
	else if (Channel == 4) {
		Timer -> CCR4 = CCRx;
	}
}
