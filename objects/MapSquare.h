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
    MapSquareTraversals traversals;



    MapSquare(Coordinate &ne, Coordinate &nw, Coordinate &se, Coordinate &sw) : northEast(ne), northWest(nw), southEast(se), southWest(sw) {

    }

    void updateTraversalPaths();

private:

};






#endif //TOPOGRAPHY_MAPSQUARE_H

