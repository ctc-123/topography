//
// Created by ct_co on 07/12/2021.
//

#include "GameController.h"
#include "../draw/MapDrawer.h"


GameController::GameController() {

}

void GameController::setMapDrawer(MapDrawer *_mapDrawer){
    mapDrawer = _mapDrawer;
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

void GameController::setMap(Map *_map) {
    map = _map;
}
