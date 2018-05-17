#include <board.h>
#include "utils.h"
#include "Integrate.h"
#include "main.h"


 ACCELEROMETER_STATE state;
 //MAGNETOMETER_STATE mstate;
 
 ACCELEROMETER_STATE  prior_state;
 ACCELEROMETER_STATE  offset;


 double priorx, priory;
 int mode = 0;
 void Default (void){
		priorx=0;
		priory=0;
		mode = 0;
	/*	int x = 0; 
	 while (x<100){
		 //samples the first 100 accelerometer data
		 Accelerometer_GetState(&state); // polls the most recent accelerometer data
		offset.x +=state.x;
		 offset.y +=state.y;
		 x+=1;
	 }
	 offset.x /=100;
	 offset.y /=100;*/
	 
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
	 
	//PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
	//PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;
	 
	NVIC_SetPriority(PIT0_IRQn, 1); //sets the priority for the interrupt so that we can write out appropriate data
	NVIC_SetPriority(PIT1_IRQn, 2);
 
 }
 void PIT0_IRQHandler (void){
	//This handels the interrupt request when it's passed in 
		Accelerometer_GetState(&state); // polls the most recent accelerometer data
	 
	 // computes the acceleration based on the prior acceleration data = .3*current value + .7*prior value
	 double a = state.x*0.5 + prior_state.x*0.5;
	 double b = state.y*0.5 + prior_state.y*0.5;
	 
	 	prior_state.x = a;
		prior_state.y = b;
	
	 if (mode == 0){
	 //outputs the values for desplay
		double x_pos = priorx;
		double y_pos = priory;
		int outy = (int)(y_pos*10000);
		int outx = (int)(x_pos*10000);
	 
		if (state.x > 30 || state.x < -30){
		x_pos  = integrate_posx(a*.001);
		priorx = x_pos;
		int outx= (int)(x_pos*10000);
	 }
	
	if (state.y>60 || state.y < -60){
					y_pos  = integrate_posy(b*.001);
					priory = y_pos;
					outy = (int)(y_pos*10000);
		}

		debug_printf("%8d %8d %8d \r\n", outx, outy, 121212);
	 }
	 else if (mode == 1) {
					 double x_pos = priorx;
					double y_pos = priory;
					int outy = (int)(y_pos*10000);
					int outx = (int)(x_pos*10000);
				 
					if (a > 30 || a < -30){
					x_pos  = integrate_velx(a*.001);
					priorx = x_pos;
					int outx= (int)(x_pos*10000);
				 }
				
				if (b>60 || b < -60){
								y_pos  = integrate_vely(b*.001);
								priory = y_pos;
								outy = (int)(y_pos*10000);
					}

					debug_printf("%8d %8d %8d \r\n", outx, outy, 1010);
	 
	 }
	 else {
		 
		 	 double x_pos = priorx;
				double y_pos = priory;
					int outy = (int)(y_pos*10 * 9.8);
					int outx = (int)(x_pos*10 * 9.8);
				 
					if (a > 30 || a < -30){
					x_pos  = (a*.001*9.8);
					priorx = x_pos;
					int outx= (int)(x_pos*10000);
				 }
				
				if (b>60 || b < -60){
								y_pos  = (b*.001*9.8);
								priory = y_pos;
								outy = (int)(y_pos*10000);
					}
				debug_printf("%8d %8d %8d \r\n", outx, outy, 1111);
	 
	 }
	 
	 	PIT->CHANNEL[0].TFLG = 1;
}

 
 void PIT1_IRQHandler (void){
// this function is supposed to service the time update interrupt request
		
			PIT->CHANNEL[1].TFLG = 1;
}
 void setup_Button(void){
			
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; //Enable clock to Port B
			PORTC_PCR6 |= (PORT_PCR_MUX(1));  // Set 
			PTC->PDDR &= ~(1 << 6); // Configuring Port B as input
			PORTC_PCR6 |= (1<<1); //enables pull up
			PORTC_PCR6 |= (1001 << 16); //triggers interrupt on rising edge
			NVIC_EnableIRQ(PORTC_IRQn) ;  //Setting IRQ handler for PortB
		 
	 //PTC6
 }
 void PORTC_IRQHandler(void) {
			 //GPIOA_PSOR |= (1 << 1);
			__disable_irq(); // sets PM flag
			
	 			//debug_printf("HI");
			if(PTC->PDIR & GPIO_PDIR_PDI(1<<6) ){
				if (mode == 0){
					LEDRed_On();
					delay();
					delay();
					LEDRed_Toggle();
					setup_Integral();
					debug_printf("%5d \r\n", 100000); //sends a reset signal
					mode = 1;
				}
				else if (mode ==1){
						LEDGreen_On();
						delay();
						delay();
						LEDGreen_Toggle();
						setup_Integral();
						debug_printf("%5d \r\n", 100000); //sends  reset signal
						mode = 2;
				}
				else {
					
						LEDBlue_Toggle();
						delay();
						delay();
						LEDBlue_Toggle();
						setup_Integral(); //resets integral values to default
						debug_printf("%5d \r\n", 100000); //sends  reset signal
						mode = 0;
				
				
				}
				
					priorx = 0.0;
					priory = 0.0;
				
			
			} 


				
			PORTC -> ISFR = (1 << 6); //clears it
		//	NVIC_ClearPendingIRQ(PORTC_IRQn);
		__enable_irq(); // clears PM flag
}


int main() {
	LED_Initialize(); // this sets up the LEDS so that we can use them to desplay user MOVEMENT WHEN it's registered
	hardware_init(); // Sets up all the HARDWARE readings
	Accelerometer_Initialize(); // Initializes the Accelerometer
	Default(); // sets up prior acceleration data
	debug_printf("%5d \r\n", 100000); //sends a reset signal everytime we start over again to python side due to the .05 second polling rate from the python side one may need to repress reset a couple of times
	setup_Button(); //toggleing between velocity and acceleration
	setup_Integral(); // sets the Euler integral values to zeros
	SetUP(); //sets up the interrupt handeling

	//Magnetometer_GetState(&mstate);
	
	while(1){
	//creates a loop so program can run
	}


}
