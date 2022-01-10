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
    Coordinate centre;
    const int UID;
    Heights heights{};
    TraversalVectors::VectorDirection directionToTarget = TraversalVectors::vectorS_N;
    bool hasUpdatedPath = false;

    inline bool operator<(MapSquare& rhs){return UID < rhs.UID;};
    inline bool operator==(MapSquare& rhs){return UID == rhs.UID;};


    void calculateCentralHeight();
    MapSquare() : UID(0), centre(0,0,0){};
    MapSquare(Coordinate &aCentre, int aUID);

};


class MapSquareHash {
public:
    size_t operator()(const MapSquare& mapSquare) const{
        return mapSquare.UID;
    }
};






#endif //TOPOGRAPHY_MAPSQUARE_H

