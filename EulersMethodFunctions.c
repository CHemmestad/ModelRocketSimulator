#include "EulersMethodFunctions.h"
#include "RocketSpecs.h"
#include "Constants.h"
#include "Forces.h"

double findMax(double max, double current) {
    if(current > max) {
        return current;
    } else {
        return max;
    }
}

void initialize(CurrentData* current) {
    current->maxAcceleration = 0;
    current->maxVelocity = 0;
    current->maxHeight = 0;
    current->acceleration = 0;
    current->velocity = 0;
    current->height = 0;
    current->temp = 0;
    current->time = 0;
    current->airDensity = AIR_DENSITY;
    current->mass = TOTAL_MASS;
    current->thrust = 0;
    current->airBrakeState = 0;
}
void deviation(CurrentData* predicted, CurrentData* current) {
    double deviation;
    deviation = TARGET/predicted->maxHeight;
    if(current->time > BURN_TIME) {
        if(deviation < .98) {
            current->airBrakeState = 3;
        } else if(deviation < .995) {
            current->airBrakeState = 2;
        } else if(deviation < 1) {
            current->airBrakeState = 1;
        } else {
            current->airBrakeState = 0;
        }
    }
}
void newAcceleration(CurrentData* current) {
    double newAcceleration;
    if(current->velocity >= -1) {
        if(current->time <= BURN_TIME) {
            newAcceleration = (-(F_drag_Y(current)) - (F_gravity(current)) + (F_thrust(current)))/current->mass;
        } else {
            newAcceleration = (-(F_drag_Y(current)) - (F_airBrakes(current)) -  (F_gravity(current)))/current->mass;
        }
    } else {
        newAcceleration = (F_drag_Y(current) - (F_gravity(current)))/current->mass;
    }
    current->maxAcceleration = findMax(current->maxAcceleration, newAcceleration);
    current->acceleration = newAcceleration;
}
void newVelocity(CurrentData* current) {
    double newVelocity;
    newVelocity = current->velocity + current->acceleration*TIME_STEP;
    current->maxVelocity = findMax(current->maxVelocity, newVelocity);
    current->velocity = newVelocity;
}
void newHeight(CurrentData* current) {
    double newHeight;
    newHeight = current->height + current->velocity*TIME_STEP;
    current->maxHeight = findMax(current->maxHeight, newHeight);
    current->height = newHeight;
}
void newMass(CurrentData* current) {
    if(current->time <= BURN_TIME) {
        current->mass = current->mass - (PROPELLANT_MASS/BURN_TIME)*TIME_STEP;
    }
}
void newAirDensity(CurrentData* current) {
    current->airDensity = AIR_DENSITY - current->height*DELTA_AIR_DENSITY;
    if(current->airDensity < 0) {
        current->airDensity = 0;
    }
}
void addTime(CurrentData* current) {
    current->time = current->time+TIME_STEP;
}
