#include "EulersMethodFunctions.h"
#include "Forces.h"
#include "RocketSpecs.h"
#include "Constants.h"
#include <math.h>
#include <stdio.h>

double F_gravity(CurrentData* current) {
    double force;
    return force = current->mass*GRAVITY;
}
double F_drag_Y(CurrentData* current) {
    double force;
    return force = ((current->airDensity*Y_AXIS_DRAGCO*PI*pow(DIAMETER/2, 2)*pow(current->velocity, 2))/2);
}
double F_thrust(CurrentData* current) {
    double force;
    float A = 6711;
    float B = 97.13;
    float C = 1839;
    float D = -1260;
    float E = 172.7;
    double t = current->time;
    if(t <= BURN_TIME) {
        current->thrust = A + B*(t) + C*pow(t, 2) + D*pow(t, 3) + E*pow(t, 4);
    } else {
        current->thrust = 0;
    }
    return force = current->thrust;
}
double F_airBrakes(CurrentData* current) {
    double force;
    switch(current->airBrakeState) {
        case 3:
            //printf("airbrakes state : 3\n");
            //I dont know how big the airbraakes are and how many there are going to be
            force = 4*((current->airDensity*PLATE_DRAGCO*DIAMETER/2*DIAMETER/(2*2)*pow(current->velocity, 2))/2);
            break;
        case 2:
            //printf("airbrakes state : 2\n");
            force = 4*((current->airDensity*PLATE_DRAGCO*DIAMETER/2*DIAMETER/(2*4)*pow(current->velocity, 2))/2);
            break;
        case 1:
            //printf("airbrakes state : 1\n");
            force = 4*((current->airDensity*PLATE_DRAGCO*DIAMETER/2*DIAMETER/(2*8)*pow(current->velocity, 2))/2);
            break;
        case 0:
            //printf("airbrakes state : 0\n");
            force = 0;
            break;
    }
    return force;
}
