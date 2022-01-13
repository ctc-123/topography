//
// Created by ct_co on 01/08/2021.
//

#include <SDL_render.h>
#include "MapDrawer.h"
#include <cmath>

void MapDrawer::drawMap() {

    for(MapSquare mapSquare : map->mapSquares){
            drawMapSquare(&mapSquare);
    }

    for(Unit *unit : unitManager->units){
        drawUnit(unit);
    }

    drawSelectedSquare();
    drawTargetSquare();


}

void MapDrawer::drawTargetSquare()
{
    SDL_SetRenderDrawColor (renderer , 255, 255, 1, 255);
    MapSquare target = map->mapSquares[map->target];
    Coordinate baseNW(target.centre.x - 0.2, target.centre.y - 0.2,  target.centre.z);
    Coordinate baseNE(target.centre.x + 0.2, target.centre.y - 0.2,  target.centre.z);
    Coordinate baseSE(target.centre.x + 0.2, target.centre.y + 0.2,  target.centre.z);
    Coordinate baseSW(target.centre.x - 0.2, target.centre.y + 0.2,  target.centre.z);

    Coordinate topNW(target.centre.x - 0.2, target.centre.y - 0.2,  target.centre.z + 30);
    Coordinate topNE(target.centre.x + 0.2, target.centre.y - 0.2,  target.centre.z + 30);
    Coordinate topSE(target.centre.x + 0.2, target.centre.y + 0.2,  target.centre.z + 30);
    Coordinate topSW(target.centre.x - 0.2, target.centre.y + 0.2,  target.centre.z + 30);

    baseNW.x = (baseNW.x * tileSize) + offsetFromEdgeX;
    baseNW.y = (baseNW.y * tileSize) + offsetFromEdgeY;
    baseNE.x = (baseNE.x * tileSize) + offsetFromEdgeX;
    baseNE.y = (baseNE.y * tileSize) + offsetFromEdgeY;
    baseSE.x = (baseSE.x * tileSize) + offsetFromEdgeX;
    baseSE.y = (baseSE.y * tileSize) + offsetFromEdgeY;
    baseSW.x = (baseSW.x * tileSize) + offsetFromEdgeX;
    baseSW.y = (baseSW.y * tileSize) + offsetFromEdgeY;

    topNW.x = (topNW.x * tileSize) + offsetFromEdgeX;
    topNW.y = (topNW.y * tileSize) + offsetFromEdgeY;
    topNE.x = (topNE.x * tileSize) + offsetFromEdgeX;
    topNE.y = (topNE.y * tileSize) + offsetFromEdgeY;
    topSE.x = (topSE.x * tileSize) + offsetFromEdgeX;
    topSE.y = (topSE.y * tileSize) + offsetFromEdgeY;
    topSW.x = (topSW.x * tileSize) + offsetFromEdgeX;
    topSW.y = (topSW.y * tileSize) + offsetFromEdgeY;
    
    applyRotation(&baseNW);
    applyRotation(&baseNE);
    applyRotation(&baseSE);
    applyRotation(&baseSW);
    applyRotation(&topNW);
    applyRotation(&topNE);
    applyRotation(&topSE);
    applyRotation(&topSW);

    SDL_RenderDrawLine(renderer, baseNW.x, baseNW.y, baseNE.x, baseNE.y);
    SDL_RenderDrawLine(renderer, baseNE.x, baseNE.y, baseSE.x, baseSE.y);
    SDL_RenderDrawLine(renderer, baseSE.x, baseSE.y, baseSW.x, baseSW.y);
    SDL_RenderDrawLine(renderer, baseSW.x, baseSW.y, baseNW.x, baseNW.y);

    SDL_RenderDrawLine(renderer, topNW.x, topNW.y, topNE.x, topNE.y);
    SDL_RenderDrawLine(renderer, topNE.x, topNE.y, topSE.x, topSE.y);
    SDL_RenderDrawLine(renderer, topSE.x, topSE.y, topSW.x, topSW.y);
    SDL_RenderDrawLine(renderer, topSW.x, topSW.y, topNW.x, topNW.y);

    SDL_RenderDrawLine(renderer, baseNW.x, baseNW.y, topNW.x, topNW.y);
    SDL_RenderDrawLine(renderer, baseNE.x, baseNE.y, topNE.x, topNE.y);
    SDL_RenderDrawLine(renderer, baseSE.x, baseSE.y, topSE.x, topSE.y);
    SDL_RenderDrawLine(renderer, baseSW.x, baseSW.y, topSW.x, topSW.y);


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
    rect.x = unitLocation.x - 2;
    rect.y = unitLocation.y - 2;
    rect.h = 4;
    rect.w = 4;

    SDL_RenderDrawRect(renderer, &rect);
    //SDL_RenderDrawPoint(renderer, unitLocation.x, unitLocation.y);
}

void MapDrawer::drawSelectedSquare(){
    SDL_SetRenderDrawColor (renderer , selectedSquareColour.r, selectedSquareColour.g, selectedSquareColour.b, selectedSquareColour.a);

    MapSquare mapSquare = map->mapSquares[map->getIndexInto(map->selX, map->selY)];

    Coordinate nw(mapSquare.centre.x - 0.5, mapSquare.centre.y - 0.5, mapSquare.heights.nw);
    Coordinate ne(mapSquare.centre.x + 0.5, mapSquare.centre.y - 0.5, mapSquare.heights.ne);
    Coordinate sw(mapSquare.centre.x - 0.5, mapSquare.centre.y + 0.5, mapSquare.heights.sw);
    Coordinate se(mapSquare.centre.x + 0.5, mapSquare.centre.y + 0.5, mapSquare.heights.se);

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

    Coordinate nw(mapSquare->centre.x - 0.5, mapSquare->centre.y - 0.5, mapSquare->heights.nw);
    Coordinate ne(mapSquare->centre.x + 0.5, mapSquare->centre.y - 0.5, mapSquare->heights.ne);
    Coordinate sw(mapSquare->centre.x - 0.5, mapSquare->centre.y + 0.5, mapSquare->heights.sw);
    Coordinate se(mapSquare->centre.x + 0.5, mapSquare->centre.y + 0.5, mapSquare->heights.se);

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

    //rotate
    double rx = (cx * rotationAngleCos) - (cy * rotationAngleSin);
    double ry = (cx * rotationAngleSin) + (cy * rotationAngleCos);

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

void MapDrawer::rotateRight() {
    rotationAngle += 0.001;
    if(rotationAngle >= M_PI * 2){
        rotationAngle = 0;
    }
    rotationAngleCos = cos(rotationAngle);
    rotationAngleSin = sin(rotationAngle);
}

void MapDrawer::rotateLeft() {
    rotationAngle -= 0.001;
    if(rotationAngle < 0){
        rotationAngle = 359;
    }
    rotationAngleCos = cos(rotationAngle);
    rotationAngleSin = sin(rotationAngle);
}
