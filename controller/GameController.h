//
// Created by ct_co on 07/12/2021.
//

#ifndef TOPOGRAPHY_GAMECONTROLLER_H
#define TOPOGRAPHY_GAMECONTROLLER_H


#include "../objects/Map.h"
#include "../draw/MapDrawer.h"
#include "../data/DataTypes.h"
#include "../data/ButtonMap.h"

class MapDrawer;

class GameController {

public:
    GameController();

    Map *map;
    MapDrawer *mapDrawer;
    UnitManager *unitManager;

    void setMap(Map *_map);
    void setMapDrawer(MapDrawer *_mapDrawer);
    void setUnitManager(UnitManager *aUnitManager);

    void rotateLeft();
    void rotateRight();
    void setButtonPressed(ButtonMap::button button);
    void setButtonReleased(ButtonMap::button button);
    void increaseZoom();
    void decreaseZoom();

    void update();

    void togglePaused();

private:
    void changeSquareHeight(DataTypes::Direction direction);
    void moveMapSelection(DataTypes::Direction direction);
    bool moveSelectionLeftPressed = false;
    bool moveSelectionRightPressed = false;
    bool moveSelectionUpPressed = false;
    bool moveSelectionDownPressed = false;
    bool raiseSelectionPressed = false;
    bool lowerSelectionPressed = false;
    bool paused = false;


};


#endif //TOPOGRAPHY_GAMECONTROLLER_H
