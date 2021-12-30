//
// Created by ct_co on 01/02/2021.
//


#ifndef TOPOGRAPHY_MAPSQUARE_H
#define TOPOGRAPHY_MAPSQUARE_H

#include "Coordinate.h"
#include "MapSquareTraversals.h"

class MapSquare {

public:
    Coordinate northEast;
    Coordinate northWest;
    Coordinate southEast;
    Coordinate southWest;
    double centralX;
    double centralY;
    MapSquareTraversals traversals;



    MapSquare(Coordinate &ne, Coordinate &nw, Coordinate &se, Coordinate &sw, double aCentralX, double aCentralY);

    void updateTraversalPaths();

private:

};






#endif //TOPOGRAPHY_MAPSQUARE_H

