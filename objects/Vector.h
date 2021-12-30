//
// Created by ct_co on 22/12/2021.
//

#ifndef TOPOGRAPHY_VECTOR_H
#define TOPOGRAPHY_VECTOR_H

class Vector {

public:

    double u;
    double v;

    Vector(): u(0.0), v(0.0){};
    Vector(double aU, double aV) : u(aU), v(aV) {};

};


#endif //TOPOGRAPHY_VECTOR_H
