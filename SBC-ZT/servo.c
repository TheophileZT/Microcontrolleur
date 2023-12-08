#include "servo.h"
#include "Driver_Timer.h"
#include "girouette.h"
#include "Driver_GPIO.h"

float dutyCycle = 0.5;
float scaler = 0.1;

void servoInit(){
	MyGPIO_Init(GPIOA, 0, AltOut_Ppull);
	MyTimer_Base_Init(TIM2, 65535, 21);	
	MyTimer_Base_Start(TIM2);
	MyTimer_PWM(TIM2,1);
	MyTimer_PWM_SetDutyCycle(TIM2,1,0.2f);
}

float traduceDutyCycle(float dutyCycle){
	return (dutyCycle/20)+0.05;
}

void bordage(void){
	float angleGirouette = GirouetteAngle();
	if(angleGirouette<50 && angleGirouette>40){
		dutyCycle = 0.2;
	} else {
		dutyCycle = 0.6;
	}
	MyTimer_PWM_SetDutyCycle(TIM4, 3, traduceDutyCycle(dutyCycle));
}
