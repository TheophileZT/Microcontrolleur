#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"

void IT_Func (void) {
	MyGPIO_Toggle(GPIOB, 12);
	TIM2 -> SR &= ~(0x1);
}

int main (void)
{
	/*RCC -> APB1ENR |= (0x01);
	TIM2 -> CR1 |= (0x01);
	TIM2 -> ARR = 65454;
	TIM2 -> PSC = 549;*/
		
	//MyTimer_Base_Init (TIM1, 65454, 549);
	//MyTimer_Base_Init (TIM2, 65454, 549); //période de 0,5s
	//MyTimer_Base_Init (TIM3, 65454, 549);
	//MyTimer_Base_Init (TIM4, 65454, 549);
	
	//MyTimer_ActiveIT(TIM2, 10, *IT_Func);
	
	//MyGPIO_Init (GPIOB, 12, Out_Ppull) ;
	
	//MyTimer_Base_Start(TIM1);
	//MyTimer_Base_Start(TIM2);
	//MyTimer_Base_Start(TIM3);
	//MyTimer_Base_Start(TIM4);
	
	//MyTimer_PWM(TIM2, 1);
	
	MyTimer_Base_Init (TIM2, 359, 1);//fréquence de 100kH
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(TIM2, 1);
	MyTimer_PWM_Config(TIM2, 1, 20);
	
	do {
	} while(1);
}
