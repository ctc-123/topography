//
// Created by ct_co on 01/02/2021.
//

#include "Map.h"
#include <cmath>

using namespace std;
//make x and y odd so that we can find whole-number central point
Map::Map(int aMapSizeX, int aMapSizeY) {

    mapSizeX = aMapSizeX;
    mapSizeY = aMapSizeY;


    for (int i = 0; i < mapSizeX; ++i) {
        vector<MapSquare*> row;
        for (int j = 0; j < mapSizeY; ++j) {
            Coordinate *nw = new Coordinate( i, j, createRandomHeight(0,5));
            Coordinate *ne = new Coordinate( i + 1, j, createRandomHeight(0,5));
            Coordinate *se = new Coordinate( i + 1, j + 1, createRandomHeight(0,5));
            Coordinate *sw = new Coordinate( i, j + 1, createRandomHeight(0,5));
            MapSquare *square =  new MapSquare(*ne, *nw, *se, *sw);
            row.push_back(square);
        }
        mapSquares.push_back(row);
    }

    centralPoint = mapSquares[mapSizeX/2][mapSizeY/2]->northWestCorner;

    for (int i = 0; i < mapSizeX; ++i) {

        for (int j = 0; j < mapSizeY; ++j) {

            if(i == 0 && j == 0){
                // do nothing
            }
            else if(i > 0 && j == 0){
                mapSquares[i][j]->northWestCorner.z = mapSquares[i - 1][j]->northEastCorner.z;
                mapSquares[i][j]->southWestCorner.z = mapSquares[i - 1][j]->southEastCorner.z;
            }
            else if (i == 0 && j > 0){
                mapSquares[i][j]->northWestCorner.z = mapSquares[i][j - 1]->southWestCorner.z;
                mapSquares[i][j]->northEastCorner.z = mapSquares[i][j - 1]->southEastCorner.z;
            }
            else{
                mapSquares[i][j]->northWestCorner.z = mapSquares[i][j - 1]->southWestCorner.z;
                mapSquares[i][j]->northEastCorner.z = mapSquares[i][j - 1]->southEastCorner.z;
                mapSquares[i][j]->southWestCorner.z = mapSquares[i - 1][j]->southEastCorner.z;
            }

        }

    }


}

int Map::createRandomHeight(int lowerBound, int upperBound)
{
    return rand()%(upperBound-lowerBound + 1) + lowerBound;
}

void Map::rotateRight() {
    rotationAngle_degrees += 0.5;
    if(rotationAngle_degrees >=359){
        rotationAngle_degrees = 0;
    }
    rotationAngle = rotationAngle_degrees * (3.14159 / 180);
}

void Map::rotateLeft() {
    rotationAngle_degrees-= 0.5;
    if(rotationAngle_degrees < 0){
        rotationAngle_degrees = 359;
    }
    rotationAngle = rotationAngle_degrees * (3.14159 / 180);
}
