#include "girouette.h"
#include "Driver_GPIO.h"

int main(){
	
	GirouetteInit();
	while(1){
		GirouetteAngle();
	}
}
