#include "servo.h"
#include "Driver_Timer.h"
#include "girouette.h"

float dutyCycle = 0.5;
float scaler = 0.1;

void servoInit(){
	MyTimer_Base_Init(TIM4, 1199,1199);
	MyTimer_PWM(TIM4,3);
	MyTimer_Base_Start(TIM4);
}

void bordage(void){
	float angleGirouette = GirouetteAngle();
	if(angleGirouette<50 && angleGirouette>40){
		dutyCycle = 0.2;
	} else {
		dutyCycle = 0.6;
	}
	MyTimer_PWM_SetDutyCycle(TIM4, 3, scaler*dutyCycle);
}
