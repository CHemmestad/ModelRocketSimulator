#ifndef FORCES_H
#define FORCES_H

double F_gravity(CurrentData* current);
double F_drag_Y(CurrentData* current);
double F_thrust(CurrentData* current);
double F_airBrakes(CurrentData* current);

#endif