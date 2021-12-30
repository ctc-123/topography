//
// Created by ct_co on 22/12/2021.
//

#ifndef TOPOGRAPHY_MAPSQUARETRAVERSALS_H
#define TOPOGRAPHY_MAPSQUARETRAVERSALS_H

#include "../data/TraversalVectors.h"
#include "Vector.h"

class MapSquareTraversals {

public:
    std::map<TraversalVectors::VectorDirection, double> directionToSpeedMap;
    MapSquareTraversals();

};


#endif //TOPOGRAPHY_MAPSQUARETRAVERSALS_H
