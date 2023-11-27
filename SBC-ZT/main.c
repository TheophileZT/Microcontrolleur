#include "girouette.h"
#include "Driver_GPIO.h"

int main(){
	
	GirouetteInit();
	MyGPIO_Init(GPIOC, 10, Out_Ppull);
	while(1){
		if (GirouetteAngle()>45||GirouetteAngle()<-45){
			MyGPIO_Set(GPIOC, 10);
		} else {
			MyGPIO_Reset(GPIOC, 10);
		}
	}
}
