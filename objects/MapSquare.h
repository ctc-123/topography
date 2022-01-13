//
// Created by ct_co on 01/02/2021.
//


#ifndef TOPOGRAPHY_MAPSQUARE_H
#define TOPOGRAPHY_MAPSQUARE_H

#include <vector>
#include "Coordinate.h"
#include "../data/TraversalVectors.h"


struct Heights{
    int ne;
    int nw;
    int se;
    int sw;
};

class MapSquare {

public:
    int speed = 0;
    bool hasUpdatedPath = false;
    const int UID;
    Coordinate centre;
    Heights heights{};
    TraversalVectors::VectorDirection directionToTarget = TraversalVectors::vectorS_N;

    void calculateCentralHeight();
    MapSquare() : UID(0), centre(0,0,0){};
    MapSquare(Coordinate &aCentre, int aUID);

};

#endif //TOPOGRAPHY_MAPSQUARE_H

