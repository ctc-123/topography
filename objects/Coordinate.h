//
// Created by ct_co on 31/07/2021.
//

#ifndef TOPOGRAPHY_COORDINATE_H
#define TOPOGRAPHY_COORDINATE_H


class Coordinate {

public:
    double x;
    double y;
    double z;
    Coordinate(): x(0), y(0), z(0){};
    Coordinate(int _x, int _y, int _z) : x(_x), y(_y), z(_z){}

};


#endif //TOPOGRAPHY_COORDINATE_H
