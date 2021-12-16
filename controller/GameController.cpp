//
// Created by ct_co on 07/12/2021.
//

#include "GameController.h"

#include <utility>

GameController::GameController() {

}

void GameController::setInputHandler(InputHandler *_inputHandler) {
    inputHandler = _inputHandler;
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
