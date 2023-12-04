#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_GPIO.h"

void MyUSART_Reception_Init(USART_TypeDef * Usart) {
	
	if(Usart == USART1){
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN; //clock enable
	}
	else if(Usart == USART2){
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN; //clock enable
	}
	else if(Usart == USART3){
		RCC -> APB1ENR |= RCC_APB1ENR_USART3EN; //clock enable
	}
	
	if(Usart == USART1){
		MyGPIO_Init(GPIOA, 10, In_PullUp); //Pin de USART1_RX
	}
	else if(Usart == USART2){
		MyGPIO_Init(GPIOA, 3, In_PullUp); //Pin de USART2_RX
	}
	else if(Usart == USART3){
		MyGPIO_Init(GPIOB, 11, In_PullUp); //Pin de USART3_RX
	}
	
	Usart -> CR1 |= (0x1 << 13); //Enable the USART by writing the UE bit in USART_CR1 register to 1
	Usart -> CR1 &= ~(0x1 << 12); //Program the M bit in USART_CR1 to define the word length at 0 for  1 Start bit, 8 Data bits, n Stop bit
	Usart -> CR2 &= ~(0x3 << 12); //Program the number of stop bits in USART_CR2, 00: 1 Stop bit
	//Usart -> CR3 |= (0x1 << 6); //Select DMA enable (DMAR) in USART_CR3
	
	Usart -> BRR &= ~(0xFFFF);
	if(Usart == USART1){
		Usart -> BRR |= (0x1D4C); //baud rate pour USART1 (72Mhz/9600)
	}
	else if(Usart == USART2){
		Usart -> BRR |= (0xEA6); //baud rate pour USART2 (36Mhz/9600)
	}
	else if(Usart == USART3){
		Usart -> BRR |= (0xEA6); //baud rate pour USART3 (36Mhz/9600)
	}
	
	Usart -> CR1 |= (0x1 << 2); //Set the RE bit in USART_CR1.
	
	while (!(Usart -> SR & (0x1 << 6))) {
		Usart -> CR1 |= (0x1 << 2); //Set the RE bit USART_CR1. This enables the receiver which begins searching for a start bit
	} //After writing the last data into the USART_DR register, wait until TC=1. This indicates
																				 //that the transmission of the last frame is complete. This is required for instance when
																				 //the USART is disabled or enters the Halt mode to avoid corrupting the last
																				 //transmission.
}

void MyUSART_Transmission_Init(USART_TypeDef * Usart){
	
	if(Usart == USART1){
		MyGPIO_Init(GPIOA, 9, AltOut_Ppull); //Pin de USART1_TX
	}
	else if(Usart == USART2){
		MyGPIO_Init(GPIOA, 2, AltOut_Ppull); //Pin de USART2_TX
	}
	else if(Usart == USART3){
		MyGPIO_Init(GPIOB, 10, AltOut_Ppull); //Pin de USART3_TX
	}
	
	Usart -> CR1 |= (0x1 << 13); // Enable the USART by writing the UE bit in USART_CR1 register to 1.
	Usart -> CR1 &= ~(0x1 << 12); //Program the M bit in USART_CR1 to define the word length at 0 for  1 Start bit, 8 Data bits, n Stop bit
	Usart -> CR2 &= ~(0x3 << 12); //Program the number of stop bits in USART_CR2, 00: 1 Stop bit
	//Usart -> CR3 |= (0x1 << a regarder); //Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
															//place. Configure the DMA register as explained in multibuffer communication.
	if(Usart == USART1){
		Usart -> BRR |= (0x1D4C); //baud rate pour USART1 (72Mhz/9600)
	}
	else if(Usart == USART2){
		Usart -> BRR |= (0xEA6); //baud rate pour USART2 (36Mhz/9600)
	}
	else if(Usart == USART3){
		Usart -> BRR |= (0xEA6); //baud rate pour USART3 (36Mhz/9600)
	}
	
	Usart -> CR1 |= (0x1 << 3); //Set the TE bit in USART_CR1 to send an idle frame as first transmission.
}

void MyUSART_Send(USART_TypeDef * Usart, char * ptr){
	int i = 0;
	
	while (ptr[i]!='\0'){ //boucle pour itérer sur tous les char
		Usart -> DR = (ptr[i]);
		i++;
		while (!(Usart -> SR & (0x1 << 6))) {} //After writing the last data into the USART_DR register, wait until TC=1. This indicates
																				   //that the transmission of the last frame is complete. This is required for instance when
																				   //the USART is disabled or enters the Halt mode to avoid corrupting the last
																			 	   //transmission.
	} // Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		//for each data to be transmitted in case of single buffer.
}
