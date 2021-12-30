//
// Created by ct_co on 01/08/2021.
//

#include <SDL_render.h>
#include "MapDrawer.h"
#include "../objects/Line.h"
#include <cmath>

void MapDrawer::drawMap() {

    for(std::vector<MapSquare*> row : map->mapSquares){
        for(MapSquare* mapSquare : row){
            drawMapSquare(mapSquare);
        }
    }

    for(Unit *unit : unitManager->units){
        drawUnit(unit);
    }

    drawSelectedSquare();


}

void MapDrawer::drawUnit(Unit *unit){
    SDL_SetRenderDrawColor (renderer , 255, 1, 255, 255);

    Coordinate unitLocation;
    unitLocation.x = unit->location.x;
    unitLocation.y = unit->location.y;
    unitLocation.x = (unitLocation.x * tileSize) + offsetFromEdgeX;
    unitLocation.y = (unitLocation.y * tileSize) + offsetFromEdgeY;

    applyRotation(&unitLocation);
    SDL_Rect rect;
    rect.x = unitLocation.x - 1;
    rect.y = unitLocation.y - 1;
    rect.h = 2;
    rect.w = 2;

    SDL_RenderDrawRect(renderer, &rect);
    //SDL_RenderDrawPoint(renderer, unitLocation.x, unitLocation.y);
}

void MapDrawer::drawSelectedSquare(){
    SDL_SetRenderDrawColor (renderer , selectedSquareColour.r, selectedSquareColour.g, selectedSquareColour.b, selectedSquareColour.a);
    Coordinate ne = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->northEast;
    Coordinate nw = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->northWest;
    Coordinate se = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->southEast;
    Coordinate sw = map->mapSquares[map->selectedSquareX][map->selectedSquareY]->southWest;

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

void MapDrawer::drawMapSquare(MapSquare *mapSquare) {

    SDL_SetRenderDrawColor (renderer , mapColour.r, mapColour.g, mapColour.b, mapColour.a);

    Coordinate ne = mapSquare->northEast;
    Coordinate nw = mapSquare->northWest;
    Coordinate se = mapSquare->southEast;
    Coordinate sw = mapSquare->southWest;

    nw.x = (nw.x * tileSize) + offsetFromEdgeX;
    nw.y = (nw.y * tileSize) + offsetFromEdgeY;
    ne.x = (ne.x * tileSize) + offsetFromEdgeX;
    ne.y = (ne.y * tileSize) + offsetFromEdgeY;
    sw.x = (sw.x * tileSize) + offsetFromEdgeX;
    sw.y = (sw.y * tileSize) + offsetFromEdgeY;
    se.x = (se.x * tileSize) + offsetFromEdgeX;
    se.y = (se.y * tileSize) + offsetFromEdgeY;

    applyRotation(&ne);
    applyRotation(&nw);
    applyRotation(&se);
    applyRotation(&sw);

    //fillSpace(&ne, &nw, &se, &sw);
    SDL_RenderDrawLine(renderer, nw.x, nw.y, sw.x, sw.y);
    SDL_RenderDrawLine(renderer, nw.x, nw.y, ne.x, ne.y);
    SDL_RenderDrawLine(renderer, sw.x, sw.y, se.x, se.y);
    SDL_RenderDrawLine(renderer, ne.x, ne.y, se.x, se.y);


}

void MapDrawer::fillSpace(Coordinate* ne, Coordinate* nw, Coordinate* se, Coordinate* sw){

    SDL_Vertex vert[4];
    int indices[] = {0, 1, 2, 1, 2, 3};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // center
    vert[0].position.x = ne->x;
    vert[0].position.y = ne->y;
    vert[0].color.r = 0;
    vert[0].color.g = 0;
    vert[0].color.b = 0;
    vert[0].color.a = 128;

    // left
    vert[1].position.x = nw->x;
    vert[1].position.y = nw->y;
    vert[1].color.r = 0;
    vert[1].color.g = 0;
    vert[1].color.b = 0;
    vert[1].color.a = 128;

    // right
    vert[2].position.x = se->x;
    vert[2].position.y = se->y;
    vert[2].color.r = 0;
    vert[2].color.g = 0;
    vert[2].color.b = 0;
    vert[2].color.a = 128;

    vert[3].position.x = sw->x;
    vert[3].position.y = sw->y;
    vert[3].color.r = 0;
    vert[3].color.g = 0;
    vert[3].color.b = 0;
    vert[3].color.a = 128;

    SDL_RenderGeometry(renderer, NULL, vert, 4, indices, 6);
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

MapDrawer::MapDrawer(SDL_Renderer *r, Map *aMap, UnitManager* aUnitManager, int aScreenSizeX, int aScreenSizeY)
                    :renderer(r), map(aMap), unitManager(aUnitManager), screenSizeX(aScreenSizeX), screenSizeY(aScreenSizeY)
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
