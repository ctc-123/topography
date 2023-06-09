//
// Created by ct_co on 13/01/2022.
//

#ifndef TOPOGRAPHY_MAPIOHANDLER_H
#define TOPOGRAPHY_MAPIOHANDLER_H


#include <string>
#include "../objects/MapSquare.h"

class MapIOHandler {

public:
    static std::vector<MapSquare> getMap(std::string &mapName, int &aMaxHeightDiff);
};


#endif //TOPOGRAPHY_MAPIOHANDLER_H
