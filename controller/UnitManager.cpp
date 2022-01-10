//
// Created by ct_co on 21/12/2021.
//

#include <cmath>
#include <cfloat>
#include <random>
#include <queue>


#include "UnitManager.h"
#include "../objects/MapSquare.h"
#include "../objects/Map.h"


UnitManager::UnitManager(int numOfUnits) {
    for (int i = 0; i < numOfUnits; ++i) {
        auto unit = new Unit(Coordinate(10,10,0),
                        Coordinate(90,90,0),
                        Vector(0.0, 1.0),
                            TraversalVectors::vectorN_S);

        units.push_back(unit);
    }
}


void UnitManager::update(Map *map) {
    for(Unit* unit : units){
        //move the unit along its path

    }
}





