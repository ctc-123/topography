//
// Created by ct_co on 01/02/2021.
//

#ifndef TOPOGRAPHY_MAP_H
#define TOPOGRAPHY_MAP_H


#include <vector>
#include <array>
#include "MapSquare.h"
#include "../data/DataTypes.h"

class Map {

public:
    int mapSizeX = 0;
    int mapSizeY = 0;

    double rotationAngle_degrees = 45;
    double rotationAngle = rotationAngle_degrees * (3.14159 / 180);

    int selectedSquareX = 0;
    int selectedSquareY = 0;

    std::vector<std::vector<MapSquare*>> mapSquares;


    Map() = default;
    Map(int aMapSizeX, int aMapSizeY);

    void rotateLeft();
    void rotateRight();
    void moveSelectedSquare(DataTypes::Direction direction);

private:
    int createRandomHeight(int lowerBound, int upperBound);
};


#endif //TOPOGRAPHY_MAP_H
