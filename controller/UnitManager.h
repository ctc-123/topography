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
    UnitManager(int numOfUnits);

    std::vector<Unit*> units;
    void update(Map *map);



};


#endif //TOPOGRAPHY_UNITMANAGER_H
