//
// Created by ct_co on 22/12/2021.
//

#ifndef TOPOGRAPHY_VECTORPATH_H
#define TOPOGRAPHY_VECTORPATH_H


#include "Vector.h"

class VectorPath {

public:
    Vector vector;
    double speed;
    VectorPath(): vector(Vector(0,0)), speed(0){};
    VectorPath(double aU, double aV, double aSpeed);

};


#endif //TOPOGRAPHY_VECTORPATH_H
