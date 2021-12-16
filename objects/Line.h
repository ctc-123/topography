//
// Created by ct_co on 26/11/2021.
//

#ifndef TOPOGRAPHY_LINE_H
#define TOPOGRAPHY_LINE_H


#include "Coordinate.h"

class Line {

public:
    Coordinate a;
    Coordinate b;
    Line(Coordinate _a, Coordinate _b) : a(_a), b(_b){};

};


#endif //TOPOGRAPHY_LINE_H
