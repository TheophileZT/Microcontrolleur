#include "stm32f10x.h"
#include "MyGPIO.h"

void MyGPIO_Init ( GPIO_TypeDef *GPIO, uint8_t pin, uint8_t conf){
	
	if (GPIO == GPIOA) {
		RCC->APB2ENR |= (0x01 << 2);
	}
	if (GPIO == GPIOB) {
		RCC->APB2ENR |= (0x01 << 3);
	}
	if (GPIO == GPIOC) {
		RCC->APB2ENR |= (0x01 << 4);
	}
	if (GPIO == GPIOD) {
		RCC->APB2ENR |= (0x01 << 5);
	}
	
	if(conf == In_PullDown){
			GPIO -> ODR &= ~(0x1 << pin);
		}
		else if (conf == In_PullUp){
			GPIO -> ODR |= (0x1 << pin);
		}
		
	if (pin < 8) {
		GPIO->CRL &= ~(0xF << 4*pin);
		if (conf == In_PullUp) {
			GPIO->CRL |= ((conf + 1) << 4*pin);
		}
		else {
			GPIO->CRL |= (conf << 4*pin);
		}
		
	}
	else {
		GPIO->CRH &= ~(0xF << 4*(pin - 8));
		if (conf == In_PullUp) {
			GPIO->CRH |= ((conf + 1) << 4*(pin - 8));
		}
		else {
			GPIO->CRH |= (conf << 4*(pin - 8));
		}
	}
}

int MyGPIO_Read (GPIO_TypeDef * GPIO , char GPIO_Pin) {
	return ((GPIO -> IDR) & (0x1 << GPIO_Pin));
}

void MyGPIO_Set (GPIO_TypeDef * GPIO , char GPIO_Pin) {
		GPIO -> ODR |= (0x01 << GPIO_Pin);
}

void MyGPIO_Reset (GPIO_TypeDef * GPIO , char GPIO_Pin) {
	GPIO -> ODR &= ~(0x01 << GPIO_Pin);
}

void MyGPIO_Toggle (GPIO_TypeDef * GPIO , char GPIO_Pin) {
	if (MyGPIO_Read (GPIO, GPIO_Pin)) {
		MyGPIO_Reset (GPIO, GPIO_Pin);
	}
	else {
		MyGPIO_Set (GPIO, GPIO_Pin);
	}
}
