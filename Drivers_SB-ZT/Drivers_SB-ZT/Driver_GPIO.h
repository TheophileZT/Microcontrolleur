#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"
typedef struct
{
GPIO_TypeDef * GPIO ;
char GPIO_Pin ; //numero de 0 a 15
char GPIO_Conf ; //voir ci dessous
} MyGPIO_Struct_TypeDef ;
#define In_Floating 0x1 // a completer
#define In_PullDown 0x2 // a completer
#define In_PullUp 0x3// a completer
#define In_Analog 0x4 // a completer
#define Out_Ppull 0x5 // a completer
#define Out_OD 0x6 // a completer
#define AltOut_Ppull 0x7 // a completer
#define AltOut_OD 0x8 // a completer
void MyGPIO_Init ( GPIO_TypeDef * GPIOStructPtr, uint8_t pin, uint8_t conf ) ;
int MyGPIO_Read ( GPIO_TypeDef * GPIO , uint8_t pin ) ; // renvoie 0 ou autre chose different de 0
void MyGPIO_Set ( GPIO_TypeDef * GPIO , uint8_t pin ) ;
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , uint8_t pin ) ;
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , uint8_t pin ) ;
#endif
