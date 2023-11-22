#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_GPIO.h"

void MyUSART_Reception_Init(USART_TypeDef * Usart) {
	
	/*********************************/
	MyGPIO_Init(GPIOA, 10, In_PullUp); //Pin de USART1_RX
	/*********************************/ //à changer pour autre usart2 et 3...
	
	Usart -> CR1 |= (0x1 << 13); //Enable the USART by writing the UE bit in USART_CR1 register to 1
	Usart -> CR1 &= ~(0x1 << 12); //Program the M bit in USART_CR1 to define the word length at 0 for  1 Start bit, 8 Data bits, n Stop bit
	Usart -> CR2 &= ~(0x3 << 12); //Program the number of stop bits in USART_CR2, 00: 1 Stop bit
	//Usart -> CR3 |= (0x1 << 6); //Select DMA enable (DMAR) in USART_CR3
	Usart -> BRR &= ~(0xFFFF);
	
	/*********************************/
	Usart -> BRR |= (0x1D4C); //baud rate pour USART1 (72Mhz/9600)
	/*********************************/ //à changer pour autre usart2 et 3...
	
	Usart -> CR1 |= (0x1 << 2); //Set the RE bit USART_CR1. This enables the receiver which begins searching for a start bit
}

void MyUSART_Transmission_Init(USART_TypeDef * Usart, char * ptr){
	int i = 0;
	
	/*********************************/
	MyGPIO_Init(GPIOA, 9, AltOut_Ppull); //Pin de USART1_TX
	/*********************************/ //à changer pour autre usart2 et 3...
	
	Usart -> CR1 |= (0x1 << 13); // Enable the USART by writing the UE bit in USART_CR1 register to 1.
	Usart -> CR1 &= ~(0x1 << 12); //Program the M bit in USART_CR1 to define the word length at 0 for  1 Start bit, 8 Data bits, n Stop bit
	Usart -> CR2 &= ~(0x3 << 12); //Program the number of stop bits in USART_CR2, 00: 1 Stop bit
	//Usart -> CR3 |= (0x1 << a regarder); //Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
															//place. Configure the DMA register as explained in multibuffer communication.
	/*********************************/
	Usart -> BRR |= (0x1D4C); //baud rate pour USART1 (72Mhz/9600)
	/*********************************/ //à changer pour autre usart2 et 3...
	
	Usart -> CR1 |= (0x1 << 3); //Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	
	while (ptr[i]!='\0'){ //boucle pour itérer sur tous les char
		Usart -> DR = (ptr[i]);
		i++;
	} // Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		//for each data to be transmitted in case of single buffer.
	while (!(Usart -> SR & (0x1 << 6))) {} //After writing the last data into the USART_DR register, wait until TC=1. This indicates
																				 //that the transmission of the last frame is complete. This is required for instance when
																				 //the USART is disabled or enters the Halt mode to avoid corrupting the last
																				 //transmission.
}
