//
// Created by ct_co on 22/12/2021.
//

#ifndef TOPOGRAPHY_MAPSQUARETRAVERSALS_H
#define TOPOGRAPHY_MAPSQUARETRAVERSALS_H

#include "../data/TraversalVectors.h"
#include "VectorPath.h"

class MapSquareTraversals {

    std::map<TraversalVectors::VectorDirection, VectorPath> vectorMap;
    MapSquareTraversals();

};


#endif //TOPOGRAPHY_MAPSQUARETRAVERSALS_H
