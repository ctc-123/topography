//
// Created by ct_co on 07/12/2021.
//

#include "InputHandler.h"
#include "../data/DataTypes.h"


void InputHandler::setGameController(GameController *_gameController) {
    gameController = _gameController;
}


void InputHandler::handleInput(SDL_Event &event) {
    if(event.type == SDL_MOUSEBUTTONDOWN ||
        event.type == SDL_MOUSEBUTTONUP){
        handleMouseClick(event.button);
    }
    else if(event.type == SDL_KEYDOWN){
        handleKeyboardEvent(event.key);
    }
    else if(event.type == SDL_MOUSEWHEEL){
        handleScrollEvent(event.wheel);
    }
}

void InputHandler::handleScrollEvent(SDL_MouseWheelEvent event){
    if(event.y > 0)
    {
        gameController->increaseZoom();
    }
    else if(event.y < 0)
    {
        gameController->decreaseZoom();
    }
}

void InputHandler::handleMouseClick(SDL_MouseButtonEvent &event) {
    if(event.type ==  SDL_MOUSEBUTTONDOWN){

    }
}

void InputHandler::handleKeyboardEvent(SDL_KeyboardEvent &event) {
    if(event.type ==  SDL_KEYDOWN){
        SDL_Keysym key = event.keysym;
        if(key.scancode == SDL_SCANCODE_LEFT){
            gameController->moveMapSelection(DataTypes::Direction::LEFT);
        }
        else if(key.scancode == SDL_SCANCODE_RIGHT){
            gameController->moveMapSelection(DataTypes::Direction::RIGHT);
        }
        else if(key.scancode == SDL_SCANCODE_DOWN){
            gameController->moveMapSelection(DataTypes::Direction::DOWN);
        }
        else if(key.scancode == SDL_SCANCODE_UP){
            gameController->moveMapSelection(DataTypes::Direction::UP);
        }
    }
}
