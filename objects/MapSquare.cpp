//
// Created by ct_co on 01/02/2021.
//

#include <cmath>
#include "MapSquare.h"


MapSquare::MapSquare(Coordinate &aCentre, int aUID) :  centre(aCentre), UID(aUID){
    this->heights.nw = centre.z;
    this->heights.ne = centre.z;
    this->heights.se = centre.z;
    this->heights.sw = centre.z;
    this->heights.n = centre.z;
    this->heights.e = centre.z;
    this->heights.s = centre.z;
    this->heights.w = centre.z;
}

void MapSquare::update() {
    this->heights.n = (heights.nw + heights.ne) / 2;
    this->heights.e = (heights.ne + heights.se) / 2;
    this->heights.s = (heights.sw + heights.se) / 2;
    this->heights.w = (heights.nw + heights.sw) / 2;
    this->centre.z = floor((heights.ne + heights.nw + heights.se + heights.sw
            + heights.e + heights.w + heights.s + heights.n ) / 8.0);
}

