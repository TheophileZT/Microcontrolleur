#ifndef MYUSART_H
#define MYUSART_H

#include "stm32f10x.h"

typedef struct{
	USART_TypeDef * Usart;
} MyUSART_Struct_TypeDef ;

/*
**************************************************************************************************
* @brief 
* @param -> USART_TypeDef * Usart : USART concrné
* @Note -> When a character is received
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
*************************************************************************************************
*/
void MyUSART_Reception_Init(USART_TypeDef * Usart);

/*
**************************************************************************************************
* @brief 
* @param -> USART_TypeDef * Usart : USART concrné
* @Note -> 
*************************************************************************************************
*/
void MyUSART_Emission_Init(USART_TypeDef * Usart);

#endif
