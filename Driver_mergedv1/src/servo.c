#include "servo.h"
#include "Driver_Timer.h"
#include "girouette.h"
#include "Driver_GPIO.h"

float dutyCycle = 0.045;
float traduce;

float traduceDutyCycle(float dutyCycle){
	 // Cette fonction pourrait être utilisée pour effectuer une conversion ou un ajustement du cycle de service
	//traduce = (dutyCycle)/28.57;
	return dutyCycle;
}

void servoInit(){
	// Initialisation du Timer 3 en mode de base avec une période de 65535 et un prescaler de 21
	MyTimer_Base_Init(TIM3, 65535, 21);	
	MyTimer_Base_Start(TIM3);
	MyTimer_PWM(TIM3,2); //configuration de la PWM
	MyTimer_PWM_SetDutyCycle(TIM3,2,traduceDutyCycle(dutyCycle));
}

void bordage(void){
	
	float angleGirouette = GirouetteAngle(); // Récupération de l'angle de la girouette
	dutyCycle = (angleGirouette+180)/360; 
	// calcul du nouveau duty cycle en fonction de l'angle à remplacer par traduce dutyCycle avec une bonne fonction
	if (angleGirouette>-45 && angleGirouette<45){
		dutyCycle = 0.045;
	} else if (angleGirouette<0){
		dutyCycle = 0.088;
	} else {
		dutyCycle = 0.008;
	}
	
	MyTimer_PWM_SetDutyCycle(TIM3, 2, traduceDutyCycle(dutyCycle));
	
}
