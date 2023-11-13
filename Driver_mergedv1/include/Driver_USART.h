#ifndef MYUSART_H
#define MYUSART_H

#include "stm32f10x.h"

typedef struct{
	USART_TypeDef * Usart;
} MyUSART_Struct_TypeDef ;

/*
**************************************************************************************************
	* @brief
	* @param -> 
	* @Note -> 
*************************************************************************************************
*/
void MyUSART_Reception_Init(USART_TypeDef * Usart);

#endif
