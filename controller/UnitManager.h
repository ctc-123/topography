//
// Created by ct_co on 21/12/2021.
//

#ifndef TOPOGRAPHY_UNITMANAGER_H
#define TOPOGRAPHY_UNITMANAGER_H


#include <vector>
#include <map>
#include <unordered_map>
#include "../objects/Unit.h"
#include "../objects/Map.h"
#include "../data/TraversalVectors.h"


class UnitManager {

public:
    UnitManager(int numOfUnits, int mapSize);

    std::vector<Unit*> units;
    void update(Map *map);
    void init(Map *map);

private:
    const double DIAGONAL_STEP_DISTANCE_HALF = 1.4142135623 / 2;
    const double VERTICAL_HORIZONTAL_STEP_DISTANCE_HALF = 1.0 / 2;
    int minNumOfSteps = 10;
    int maxNumOfSteps = 125;

    void updateUnit(Unit *unit, Map *map);
};


#endif //TOPOGRAPHY_UNITMANAGER_H
