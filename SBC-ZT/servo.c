#include "servo.h"
#include "Driver_Timer.h"
#include "girouette.h"
#include "Driver_GPIO.h"

float dutyCycle = 0.5;
float scaler = 0.1;

void servoInit(){
	MyTimer_Base_Init(TIM3, 65535, 21);	
	MyTimer_Base_Start(TIM3);
	MyTimer_PWM(TIM3,2);
	MyTimer_PWM_SetDutyCycle(TIM3,2,0.2f);
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
