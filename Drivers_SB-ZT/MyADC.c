#include "MyADC.h"

void myADC_Init(ADC_TypeDef * ADC, uint16_t psc, char channel){
	
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}
	
	RCC->CFGR &= ~((0x3)<<14);   // on passe les bits de ADCPRE à 0 avant de les modifier
	if (psc == 6){		
		RCC->CFGR |= (0x2)<<14;  // ou RCC_CFGR_ADCPRE_DIV6
	} else if (psc == 8) {
		RCC->CFGR |= (0x3)<<14; // ou RCC_CFGR_ADCPRE_DIV8
	}
	
	ADC1->CR2|= ADC_CR2_ADON; // Active l'ADC
	
	ADC->CR2 |= (0x1) << 20;  // Active le trigger externe
}
