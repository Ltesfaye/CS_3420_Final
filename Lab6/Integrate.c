#include "Integrate.h"
#include <fsl_debug_console.h>

double prior_positionx;
double prior_velocityx;

double prior_positiony;
double prior_velocityy;

double time_step = 1./10.;



void setup_Integral(){
	//set's up everything to default values
	 prior_positionx = 0.0;
	 prior_velocityx = 0.0;
	
	 prior_positiony = 0.0;
	 prior_velocityy = 0.0;
	time_step = 1./10.;

	
	
}
double integrate_velx(double m){
		double velocityx = prior_velocityx + m*9.8*(time_step);
		prior_velocityx = velocityx;
	return velocityx;
}
double integrate_vely(double m){
		double velocityy = prior_velocityy + m*9.8*(time_step);
		prior_velocityy= velocityy;
	return velocityy;
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
