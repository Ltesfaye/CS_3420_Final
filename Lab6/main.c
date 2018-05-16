#include <board.h>
#include "utils.h"
#include "Integrate.h"
#include "main.h"


 ACCELEROMETER_STATE state;
 MAGNETOMETER_STATE mstate;
 
 ACCELEROMETER_STATE  prior_state;
 ACCELEROMETER_STATE  offset;
 int priorx, priory;

 
 void Default (void){
		priorx=0;
		priory=0;
		
		int x = 0; 
	 while (x<100){
		 //samples the first 100 accelerometer data
		 Accelerometer_GetState(&state); // polls the most recent accelerometer data
		offset.x +=state.x;
		 offset.y +=state.y;
	 }
	 offset.x /=100;
	 offset.y /=100;
	 
		Accelerometer_GetState(&state); // polls the most recent accelerometer data
	 
	 	prior_state.x = state.x;
		prior_state.y = state.y;
		prior_state.z = state.z;
	
 }
 void SetUP(void){
 	// this instantiates exerything we're using 
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR = 0;
	PIT->CHANNEL[0].LDVAL = DEFAULT_SYSTEM_CLOCK /10; //approx 1/10 sec
	PIT->CHANNEL[1].LDVAL =  DEFAULT_SYSTEM_CLOCK/100; // approx 1/100 sec
	NVIC_EnableIRQ(PIT0_IRQn);
	NVIC_EnableIRQ(PIT1_IRQn);
	 
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	 
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;
	 
	NVIC_SetPriority(PIT0_IRQn, 1); //sets the priority for the interrupt so that we can write out appropriate data
	NVIC_SetPriority(PIT1_IRQn, 2);
 
 }
  void PIT0_IRQHandler (void){
	//This handels the interrupt request when it's passed in 
		Accelerometer_GetState(&state); // polls the most recent accelerometer data
	 
	 // computes the acceleration based on the prior acceleration data = .3*current value + .7*prior value
	 double a = state.x*0.6 + prior_state.x*0.4 - offset.x;
	 double b = state.y*0.6 + prior_state.y*0.4 - offset.y;
	 
	 	prior_state.x = a;
		prior_state.y = b;
	 
	 //outputs the values for desplay
		double x_pos  = integrate_posx(a*.001);
		int outx= (int)(x_pos*10000);
	 
		double y_pos  = integrate_posy(b*.001);
		int outy = (int)(y_pos*10000);
		priorx = outx;
		priory = outy;
	 
	 debug_printf("%8d %8d %8d \r\n", outx, outy, 121212);
	 
	 	PIT->CHANNEL[0].TFLG = 1;
}

 
 void PIT1_IRQHandler (void){
// this function is supposed to service the time update interrupt request
		
			PIT->CHANNEL[1].TFLG = 1;
}

int main() {
	LED_Initialize(); // this sets up the LEDS so that we can use them to desplay user MOVEMENT WHEN it's registered
	hardware_init(); // Sets up all the HARDWARE readings
	Accelerometer_Initialize(); // Initializes the Accelerometer
	Magnetometer_Initialize(); // Initializes the Magnetometer
	Default(); // sets up prior acceleration data
	debug_printf("%5d \r\n", 100000); //sends a reset signal everytime we start over again to python side due to the .05 second polling rate from the python side one may need to repress reset a couple of times
	
	setup_Integral(); // sets the Euler integral values to zeros
	SetUP(); //sets up the interrupt handeling

	//Magnetometer_GetState(&mstate);
	
	while(1){
	//creates a loop so program can run
	}


}
