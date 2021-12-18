//
// Created by ct_co on 01/02/2021.
//

#ifndef TOPOGRAPHY_MAP_H
#define TOPOGRAPHY_MAP_H


#include <vector>
#include <array>
#include "MapSquare.h"

class Map {

public:
    int mapSizeX = 0;
    int mapSizeY = 0;

    double rotationAngle_degrees = 45;
    double rotationAngle = rotationAngle_degrees * (3.14159 / 180);

    std::vector<std::vector<MapSquare*>> mapSquares;

    Map() = default;
    Map(int aMapSizeX, int aMapSizeY);

    void rotateLeft();
    void rotateRight();

private:
    int createRandomHeight(int lowerBound, int upperBound);

};


#endif //TOPOGRAPHY_MAP_H
