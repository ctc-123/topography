//
// Created by ct_co on 07/12/2021.
//

#ifndef TOPOGRAPHY_GAMECONTROLLER_H
#define TOPOGRAPHY_GAMECONTROLLER_H


#include "../objects/Map.h"
#include "../draw/MapDrawer.h"
#include "../data/DataTypes.h"

class MapDrawer;

class GameController {

public:
    GameController();

    Map *map;
    MapDrawer *mapDrawer;

    void setMap(Map *_map);
    void setMapDrawer(MapDrawer *_mapDrawer);

    void moveMapSelection(DataTypes::Direction direction);
    void rotateLeft();
    void rotateRight();
    void increaseZoom();
    void decreaseZoom();
};


#endif //TOPOGRAPHY_GAMECONTROLLER_H
