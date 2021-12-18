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
            drawMapSquare(i, j);
        }
    }
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

void MapDrawer::drawMapSquare(int i, int j) {

    SDL_SetRenderDrawColor (renderer , 100, 255, 0, 255 );

    if(i == map->mapSizeX / 2 && j == map->mapSizeY / 2)
    {
        SDL_SetRenderDrawColor (renderer , 255, 0, 0, 255 );
    }

    Coordinate ne = map->mapSquares[i][j]->northEastCorner;
    Coordinate nw = map->mapSquares[i][j]->northWestCorner;
    Coordinate se = map->mapSquares[i][j]->southEastCorner;
    Coordinate sw = map->mapSquares[i][j]->southWestCorner;

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
    SDL_RenderDrawLine(renderer, sw.x, sw.y, se.x, se.y);
    SDL_RenderDrawLine(renderer, nw.x, nw.y, ne.x, ne.y);
    SDL_RenderDrawLine(renderer, ne.x, ne.y, se.x, se.y);
}

void MapDrawer::applyRotation(Coordinate* coord) {

    double cx = coord->x - centralPoint.x;
    double cy = coord->y - centralPoint.y;

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

/*
 * 
 *     int leftIsoX1 = (left.a.x - left.a.y);
    int leftIsoY1 = ((left.a.x + left.a.y) / 2) - left.a.z;
    int left.b.x = (left.b.x - left.b.y);
    int left.b.y = ((left.b.x + left.b.y) / 2) - left.b.z;
    SDL_RenderDrawLine(r, leftIsoX1 + offsetX, leftIsoY1 + offsetY, left.b.x + offsetX, left.b.y + offsetY);

    int bottomIsoX1 = (bottom.a.x - bottom.a.y);
    int bottomIsoY1 = ((bottom.a.x + bottom.a.y) / 2) - bottom.a.z;
    int bottom.b.x = (bottom.b.x - bottom.b.y);
    int bottom.b.y = ((bottom.b.x + bottom.b.y) / 2) - bottom.b.z;
    SDL_RenderDrawLine(r, bottomIsoX1 + offsetX , bottomIsoY1 + offsetY, bottom.b.x + offsetX, bottom.b.y + offsetY);

    int topIsoX1 = (top.a.x - top.a.y);
    int topIsoY1 = ((top.a.x + top.a.y) / 2) - top.a.z;
    int top.b.x = (top.b.x - top.b.y) ;
    int top.b.y = ((top.b.x + top.b.y) / 2) - top.b.z;
    SDL_RenderDrawLine(r, topIsoX1 + offsetX, topIsoY1 + offsetY, top.b.x + offsetX, top.b.y + offsetY);

    int rightIsoX1 = (right.a.x - right.a.y) ;
    int rightIsoY1 = ((right.a.x + right.a.y) / 2) - right.a.z;
    int right.b.x = (right.b.x - right.b.y);
    int right.b.y = ((right.b.x + right.b.y) / 2) - right.b.z;
    SDL_RenderDrawLine(r, rightIsoX1 + offsetX, rightIsoY1 + offsetY, right.b.x + offsetX, right.b.y + offsetY);
 */