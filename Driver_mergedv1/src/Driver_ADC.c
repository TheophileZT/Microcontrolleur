#include "Driver_ADC.h"

void myADC_Init(ADC_TypeDef * ADC, uint16_t psc, char channel){
	
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}
	
	RCC->CFGR &= ~((0x3)<<14);   // on passe les bits de ADCPRE � 0 avant de les modifier
	if (psc == 6){		
		RCC->CFGR |= (0x2)<<14;  // ou RCC_CFGR_ADCPRE_DIV6  car la fréquence de l'horloge doit être inférieur à 14Mhz
	} else if (psc == 8) {
		RCC->CFGR |= (0x3)<<14; // ou RCC_CFGR_ADCPRE_DIV8
	}
	
	ADC1->CR2|= ADC_CR2_ADON; // Active l'ADC
	
	ADC1->SQR1&= ADC_SQR1_L;
	ADC1->SQR3|= channel;
}

int myADC_conversion(){
	ADC1->CR2 |= ADC_CR2_ADON; //lance la conversion
	while(!(ADC1->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
	ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
  return ADC1->DR & ~((0x0F) << 12); // retour de la conversion
}
