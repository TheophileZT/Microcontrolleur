#include "Driver_GPIO.h"

void MyGPIO_Init ( GPIO_TypeDef * GPIO, uint8_t pin, uint8_t conf ){
	if(GPIO==GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	if(GPIO==GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	if(GPIO==GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	if(GPIO==GPIOD) RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	if (pin<8){
		GPIO->CRL&=(~(0xF))<<pin*4;
		
		switch (conf) {
			case In_Floating :
				GPIO->CRL|=(0x4)<<pin*4;
				break;
			case In_PullDown :
				GPIO->CRL|=(0x8)<<pin*4;
				GPIO->ODR=0;
				break;
			case In_PullUp :
				GPIO->CRL|=(0x8)<<pin*4;
				GPIO->ODR=1;
				break;
			case In_Analog :
				break;
			case Out_Ppull :
				GPIO->CRL|=(0x3)<<pin*4;
				break;
			case Out_OD :
				GPIO->CRL|=(0x7)<<pin*4;
				break;
			case AltOut_Ppull :
				GPIO->CRL|=(0xB)<<pin*4;
				break;
			case AltOut_OD :
				GPIO->CRL|=(0xF)<<pin*4;
				break;
		}
	}
	if (pin>7){
		GPIO->CRH&=(~(0xF))<<(pin*4)%8;
		
		switch (conf) {
			case In_Floating :
				GPIO->CRH|=(0x4)<<(pin*4)%8;
				break;
			case In_PullDown :
				GPIO->CRH|=(0x8)<<(pin*4)%8;
				GPIO->ODR=0;
				break;
			case In_PullUp :
				GPIO->CRH|=(0x8)<<(pin*4)%8;
				GPIO->ODR=1;
				break;
			case In_Analog :
				break;
			case Out_Ppull :
				GPIO->CRH|=(0x3)<<(pin*4)%8;
				break;
			case Out_OD :
				GPIO->CRH|=(0x7)<<(pin*4)%8;
				break;
			case AltOut_Ppull :
				GPIO->CRH|=(0xB)<<(pin*4)%8;
				break;
			case AltOut_OD :
				GPIO->CRH|=(0xF)<<(pin*4)%8;
				break;
		}
		
	}

}
int MyGPIO_Read ( GPIO_TypeDef * GPIO , uint8_t pin ){// renvoie 0 ou autre chose different de 0
	GPIO->IDR&=(~(0x1))<<pin;
	return GPIO->IDR;
}



void MyGPIO_Set ( GPIO_TypeDef * GPIO , uint8_t pin ){
	GPIO->ODR|=(0x1)<<pin;
}



void MyGPIO_Reset ( GPIO_TypeDef * GPIO , uint8_t pin ){
	GPIO->ODR&=(~(0x1))<<pin;
}



void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , uint8_t pin ){
	GPIO->ODR^=(0x1)<<pin;
}

