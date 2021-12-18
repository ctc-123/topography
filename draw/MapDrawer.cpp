//
// Created by ct_co on 01/08/2021.
//

#include <SDL_render.h>
#include "MapDrawer.h"
#include "../objects/Line.h"
#include <cmath>

void MapDrawer::drawMap() {
    for(int i = 0; i < map->mapSizeX; i++)
    {
        for (int j = 0; j < map->mapSizeY; ++j)
        {
            drawMapSquare(i, j, mapColour);
        }
    }
    drawSelectedSquare();

}

void MapDrawer::drawSelectedSquare(){
    SDL_SetRenderDrawColor (renderer , selectedSquareColour.r, selectedSquareColour.g, selectedSquareColour.b, selectedSquareColour.a);
    Coordinate ne = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->northEastCorner;
    Coordinate nw = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->northWestCorner;
    Coordinate se = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->southEastCorner;
    Coordinate sw = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->southWestCorner;

    nw.x = (nw.x * tileSize) + offsetFromEdgeX;
    nw.y = (nw.y * tileSize) + offsetFromEdgeY;
    ne.x = (ne.x * tileSize) + offsetFromEdgeX;
    ne.y = (ne.y * tileSize) + offsetFromEdgeY;
    se.x = (se.x * tileSize) + offsetFromEdgeX;
    se.y = (se.y * tileSize) + offsetFromEdgeY;
    sw.x = (sw.x * tileSize) + offsetFromEdgeX;
    sw.y = (sw.y * tileSize) + offsetFromEdgeY;

    applyRotation(&ne);
    applyRotation(&nw);
    applyRotation(&se);
    applyRotation(&sw);

    SDL_RenderDrawLine(renderer, nw.x, nw.y, sw.x, sw.y);
    SDL_RenderDrawLine(renderer, nw.x, nw.y, ne.x, ne.y);
    SDL_RenderDrawLine(renderer, sw.x, sw.y, se.x, se.y);
    SDL_RenderDrawLine(renderer, ne.x, ne.y, se.x, se.y);
}

void MapDrawer::drawMapSquare(int i, int j, SDL_Color colour) {

    SDL_SetRenderDrawColor (renderer , colour.r, colour.g, colour.b, colour.a);

    Coordinate ne = map->mapSquares[i][j]->northEastCorner;
    Coordinate nw = map->mapSquares[i][j]->northWestCorner;
    Coordinate sw = map->mapSquares[i][j]->southWestCorner;

    nw.x = (nw.x * tileSize) + offsetFromEdgeX;
    nw.y = (nw.y * tileSize) + offsetFromEdgeY;
    ne.x = (ne.x * tileSize) + offsetFromEdgeX;
    ne.y = (ne.y * tileSize) + offsetFromEdgeY;
    sw.x = (sw.x * tileSize) + offsetFromEdgeX;
    sw.y = (sw.y * tileSize) + offsetFromEdgeY;

    applyRotation(&ne);
    applyRotation(&nw);
    applyRotation(&sw);

    SDL_RenderDrawLine(renderer, nw.x, nw.y, sw.x, sw.y);
    SDL_RenderDrawLine(renderer, nw.x, nw.y, ne.x, ne.y);

    //only need to draw if at south and east edges - otherwise already drawn
    if(i == map->mapSizeX - 1|| j == map->mapSizeY - 1){
        Coordinate se = map->mapSquares[i][j]->southEastCorner;
        se.x = (se.x * tileSize) + offsetFromEdgeX;
        se.y = (se.y * tileSize) + offsetFromEdgeY;

        applyRotation(&se);
        SDL_RenderDrawLine(renderer, sw.x, sw.y, se.x, se.y);
        SDL_RenderDrawLine(renderer, ne.x, ne.y, se.x, se.y);
    }
}

void MapDrawer::applyRotation(Coordinate* coord) {

    double cx = coord->x - centralPoint.x;
    double cy = coord->y - centralPoint.y;

    //TODO calculate these once for each rotation angle change
    double cos_rot = cos(map->rotationAngle);
    double sin_rot = sin(map->rotationAngle);

    //rotate
    double rx = (cx * cos_rot) - (cy * sin_rot);
    double ry = (cx * sin_rot) + (cy * cos_rot);

    //make isometric
    double px = (rx - ry);
    double py = ((rx + ry)  / 2) - coord->z;
    coord->x = px  + centralPoint.x;
    coord->y = py + centralPoint.y;
}

void MapDrawer::increaseZoom() {
    zoomScale += 0.1;
    if(zoomScale >= 4.0){
        zoomScale = 4.0;
    }
    tileSize = baseTileSize * zoomScale;
    offsetFromEdgeX = (screenSizeX - (map->mapSizeX * tileSize)) / 2;
    offsetFromEdgeY = (screenSizeY - (map->mapSizeY * tileSize)) / 2;
}

void MapDrawer::decreaseZoom(){
    zoomScale -= 0.1;
    if(zoomScale <= 0.2){
        zoomScale = 0.2;
    }
    tileSize = baseTileSize * zoomScale;
    offsetFromEdgeX = (screenSizeX - (map->mapSizeX * tileSize)) / 2;
    offsetFromEdgeY = (screenSizeY - (map->mapSizeY * tileSize)) / 2;
}

MapDrawer::MapDrawer(SDL_Renderer *r, Map *aMap, int aScreenSizeX, int aScreenSizeY) : renderer(r), map(aMap), screenSizeX(aScreenSizeX), screenSizeY(aScreenSizeY)
{
    auto sx = static_cast<double>(screenSizeX);
    auto sy = static_cast<double>(screenSizeY);

    if(screenSizeY > screenSizeX){
        baseTileSize = (screenSizeX / aMap->mapSizeX) * 0.5;
    }else{
        baseTileSize = (screenSizeY / aMap->mapSizeY) * 0.9;
    }

    offsetFromEdgeX = (screenSizeX - (map->mapSizeX * baseTileSize)) / 2;
    offsetFromEdgeY = (screenSizeY - (map->mapSizeY * baseTileSize)) / 2;
    tileSize = baseTileSize;
    centralPoint.x = ceil(sx / 2);
    centralPoint.y = ceil(sy / 2);

}
