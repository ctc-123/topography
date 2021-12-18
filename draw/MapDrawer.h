//
// Created by ct_co on 01/08/2021.
//

#ifndef TOPOGRAPHY_MAPDRAWER_H
#define TOPOGRAPHY_MAPDRAWER_H

#include <SDL_render.h>
#include "../objects/MapSquare.h"
#include "../objects/Map.h"

class MapDrawer {

public:
    SDL_Renderer* renderer;
    Map* map;
    int screenSizeX = 0;
    int screenSizeY = 0;
    int baseTileSize = 0;
    int tileSize = 0;
    int offsetFromEdge = 0;
    int offsetFromEdgeX = 0;
    int offsetFromEdgeY = 0;
    double zoomScale = 1.0;
    Coordinate centralPoint;

    MapDrawer(SDL_Renderer *r, Map *aMap , int aScreenSizeX, int aScreenSizeY);
    void drawMap();
    void increaseZoom();
    void decreaseZoom();

private:
    void applyRotation(Coordinate *coord);
    void drawMapSquare(int i, int j);

};


#endif //TOPOGRAPHY_MAPDRAWER_H
