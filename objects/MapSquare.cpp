//
// Created by ct_co on 01/02/2021.
//

#include <cmath>
#include "MapSquare.h"


MapSquare::MapSquare(Coordinate &aCentre, int aUID) :  centre(aCentre), UID(aUID){
    heights.nw = centre.z;
    heights.ne = centre.z;
    heights.se = centre.z;
    heights.sw = centre.z;
}

void MapSquare::calculateCentralHeight() {
    centre.z = floor( (heights.ne + heights.nw + heights.se + heights.sw) / 4);
}

