//
// Created by ct_co on 07/12/2021.
//

#include "GameController.h"
#include "../draw/MapDrawer.h"



GameController::GameController() {

}

void GameController::changeSquareHeight(DataTypes::Direction direction){
    map->changeSquareHeight(direction);
}

void GameController::increaseZoom(){
    mapDrawer->increaseZoom();
}

void GameController::decreaseZoom(){
    mapDrawer->decreaseZoom();
}

void GameController::rotateLeft() {
    map->rotateLeft();
}

void GameController::rotateRight() {
    map->rotateRight();
}

void GameController::moveMapSelection(DataTypes::Direction direction) {
    map->moveSelectedSquare(direction);
}

void GameController::setMapDrawer(MapDrawer *_mapDrawer){
    mapDrawer = _mapDrawer;
}

void GameController::setMap(Map *_map) {
    map = _map;
}
