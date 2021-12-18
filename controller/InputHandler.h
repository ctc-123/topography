//
// Created by ct_co on 07/12/2021.
//

#ifndef TOPOGRAPHY_INPUTHANDLER_H
#define TOPOGRAPHY_INPUTHANDLER_H


#include <SDL_events.h>
#include "../objects/Map.h"
#include "GameController.h"

class GameController;

class InputHandler {

public:
    GameController *gameController;
    InputHandler(){};
    void handleInput(SDL_Event& event);
    void setGameController(GameController *_gameController);

private:
    void handleKeyboardEvent(SDL_KeyboardEvent& event);
    void handleMouseClick(SDL_MouseButtonEvent& event);

    void handleScrollEvent(SDL_MouseWheelEvent);
};


#endif //TOPOGRAPHY_INPUTHANDLER_H
