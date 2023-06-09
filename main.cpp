#include "objects/Map.h"
#include "SDL.h"
#include "controller/InputHandler.h"
#include "controller/GameController.h"


void destroySDL(SDL_Window *window){
    SDL_DestroyWindow(window);
    SDL_Quit();
}



int SDL_main(int argc, char *argv[])
{

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    int mapSizeX = 50;
    int mapSizeY = 50;
    std::string mapName = "C:\\dev\\topography\\mapfiles\\map.csv";

    SDL_Init ( SDL_INIT_VIDEO );
    SDL_Window *window = SDL_CreateWindow ( "MAP SQUARES", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
    SDL_Renderer *renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_SOFTWARE );

    //ensure traversal vectors is init - this is a bit hacky?
    TraversalVectors();
    Map map(mapSizeX, mapSizeY);
    //Map map(mapName);

    InputHandler inputHandler;
    GameController gameController;
    UnitManager unitManager(2000, map.mapSizeX);
    MapDrawer mapDrawer(renderer, &map, &unitManager, SCREEN_WIDTH, SCREEN_HEIGHT);

    unitManager.init(&map);
    gameController.setMap(&map);
    gameController.setMapDrawer(&mapDrawer);
    gameController.setUnitManager(&unitManager);
    inputHandler.setGameController(&gameController);



    bool is_running = true;

    Uint64 ticks = 0;

    SDL_RenderClear ( renderer );
    while ( is_running )
    {
        ticks = SDL_GetTicks64();
        SDL_Event event;
        while ( SDL_PollEvent( &event ))
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

        gameController.update();

        mapDrawer.drawMap();

        /* DEBUG - draw cross-hair
        SDL_SetRenderDrawColor (renderer , 255, 0, 0, 255 );
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
        */

        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent ( renderer );

        Uint64 elapsedTicks = SDL_GetTicks64() - ticks;
        if(elapsedTicks < 10){
            SDL_Delay(10 - elapsedTicks);
        }

        SDL_SetRenderDrawColor ( renderer,0,0,0,255 );
        SDL_RenderClear ( renderer );


    }

    SDL_Quit ();

    destroySDL(window);

    return 0;

}
