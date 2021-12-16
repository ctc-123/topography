//
// Created by ct_co on 07/12/2021.
//

#include "InputHandler.h"

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
}

void InputHandler::handleMouseClick(SDL_MouseButtonEvent &event) {
    if(event.type ==  SDL_MOUSEBUTTONDOWN){

    }
}

void InputHandler::handleKeyboardEvent(SDL_KeyboardEvent &event) {
    if(event.type ==  SDL_KEYDOWN){
        SDL_Keysym key = event.keysym;
        if(key.scancode == SDL_SCANCODE_LEFT){
            gameController->rotateLeft();
        }
        else if(key.scancode == SDL_SCANCODE_RIGHT){
            gameController->rotateRight();
        }
    }
}
