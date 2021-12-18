//
// Created by ct_co on 01/02/2021.
//


#ifndef TOPOGRAPHY_MAPSQUARE_H
#define TOPOGRAPHY_MAPSQUARE_H

#include "Coordinate.h"

class MapSquare {

public:
    Coordinate northEastCorner;
    Coordinate northWestCorner;
    Coordinate southEastCorner;
    Coordinate southWestCorner;
    MapSquare(Coordinate &ne, Coordinate &nw, Coordinate &se, Coordinate &sw) : northEastCorner(ne), northWestCorner(nw), southEastCorner(se), southWestCorner(sw) {

    }

private:

};






#endif //TOPOGRAPHY_MAPSQUARE_H
