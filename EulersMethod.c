#include <stdio.h>
#include <stdlib.h>
#include "EulersMethodFunctions.h"
#include "Constants.h"

void printMaxMetric(CurrentData* current);
void printMaxImperial(CurrentData* current);
void runPredictions(CurrentData* current);
void cpyStru(CurrentData* struct1, CurrentData* struct2);
void recordData(CurrentData* current, FILE *file1, FILE *file2);

int main() {
    CurrentData* predicted = (CurrentData*)malloc(sizeof(CurrentData));
    CurrentData* current = (CurrentData*)malloc(sizeof(CurrentData));

    FILE *fptr1, *fptr2;
    fptr1 = fopen("Height.txt", "w");
    fptr2 = fopen("Time.txt", "w");

    initialize(predicted);
    initialize(current);

    while(current->height > -0.1) {
        for(double timer = 0; timer < .10; timer += TIME_STEP) {
            newAcceleration(current);
            newVelocity(current);
            newHeight(current);
            newMass(current);
            newAirDensity(current);
            addTime(current);
        }
        recordData(current, fptr1, fptr2);
        cpyStru(predicted, current);
        runPredictions(predicted);
        deviation(predicted, current);
    }

    printMaxMetric(current);
    printMaxImperial(current);
    free(predicted);
    free(current);

    fclose(fptr1);
    fclose(fptr2);
    
    return 0;
}

void runPredictions(CurrentData* predicted) {
    while(predicted->height > -0.1) {
        newAcceleration(predicted);
        newVelocity(predicted);
        newHeight(predicted);
        newMass(predicted);
        newAirDensity(predicted);
        addTime(predicted);
    }
}
void cpyStru(CurrentData* struct1, CurrentData* struct2) {
    struct1->maxAcceleration = struct2->maxAcceleration;
    struct1->maxVelocity = struct2->maxVelocity;
    struct1->maxHeight = struct2->maxHeight;
    struct1->acceleration = struct2->acceleration;
    struct1->velocity = struct2->velocity;
    struct1->height = struct2->height;
    struct1->temp = struct2->temp;
    struct1->time = struct2->time;
    struct1->airDensity = struct2->airDensity;
    struct1->mass = struct2->mass;
    struct1->thrust = struct2->thrust;
}

void recordData(CurrentData* current, FILE *file1, FILE *file2) {
    fprintf(file1, "%lf\n", current->height);
    fprintf(file2, "%lf\n", current->time);
}

void printMaxMetric(CurrentData* current) {
    printf("Max Acceleration (m/s^2) : %.4lf, Max Velocity (m/s): %.4lf, Max Height (m): %.4lf, Flight Time (s): %.4lf\n", 
    current->maxAcceleration, current->maxVelocity, current->maxHeight, current->time);
}

void printMaxImperial(CurrentData* current) {
    printf("Max Acceleration (G) : %.4lf, Max Velocity (ft/s): %.4lf, Max Height (ft): %.4lf, Flight Time (s): %.4lf\n", 
    current->maxAcceleration*0.10197, current->maxVelocity*3.28084, current->maxHeight*3.28084, current->time);
}
