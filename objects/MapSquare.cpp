//
// Created by ct_co on 01/02/2021.
//

#include "MapSquare.h"


void MapSquare::updateTraversalPaths() {

    double approxNorth = (northWest.z + northEast.z) / 2;
    double approxEast = (northEast.z + southEast.z) / 2;
    double approxSouth = (southWest.z + southEast.z) / 2;
    double approxWest = (northWest.z + southWest.z) / 2;

    traversalPathNW_E = northWest.z - approxEast;
    traversalPathNW_SE = northWest.z - southEast.z;
    traversalPathNW_S = northWest.z - approxSouth;
    traversalPathN_W = approxNorth - approxWest;
    traversalPathN_SW = approxNorth - southWest.z;
    traversalPathN_S = approxNorth - approxSouth;
    traversalPathN_SE = approxNorth - southEast.z;
    traversalPathN_E = approxNorth - approxEast;
    traversalPathNE_W = northEast.z - approxWest;
    traversalPathNE_SW = northEast.z - southWest.z;
    traversalPathNE_S = northEast.z - approxSouth;
    traversalPathE_W = approxEast - approxWest;
    traversalPathE_SW = approxEast - southWest.z;
    traversalPathE_S = approxEast - approxSouth;
    traversalPathSE_W = southEast.z - approxWest;
    traversalPathS_W = approxSouth - approxWest;

}
