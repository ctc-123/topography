//
// Created by ct_co on 01/02/2021.
//

#ifndef TOPOGRAPHY_MAP_H
#define TOPOGRAPHY_MAP_H


#include <vector>
#include <array>
#include <unordered_map>
#include "MapSquare.h"
#include "../data/DataTypes.h"
#include <cmath>


class Map {

public:
    int mapSizeX = 0;
    int mapSizeY = 0;
    int selX = 0;
    int selY = 0;
    int target = 0;
    const int maxHeightDifference = 1000;
    std::vector<MapSquare> mapSquares;
    Map(int aMapSizeX, int aMapSizeY);
    explicit Map(std::string &mapName);

    void moveSelectedSquare(DataTypes::Direction direction);
    void changeSquareHeight(DataTypes::Direction direction);
    double heightDifference(MapSquare one, MapSquare two, double &diffOne, double &diffTwo);
    int normaliseSpeed(int aSpeed);
    MapSquare *getAt(int i, int j);
    MapSquare *getAt(int UID);

private:

    int getIndexInto(int i, int j);
    static int createRandomHeight(int lowerBound, int upperBound);
    bool isValidMapIndex(int i, int j);
    void updatePath();
    std::vector<MapSquare*> neighbors(int i, int j);
    static double distanceBetween(MapSquare one, MapSquare two);
    static double heuristic(MapSquare one, MapSquare two);
    static TraversalVectors::VectorDirection getDirectionTo(MapSquare from, MapSquare to);


    void printDirections();


};


#endif //TOPOGRAPHY_MAP_H
