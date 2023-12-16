#include "stm32f10x.h"
#include "Driver_GPIO.h"

// Fonction pour initialiser un GPIO
void MyGPIO_Init(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t conf) {
	// Activation de l'horloge pour le GPIO spécifié
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
	
	if (conf == In_PullDown) {
		GPIO->ODR &= ~(0x1 << pin);
	} else if (conf == In_PullUp) {
		GPIO->ODR |= (0x1 << pin);
	}

	// Configuration des registres CRL ou CRH en fonction du numéro de la pin
	if (pin < 8) {
		GPIO->CRL &= ~(0xF << 4 * pin);
		if (conf == In_PullUp) {
			GPIO->CRL |= ((conf + 1) << 4 * pin);
		} else {
			GPIO->CRL |= (conf << 4 * pin);
		}
	} else {
		GPIO->CRH &= ~(0xF << 4 * (pin - 8));
		if (conf == In_PullUp) {
			GPIO->CRH |= ((conf + 1) << 4 * (pin - 8));
		} else {
			GPIO->CRH |= (conf << 4 * (pin - 8));
		}
	}
}

// Fonction pour lire l'état d'une pin
int MyGPIO_Read(GPIO_TypeDef *GPIO, char GPIO_Pin) {
	return ((GPIO->IDR) & (0x1 << GPIO_Pin));
}

// Fonction pour définir l'état d'une pin à 1
void MyGPIO_Set(GPIO_TypeDef *GPIO, char GPIO_Pin) {
	GPIO->ODR |= (0x01 << GPIO_Pin);
}

// Fonction pour définir l'état d'une pin à 0
void MyGPIO_Reset(GPIO_TypeDef *GPIO, char GPIO_Pin) {
	GPIO->ODR &= ~(0x01 << GPIO_Pin);
}

// Fonction pour basculer l'état d'une pin
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, char GPIO_Pin) {
	if (MyGPIO_Read(GPIO, GPIO_Pin)) {
		MyGPIO_Reset(GPIO, GPIO_Pin);
	} else {
		MyGPIO_Set(GPIO, GPIO_Pin);
	}
}

// Configuration d'une interruption externe sur le GPIOB0 sur EXTI0
void MyGPIO_ExtI(void) {
	// Activation de l'horloge
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Initialisation de la pin
	MyGPIO_Init(GPIOB, 0, In_Floating);
	
	// Configuration de l'AFIO_EXTICR suur la bonne pin
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB;
	
	// Activation de l'interruption sur la pin 0
	EXTI->IMR |= EXTI_IMR_MR0;
	
	// Configuration du déclenchement sur front montant
	EXTI->RTSR |= EXTI_RTSR_TR0;
	
	// Effacement du drapeau d'interruption sur la pin 0
	EXTI->PR &= ~(0x1);
	
	// Activation de l'interruption dans le NVIC
	NVIC->ISER[0] |= (0x1) << 6;
	
	// Configuration de la priorité de l'interruption
	NVIC->IP[6] = 1 << 4;
}
