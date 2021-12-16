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

void MapDrawer::drawMapSquare(int i, int j) {

    SDL_SetRenderDrawColor (renderer , 100, 255, 0, 255 );

    Coordinate ne = map->mapSquares[i][j]->northEastCorner;
    Coordinate nw = map->mapSquares[i][j]->northWestCorner;
    Coordinate se = map->mapSquares[i][j]->southEastCorner;
    Coordinate sw = map->mapSquares[i][j]->southWestCorner;

    nw.x = (nw.x * TILE_SIZE) + offsetFromEdgeX;
    nw.y = (nw.y * TILE_SIZE) + offsetFromEdgeY;
    ne.x = (ne.x * TILE_SIZE) + offsetFromEdgeX;
    ne.y = (ne.y * TILE_SIZE) + offsetFromEdgeY;
    se.x = (se.x * TILE_SIZE) + offsetFromEdgeX;
    se.y = (se.y * TILE_SIZE) + offsetFromEdgeY;
    sw.x = (sw.x * TILE_SIZE) + offsetFromEdgeX;
    sw.y = (sw.y * TILE_SIZE) + offsetFromEdgeY;

    applyRotation(&ne);
    applyRotation(&nw);
    applyRotation(&se);
    applyRotation(&sw);

    SDL_RenderDrawLine(renderer, nw.x, nw.y, sw.x, sw.y);
    SDL_RenderDrawLine(renderer, sw.x, sw.y, se.x, se.y);
    SDL_RenderDrawLine(renderer, nw.x, nw.y, ne.x, ne.y);
    SDL_RenderDrawLine(renderer, ne.x, ne.y, se.x, se.y);
}

void MapDrawer::centreOnScreen(Coordinate* ne, Coordinate* nw, Coordinate* se, Coordinate* sw) {


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
    double py = ((rx + ry)  / 2);// - coord->z;
    coord->x = px  + centralPoint.x;
    coord->y = py + centralPoint.y;
}

MapDrawer::MapDrawer(SDL_Renderer *r, Map *aMap, int aScreenSizeX, int aScreenSizeY) : renderer(r), map(aMap), screenSizeX(aScreenSizeX), screenSizeY(aScreenSizeY)
{
    offsetFromEdgeX = 2 * (aScreenSizeX / 8);
    offsetFromEdgeY = 0.5625 * (aScreenSizeY / 8);

    if(screenSizeY > screenSizeX){
        offsetFromEdge = 2 * (screenSizeY/8);
        TILE_SIZE = (screenSizeX - (2 * offsetFromEdgeX)) / aMap->mapSizeX;
    }else{
        offsetFromEdge = 2 * (screenSizeX/8);
        TILE_SIZE = (screenSizeY - (2 * offsetFromEdgeY)) / aMap->mapSizeY;
    }


    centralPoint.x = 960;//(aMap->centralPoint.x * ((screenSizeX - (2 * offsetFromEdgeX)) / aMap->mapSizeX)) + offsetFromEdgeX;
    centralPoint.y = 540;//(aMap->centralPoint.y * ((screenSizeY - (2 * offsetFromEdgeY)) / aMap->mapSizeY)) + offsetFromEdgeY;

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