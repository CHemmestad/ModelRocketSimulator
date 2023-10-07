#ifndef ROCKET_SPECS_H

#define HEIGHT 3.6576 //m
#define DIAMETER 0.127 //m
#define ROCKET_MASS 9.572 //kg
#define MOTER_MASS 16.937 //kg
#define PROPELLANT_MASS 9.779 //kg
#define TOTAL_MASS (ROCKET_MASS+MOTER_MASS+PROPELLANT_MASS)
#define BURN_TIME 4.03 //s

//For now
#define X_AXIS_DRAGCO 0
#define Y_AXIS_DRAGCO 0.4
#define Z_AXIS_DRAGCO 0
#define PLATE_DRAGCO 1.2
#define IMPULSE 21384 //Ns
#define THRUST (IMPULSE/BURN_TIME) // N

#endif