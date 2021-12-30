//
// Created by ct_co on 21/12/2021.
//

#ifndef TOPOGRAPHY_UNITMANAGER_H
#define TOPOGRAPHY_UNITMANAGER_H


#include <vector>
#include <map>
#include "../objects/Unit.h"
#include "../objects/Map.h"
#include "../data/TraversalVectors.h"


class UnitManager {

public:
    UnitManager(int numOfUnits);

    std::vector<Unit*> units;
    void update(Map *map);

private:
    double calculateDistanceBetween(double fromX, double fromY, double toX, double toY);
    void getSurroundingSquares(int newX, int newY, Map *map, std::vector<MapSquare *> &squares);

    TraversalVectors::VectorDirection getDirectionTo(int newI, int newJ, int candidateI, int candidateJ);
};


#endif //TOPOGRAPHY_UNITMANAGER_H
