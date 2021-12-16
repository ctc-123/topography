#include <iostream>
#include "objects/Map.h"
#include "SDL.h"
#include "controller/InputHandler.h"
#include "controller/GameController.h"
#include "draw/MapDrawer.h"


void destroySDL(SDL_Window *window){
    SDL_DestroyWindow(window);
    SDL_Quit();
}



int SDL_main(int argc, char *argv[])
{

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    SDL_Init ( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow ( "MAP SQUARES", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    SDL_Renderer *renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_SOFTWARE );

    int mapSizeX = 20;
    int mapSizeY = 20;

    Map map(mapSizeX, mapSizeY);
    MapDrawer mapDrawer(renderer, &map, SCREEN_WIDTH, SCREEN_HEIGHT);
    InputHandler inputHandler;
    GameController gameController;


    gameController.setInputHandler(&inputHandler);
    gameController.setMap(&map);
    inputHandler.setGameController(&gameController);



    bool is_running = true;

    SDL_RenderClear ( renderer );
    while ( is_running )
    {
        SDL_Event event;
        if ( SDL_PollEvent( &event ))
        {
            if ( event.type == SDL_QUIT )
            {
                is_running = false;
            }
            else
            {
                inputHandler.handleInput(event);
            }
        }

        mapDrawer.drawMap();


        map.rotateRight();
        SDL_SetRenderDrawColor (renderer , 255, 0, 0, 255 );
        SDL_RenderDrawLine(renderer, 0, 540,1920, 540);
        SDL_RenderDrawLine(renderer, 960, 0, 960, 1080);

        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent ( renderer );

        SDL_Delay(50);

        SDL_SetRenderDrawColor ( renderer, 1, 1, 1, 255 );
        SDL_RenderClear ( renderer );


    }

    SDL_Quit ();

    destroySDL(window);

    return 0;

}
