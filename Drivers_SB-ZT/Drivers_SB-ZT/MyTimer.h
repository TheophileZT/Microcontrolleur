#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"
typedef struct
{
TIM_TypeDef * Timer ; // TIM1 à TIM4
unsigned short ARR ;
unsigned short PSC ;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d’une structure (son adresse) contenant les
informations de base
* @Note -> Fonction à lancer systématiquement avant d ’aller plus en détail dans les
conf plus fines (PWM, codeur inc ... )
*************************************************************************************************
*/
void MyTimer_Base_Init ( TIM_TypeDef * Timer, uint16_t arr, uint16_t psc) ;
#define MyTimer_Base_Start(Timer) (Timer)->CR1|=1
#define MyTimer_Base_Stop(Timer) (Timer)->CR1&=~0x1


/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer concerne
- char Prio : de 0 a 15
* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
**************************************************************************************************
*/
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio, void (*IT_Funct)(void) );


/**
* @brief
* @param ....
* @Note Active le channel spécifié sur Timer le timer spécifié
* la gestion de la configuration I/O n’est pas faite dans cette fonction
* ni le réglage de la période de la PWM (ARR, PSC)
*/
void MyTimer_PWM( TIM_TypeDef * Timer , char Channel ) ;
void MyTimer_PWM_SetDutyCycle(TIM_TypeDef * Timer, char Channel, float DutyCycle);

#endif
