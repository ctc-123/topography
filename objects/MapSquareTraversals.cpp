//
// Created by ct_co on 22/12/2021.
//

#include <map>
#include "MapSquareTraversals.h"
#include "VectorPath.h"


MapSquareTraversals::MapSquareTraversals() {

    for (int i = 0; i < TraversalVectors::VectorDirection::LAST; ++i) {
        TraversalVectors::VectorDirection direction = static_cast<TraversalVectors::VectorDirection>(i);
        vectorMap.insert(direction, TraversalVectors::vectors.at(direction));


    }


}
