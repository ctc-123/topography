//
// Created by ct_co on 21/12/2021.
//

#ifndef TOPOGRAPHY_UNITMANAGER_H
#define TOPOGRAPHY_UNITMANAGER_H


#include <vector>
#include <map>
#include "../objects/Unit.h"
#include "../objects/Map.h"

class UnitManager {

public:
    UnitManager(int numOfUnits);

    void update(Map *map);

private:
    std::vector<Unit*> units;

};


#endif //TOPOGRAPHY_UNITMANAGER_H
