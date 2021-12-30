//
// Created by ct_co on 22/12/2021.
//


#include "MapSquareTraversals.h"


MapSquareTraversals::MapSquareTraversals() {

    for (int i = 0; i < TraversalVectors::VectorDirection::LAST; ++i) {

        //initialise all direction speeds to 0
        auto direction = static_cast<TraversalVectors::VectorDirection>(i);
        directionToSpeedMap.emplace(direction, 0);
    }


}
