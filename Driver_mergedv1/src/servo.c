#include "servo.h"
#include "Driver_Timer.h"
#include "girouette.h"
#include "Driver_GPIO.h"

float dutyCycle = 0.045;
float traduce;

float traduceDutyCycle(float dutyCycle){
	//traduce = (dutyCycle)/28.57;
	return dutyCycle;
}

void servoInit(){
	MyTimer_Base_Init(TIM3, 65535, 21);	
	MyTimer_Base_Start(TIM3);
	MyTimer_PWM(TIM3,2);
	MyTimer_PWM_SetDutyCycle(TIM3,2,traduceDutyCycle(dutyCycle));
}

void bordage(void){
	float angleGirouette = GirouetteAngle();
	dutyCycle = (angleGirouette+180)/360;
	if (angleGirouette>-45 && angleGirouette<45){
		dutyCycle = 0.045;
	} else if (angleGirouette<0){
		dutyCycle = 0.088;
	} else {
		dutyCycle = 0.008;
	}
	
	MyTimer_PWM_SetDutyCycle(TIM3, 2, traduceDutyCycle(dutyCycle));
	
}
