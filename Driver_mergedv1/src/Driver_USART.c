#include "stm32f10x.h"
#include "MyTimer.h"

void MyUSART_Reception_Init(USART_TypeDef * Usart) {
	Usart -> CR1 |= (0x1 << 13); //Enable the USART by writing the UE bit in USART_CR1 register to 1
	Usart -> CR1 &= ~(0x1 << 12); //Program the M bit in USART_CR1 to define the word length at 0 for  1 Start bit, 8 Data bits, n Stop bit
	Usart -> CR2 &= ~(0x3 << 12); //Program the number of stop bits in USART_CR2, 00: 1 Stop bit
	Usart -> CR3 |= (0x1 << 6); //Select DMA enable (DMAR) in USART_CR3
	Usart -> BRR &= ~(0xFFFF);
	/*********************************/
	Usart -> BRR |= (0x1D4C); //baud rate pour USART1 (72Mhz/9600)
	/*********************************/ //à changer pour autre usart2 et 3...
}


6. Set the RE bit USART_CR1. This enables the receiver which begins searching for a 
start bit

When a character is received
• The RXNE bit is set. It indicates that the content of the shift register is transferred to the 
RDR. In other words, data has been received and can be read (as well as its 
associated error flags).
• An interrupt is generated if the RXNEIE bit is set.
• The error flags can be set if a frame error, noise or an overrun error has been detected 
during reception.
• In multibuffer, RXNE is set after every byte received and is cleared by the DMA read to 
the Data Register.
• In single buffer mode, clearing the RXNE bit is performed by a software read to the 
USART_DR register. The RXNE flag can also be cleared by writing a zero to it. The 
RXNE bit must be cleared before the end of the reception of the next character to avoid 
an overrun error.
Note: The RE bit should not be reset while receiving data. If the RE bit is disabled during 
reception, the reception of the current byte will be aborted