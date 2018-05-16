#include "Integrate.h"

int prior_positionx;
int prior_velocityx;

int prior_positiony;
int prior_velocityy;

double time_step = 1./10.;



void setup_Integral(){
	//set's up everything to default values
	 prior_positionx = 0;
	 prior_velocityx = 0;
	
	 prior_positiony = 0;
	 prior_velocityy = 0;
	
}

double integrate_posx (double magnitude){ 
	// Computes and returns the values
		double velocityx = prior_velocityx + magnitude*9.8*(time_step);
		prior_velocityx = velocityx;
		double positionx = prior_positionx + velocityx*(time_step);
		prior_positionx = positionx;
		
	return positionx;
}

double integrate_posy (double magnitude){ 
	
		double velocityy = prior_velocityy + magnitude*9.8*(time_step);
		prior_velocityy= velocityy;
		double positiony = prior_positiony + velocityy*(time_step);
		prior_positiony = positiony;
		
	return positiony;
	
}
