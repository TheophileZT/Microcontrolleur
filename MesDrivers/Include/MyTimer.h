#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct
{
	TIM_TypeDef * Timer; // TIM1 � TIM4
	unsigned short ARR;
	unsigned short PSC;
} MyTimer_Struct_TypeDef ;

/*
**************************************************************************************************
	* @brief
	* @param -> Param�tre sous forme d�une structure (son adresse) contenant les
		informations de base
	* @Note -> Fonction � lancer syst�matiquement avant d�aller plus en d�tail dans les
	c 	conf plus fines (PWM, codeur inc...)
*************************************************************************************************
*/
void MyTimer_Base_Init (TIM_TypeDef * Timer, uint16_t ARR, uint16_t PSC);

#define MyTimer_Base_Start(Timer) Timer->CR1|=(0x01);
#define MyTimer_Base_Stop(Timer) Timer->CR1&=(0x00);

/*
**************************************************************************************************
* @brief
* @param : - TIM_TypeDef * Timer : Timer concerne
- char Prio : de 0 a 15
* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
**************************************************************************************************
*/
void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_Func)(void));

/*
**************************************************************************************************
	* @brief
	* @param - TIM_TypeDef * Timer : Timer concerne,
	- char Channel : channel 1 � 4,
	* @Note Active le channel sp�cifi� sur le timer sp�cifi�
	* 			la gestion de la configuration I/O n�est pas faite dans cette fonction
	* 			ni le r�glage de la p�riode de la PWM (ARR, PSC)
**************************************************************************************************
*/
void MyTimer_PWM( TIM_TypeDef * Timer, char Channel);

/*
**************************************************************************************************
	*@brief
	* @param - Rapport : rapport cyclique souhait� de la PWM e pourcentage
	* @Note : Le timer doit avoir �t� initialis� avec MyTimer_Base_Init
**************************************************************************************************
*/
void MyTimer_PWM_Config (TIM_TypeDef * Timer, char Channel, float Rapport);

#endif
