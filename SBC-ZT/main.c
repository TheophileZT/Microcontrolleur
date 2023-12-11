#include "girouette.h"
#include "Driver_GPIO.h"
#include "servo.h"

int main(){
	
	GirouetteInit();
	while(1){
		bordage();
	}
}
