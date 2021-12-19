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
            auto *nw = new Coordinate( i, j, createRandomHeight(0,0));
            auto *ne = new Coordinate( i + 1, j, createRandomHeight(0,0));
            auto *se = new Coordinate( i + 1, j + 1, createRandomHeight(0,0));
            auto *sw = new Coordinate( i, j + 1, createRandomHeight(0,0));
            auto *square =  new MapSquare(*ne, *nw, *se, *sw);
            row.push_back(square);
        }
        mapSquares.push_back(row);
    }

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
    rotationAngle_degrees += 0.1;
    if(rotationAngle_degrees >=359.9){
        rotationAngle_degrees = 0;
    }
    rotationAngle = rotationAngle_degrees * (3.14159 / 180);
}

void Map::rotateLeft() {
    rotationAngle_degrees-= 0.1;
    if(rotationAngle_degrees < 0){
        rotationAngle_degrees = 359;
    }
    rotationAngle = rotationAngle_degrees * (3.14159 / 180);
}

void Map::changeSquareHeight(DataTypes::Direction direction){
    int change = (direction == DataTypes::UP) ? 3 : -3;

    double oldHeightNW = mapSquares[selectedSquareX][selectedSquareY]->northWestCorner.z;
    double oldHeightNE = mapSquares[selectedSquareX][selectedSquareY]->northEastCorner.z;
    double oldHeightSW = mapSquares[selectedSquareX][selectedSquareY]->southWestCorner.z;
    double oldHeightSE = mapSquares[selectedSquareX][selectedSquareY]->southEastCorner.z;
    double newHeightNW = 0;
    double newHeightNE = 0;
    double newHeightSW = 0;
    double newHeightSE = 0;

    //if all heights are the same
    if(oldHeightNE == oldHeightNW && oldHeightNE == oldHeightSE && oldHeightNE == oldHeightSW){
        newHeightNW = oldHeightNW + change;
        newHeightNE = oldHeightNE + change;
        newHeightSW = oldHeightSW + change;
        newHeightSE = oldHeightSE + change;
    }
    else if(direction == DataTypes::UP)
    {
        int heightLimit = -INT32_MAX;

        //find the highest
        if(oldHeightNE > heightLimit) heightLimit = oldHeightNE;
        if(oldHeightNW > heightLimit) heightLimit = oldHeightNW;
        if(oldHeightSE > heightLimit) heightLimit = oldHeightSE;
        if(oldHeightSW > heightLimit) heightLimit = oldHeightSW;

        if(oldHeightNE + change < heightLimit){
            newHeightNE = oldHeightNE + change;
        }else if(oldHeightNE + change >= heightLimit){
            newHeightNE = heightLimit;
        }
        if(oldHeightNW + change < heightLimit){
            newHeightNW = oldHeightNW + change;
        }else if(oldHeightNW + change >= heightLimit){
            newHeightNW = heightLimit;
        }
        if(oldHeightSE + change < heightLimit){
            newHeightSE = oldHeightSE + change;
        }else if(oldHeightSE + change >= heightLimit){
            newHeightSE = heightLimit;
        }
        if(oldHeightSW + change < heightLimit){
            newHeightSW = oldHeightSW + change;
        }else if(oldHeightSW + change >= heightLimit){
            newHeightSW = heightLimit;
        }

    }
    else if(direction == DataTypes::DOWN)
    {
        int heightLimit = INT32_MAX;

        //find the lowest
        if(oldHeightNE < heightLimit) heightLimit = oldHeightNE;
        if(oldHeightNW < heightLimit) heightLimit = oldHeightNW;
        if(oldHeightSE < heightLimit) heightLimit = oldHeightSE;
        if(oldHeightSW < heightLimit) heightLimit = oldHeightSW;

        if(oldHeightNE + change > heightLimit){
            newHeightNE = oldHeightNE + change;
        }else if(oldHeightNE + change <= heightLimit){
            newHeightNE = heightLimit;
        }
        if(oldHeightNW + change > heightLimit){
            newHeightNW = oldHeightNW + change;
        }else if(oldHeightNW + change <= heightLimit){
            newHeightNW = heightLimit;
        }
        if(oldHeightSE + change > heightLimit){
            newHeightSE = oldHeightSE + change;
        }else if(oldHeightSE + change <= heightLimit){
            newHeightSE = heightLimit;
        }
        if(oldHeightSW + change > heightLimit){
            newHeightSW = oldHeightSW + change;
        }else if(oldHeightSW + change <= heightLimit){
            newHeightSW = heightLimit;
        }

    }


    mapSquares[selectedSquareX][selectedSquareY]->northWestCorner.z = newHeightNW;
    mapSquares[selectedSquareX][selectedSquareY]->northEastCorner.z = newHeightNE;
    mapSquares[selectedSquareX][selectedSquareY]->southWestCorner.z = newHeightSW;
    mapSquares[selectedSquareX][selectedSquareY]->southEastCorner.z = newHeightSE;

    if(selectedSquareX - 1 >= 0){
        mapSquares[selectedSquareX - 1][selectedSquareY]->northEastCorner.z = newHeightNW;
        mapSquares[selectedSquareX - 1][selectedSquareY]->southEastCorner.z = newHeightSW;
        if(selectedSquareY - 1 >= 0){
            mapSquares[selectedSquareX - 1][selectedSquareY - 1]->southEastCorner.z = newHeightNW;
        }
        if(selectedSquareY + 1 < mapSizeY){
            mapSquares[selectedSquareX - 1][selectedSquareY + 1]->northEastCorner.z = newHeightSW;
        }
    }
    if(selectedSquareX + 1 < mapSizeX){
        mapSquares[selectedSquareX + 1][selectedSquareY]->northWestCorner.z = newHeightNE;
        mapSquares[selectedSquareX + 1][selectedSquareY]->southWestCorner.z = newHeightSE;
        if(selectedSquareY - 1 >= 0){
            mapSquares[selectedSquareX + 1][selectedSquareY - 1]->southWestCorner.z = newHeightNE;
        }
        if(selectedSquareY + 1 < mapSizeY){
            mapSquares[selectedSquareX + 1][selectedSquareY + 1]->northWestCorner.z = newHeightSE;
        }
    }
    if(selectedSquareY - 1 >= 0){
        mapSquares[selectedSquareX][selectedSquareY - 1]->southWestCorner.z = newHeightNW;
        mapSquares[selectedSquareX][selectedSquareY - 1]->southEastCorner.z = newHeightNE;
    }
    if(selectedSquareY + 1 < mapSizeY){
        mapSquares[selectedSquareX][selectedSquareY + 1]->northWestCorner.z = newHeightSW;
        mapSquares[selectedSquareX][selectedSquareY + 1]->northEastCorner.z = newHeightSE;
    }

}

void Map::moveSelectedSquare(DataTypes::Direction direction) {

    switch(direction){
        case DataTypes::Direction::LEFT:
            selectedSquareX++;
            break;
        case DataTypes::Direction::RIGHT:
            selectedSquareX--;
            break;
        case DataTypes::Direction::UP:
            selectedSquareY++;
            break;
        case DataTypes::Direction::DOWN:
            selectedSquareY--;
            break;
    }

    if(selectedSquareX >= mapSizeX - 1){
        selectedSquareX = mapSizeX - 1;
    }
    else if(selectedSquareX < 0){
        selectedSquareX = 0;
    }
    if(selectedSquareY >= mapSizeY - 1){
        selectedSquareY = mapSizeY - 1;
    }
    else if(selectedSquareY < 0){
        selectedSquareY = 0;
    }

}

