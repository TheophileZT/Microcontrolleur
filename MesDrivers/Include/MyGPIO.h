#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

typedef struct
{
	GPIO_TypeDef * GPIO ;
	char GPIO_Pin ; //numero de 0 a 15
	char GPIO_Conf ; // voir ci dessous
} MyGPIO_Struct_TypeDef ;

#define In_Floating 0x4 
#define In_PullDown 0x8 
#define In_PullUp 0x7 //la vrai valeur est 0x8 mais elle est déjà utilisée par In_PullDown donc on va traiter ce cas particulier dans le .c
#define In_Analog 0x0 
#define Out_Ppull 0x1
#define Out_OD 0x5
#define AltOut_Ppull 0x9 
#define AltOut_OD 0x13 
void MyGPIO_Init (GPIO_TypeDef *GPIO, uint8_t pin, uint8_t conf);
int MyGPIO_Read (GPIO_TypeDef * GPIO , char GPIO_Pin); // renvoie 0 ou autre chose different de 0
void MyGPIO_Set (GPIO_TypeDef * GPIO , char GPIO_Pin);
void MyGPIO_Reset (GPIO_TypeDef * GPIO , char GPIO_Pin);
void MyGPIO_Toggle (GPIO_TypeDef * GPIO , char GPIO_Pin);
#endif
