//
// Created by ct_co on 07/12/2021.
//

#include "GameController.h"
#include "../draw/MapDrawer.h"



GameController::GameController() {

}

void GameController::update(){

    doTick();

    if(state == DataTypes::RUNNING){

        if(updateRequired){
            if(moveSelectionLeftPressed){moveMapSelection(DataTypes::LEFT);}
            if(moveSelectionRightPressed){moveMapSelection(DataTypes::RIGHT);}
            if(moveSelectionUpPressed){moveMapSelection(DataTypes::UP);}
            if(moveSelectionDownPressed){moveMapSelection(DataTypes::DOWN);}
            if(raiseSelectionPressed){changeSquareHeight(DataTypes::UP);}
            if(lowerSelectionPressed){changeSquareHeight(DataTypes::DOWN);}
        }
        updateRequired = false;
        unitManager->update(map);
        rotateRight();
    }
}

void GameController::doTick(){
    tick++;
    if(tick >= updatePerTick){
        tick = 0;
        updateRequired = true;
    }
}

void GameController::setButtonPressed(ButtonMap::button button){
    switch (button) {
        case ButtonMap::MOVE_SELECTION_UP :
            moveSelectionUpPressed = true;
            break;
        case ButtonMap::MOVE_SELECTION_DOWN :
            moveSelectionDownPressed = true;
            break;
        case ButtonMap::MOVE_SELECTION_LEFT :
            moveSelectionLeftPressed = true;
            break;
        case ButtonMap::MOVE_SELECTION_RIGHT :
            moveSelectionRightPressed = true;
            break;
        case ButtonMap::RAISE_SELECTION :
            raiseSelectionPressed = true;
            break;
        case ButtonMap::LOWER_SELECTION :
            lowerSelectionPressed = true;
            break;
    }
}

void GameController::setButtonReleased(ButtonMap::button button){
    switch (button) {
        case ButtonMap::MOVE_SELECTION_UP :
            moveSelectionUpPressed = false;
            break;
        case ButtonMap::MOVE_SELECTION_DOWN :
            moveSelectionDownPressed = false;
            break;
        case ButtonMap::MOVE_SELECTION_LEFT :
            moveSelectionLeftPressed = false;
            break;
        case ButtonMap::MOVE_SELECTION_RIGHT :
            moveSelectionRightPressed = false;
            break;
        case ButtonMap::RAISE_SELECTION :
            raiseSelectionPressed = false;
            break;
        case ButtonMap::LOWER_SELECTION :
            lowerSelectionPressed = false;
            break;
    }
}

void GameController::togglePaused(){
    if(state == DataTypes::RUNNING){
        setState(DataTypes::PAUSED);
    }
    else if(state == DataTypes::PAUSED){
        setState(DataTypes::RUNNING);
    }

}

void GameController::setState(DataTypes::GameState aState){
    state = aState;
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
    mapDrawer->rotateLeft();
}

void GameController::rotateRight() {
    mapDrawer->rotateRight();
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

void GameController::setUnitManager(UnitManager *aUnitManager) {
    unitManager = aUnitManager;
}

