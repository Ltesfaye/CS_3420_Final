#ifndef __INTEGRATE_H__
#define __INTEGRATE_H__
void setup_Integral(void); // set's up default Euler Integral Values
double integrate_posx(double magnitude); // Computes and returns position based on prior values
double integrate_posy(double magnitude); // Computes and returns position based on prior values
double integrate_velx(double m);
double integrate_vely(double m);


#endif

