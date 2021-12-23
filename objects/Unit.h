//
// Created by ct_co on 21/12/2021.
//

#ifndef TOPOGRAPHY_UNIT_H
#define TOPOGRAPHY_UNIT_H


#include "Coordinate.h"
#include "VectorPath.h"

class Unit {

public:
    Coordinate location;
    Coordinate targetLocation;

    // this is measured in fractions of width of map square/tic
    // e.g. speed of 0.1 will take 10 movement tics to travel directly from N to S
    double speed = 0.1;
    VectorPath directionVector;


    explicit Unit(Coordinate aLocation, Coordinate aTargetLocation, VectorPath aDirectionVector)
    : location(aLocation), targetLocation(aTargetLocation), directionVector(aDirectionVector){};

};


#endif //TOPOGRAPHY_UNIT_H
