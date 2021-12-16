//
// Created by ct_co on 07/12/2021.
//

#ifndef TOPOGRAPHY_GAMECONTROLLER_H
#define TOPOGRAPHY_GAMECONTROLLER_H


#include "../objects/Map.h"
#include "InputHandler.h"

class InputHandler;

class GameController {


public:

    GameController();

    Map *map;
    InputHandler *inputHandler;

    void setMap(Map *_map);
    void setInputHandler(InputHandler *_inputHandler);

    void rotateLeft();
    void rotateRight();
};


#endif //TOPOGRAPHY_GAMECONTROLLER_H
