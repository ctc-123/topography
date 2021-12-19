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
        handleKeyboardEventDown(event.key);
    }
    else if(event.type == SDL_KEYUP){
        handleKeyboardEventUp(event.key);
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

void InputHandler::handleKeyboardEventUp(SDL_KeyboardEvent &event){
    SDL_Keysym key = event.keysym;
    if(key.scancode == SDL_SCANCODE_LEFT){
        gameController->setButtonReleased(ButtonMap::MOVE_SELECTION_LEFT);
    }
    else if(key.scancode == SDL_SCANCODE_RIGHT){
        gameController->setButtonReleased(ButtonMap::MOVE_SELECTION_RIGHT);
    }
    else if(key.scancode == SDL_SCANCODE_DOWN){
        gameController->setButtonReleased(ButtonMap::MOVE_SELECTION_DOWN);
    }
    else if(key.scancode == SDL_SCANCODE_UP){
        gameController->setButtonReleased(ButtonMap::MOVE_SELECTION_UP);
    }
    else if(key.scancode == SDL_SCANCODE_SPACE){
        gameController->setButtonReleased(ButtonMap::RAISE_SELECTION);
    }
    else if(key.scancode == SDL_SCANCODE_LCTRL){
        gameController->setButtonReleased(ButtonMap::LOWER_SELECTION);
    }
}

void InputHandler::handleKeyboardEventDown(SDL_KeyboardEvent &event) {
    SDL_Keysym key = event.keysym;

    if(key.scancode == SDL_SCANCODE_LEFT){
        gameController->setButtonPressed(ButtonMap::MOVE_SELECTION_LEFT);
    }
    else if(key.scancode == SDL_SCANCODE_RIGHT){
        gameController->setButtonPressed(ButtonMap::MOVE_SELECTION_RIGHT);
    }
    else if(key.scancode == SDL_SCANCODE_DOWN){
        gameController->setButtonPressed(ButtonMap::MOVE_SELECTION_DOWN);
    }
    else if(key.scancode == SDL_SCANCODE_UP){
        gameController->setButtonPressed(ButtonMap::MOVE_SELECTION_UP);
    }
    else if(key.scancode == SDL_SCANCODE_SPACE){
        gameController->setButtonPressed(ButtonMap::RAISE_SELECTION);
    }
    else if(key.scancode == SDL_SCANCODE_LCTRL){
        gameController->setButtonPressed(ButtonMap::LOWER_SELECTION);
    }

}
