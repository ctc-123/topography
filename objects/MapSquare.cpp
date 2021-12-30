//
// Created by ct_co on 01/02/2021.
//

#include "MapSquare.h"


void MapSquare::updateTraversalPaths() {

    double approxNorth = (northWest.z + northEast.z) / 2;
    double approxEast = (northEast.z + southEast.z) / 2;
    double approxSouth = (southWest.z + southEast.z) / 2;
    double approxWest = (northWest.z + southWest.z) / 2;


    traversals.directionToSpeedMap.at(TraversalVectors::vectorN_S) = approxNorth - approxSouth;
    traversals.directionToSpeedMap.at(TraversalVectors::vectorS_N) = approxSouth - approxNorth;
    traversals.directionToSpeedMap.at(TraversalVectors::vectorNE_SW) = northEast.z - southWest.z;
    traversals.directionToSpeedMap.at(TraversalVectors::vectorSW_NE) = southWest.z - northEast.z;
    traversals.directionToSpeedMap.at(TraversalVectors::vectorE_W) = approxEast - approxWest;
    traversals.directionToSpeedMap.at(TraversalVectors::vectorW_E) = approxWest - approxEast;
    traversals.directionToSpeedMap.at(TraversalVectors::vectorSE_NW) =southEast.z - northWest.z;
    traversals.directionToSpeedMap.at(TraversalVectors::vectorNW_SE) = northWest.z - southEast.z;

}

MapSquare::MapSquare(Coordinate &ne, Coordinate &nw, Coordinate &se, Coordinate &sw, double aCentralX, double aCentralY)
                    : northEast(ne), northWest(nw), southEast(se), southWest(sw), centralX(aCentralX), centralY(aCentralY) {
    updateTraversalPaths();
}
