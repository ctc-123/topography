//
// Created by ct_co on 01/08/2021.
//

#ifndef TOPOGRAPHY_MAPDRAWER_H
#define TOPOGRAPHY_MAPDRAWER_H


#include "../objects/MapSquare.h"
#include "../objects/Map.h"

class MapDrawer {
private:

public:
    SDL_Renderer* renderer;
    Map* map;
    int screenSizeX = 0;
    int screenSizeY = 0;
    int TILE_SIZE = 0;
    int offsetFromEdge = 0;
    int offsetFromEdgeX = 0;
    int offsetFromEdgeY = 0;
    Coordinate centralPoint;

    MapDrawer(SDL_Renderer *r, Map *aMap , int aScreenSizeX, int aScreenSizeY);;
    void drawMap();

private:
    void applyRotation(Coordinate *coord);
    void drawMapSquare(int i, int j);

    void centreOnScreen(Coordinate *ne, Coordinate *nw, Coordinate *se, Coordinate *sw);
};


#endif //TOPOGRAPHY_MAPDRAWER_H
