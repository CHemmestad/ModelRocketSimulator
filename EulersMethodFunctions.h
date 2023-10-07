#ifndef EUHLERS_METHOD_H
#define EUHLERS_METHOD_H

typedef struct CurrentData {
    double maxAcceleration;
    double maxVelocity;
    double maxHeight;
    double acceleration;
    double velocity;
    double height;
    double airDensity;
    double temp;
    double time;
    double mass;
    double thrust;
    int airBrakeState; //3 high 2 medium 1 low 0 off
} CurrentData;

void newAcceleration(CurrentData* current);
void newVelocity(CurrentData* current);
void newHeight(CurrentData* current);
void newMass(CurrentData* current);
void newAirDensity(CurrentData* current);
void deviation(CurrentData* predicted, CurrentData* current);
void addTime(CurrentData* current);
void initialize(CurrentData* current);

#endif