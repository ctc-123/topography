//
// Created by ct_co on 01/08/2021.
//

#ifndef TOPOGRAPHY_MAPDRAWER_H
#define TOPOGRAPHY_MAPDRAWER_H

#include <SDL_render.h>
#include <cmath>
#include "../objects/MapSquare.h"
#include "../objects/Map.h"
#include "../controller/UnitManager.h"

class MapDrawer {

public:
    SDL_Renderer* renderer;
    Map* map;
    UnitManager* unitManager;
    int screenSizeX = 0;
    int screenSizeY = 0;
    int baseTileSize = 0;
    int tileSize = 0;
    int offsetFromEdgeX = 0;
    int offsetFromEdgeY = 0;
    double zoomScale = 1.0;
    Coordinate centralPoint;

    SDL_Color unitColour{255, 0, 0, 0};
    SDL_Color mapColour{0, 255,0,255};
    SDL_Color selectedSquareColour{255, 0, 0, 0};

    MapDrawer(SDL_Renderer *r, Map *aMap, UnitManager* aUnitManager, int aScreenSizeX, int aScreenSizeY);
    void drawMap();
    void increaseZoom();
    void decreaseZoom();
    void rotateRight();
    void rotateLeft();

private:
    double rotationAngle = 0.1;
    double rotationAngleCos = cos(rotationAngle);
    double rotationAngleSin = sin(rotationAngle);
    void applyRotation(Coordinate *coord);
    void drawMapSquare(MapSquare *mapSquare);

    void drawSelectedSquare();

    void fillSpace(Coordinate *ne, Coordinate *nw, Coordinate *se, Coordinate *sw);

    void drawUnit(Unit *unit);

    void drawTargetSquare();
};


#endif //TOPOGRAPHY_MAPDRAWER_H
