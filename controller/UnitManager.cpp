//
// Created by ct_co on 21/12/2021.
//

#include <cmath>
#include "UnitManager.h"
#include "../objects/MapSquare.h"
#include "../objects/Map.h"

UnitManager::UnitManager(int numOfUnits) {
    for (int i = 0; i < numOfUnits; ++i) {
        auto unit = new Unit(Coordinate(0,0,0), Coordinate(25,25,0), VectorPath(0.0, 1.0));
        units.push_back(unit);
    }
}

void UnitManager::update(Map *map) {
    for(Unit* unit : units){
        MapSquare* unitLocation = map->mapSquares[floor(unit->location.x)][floor(unit->location.y)];
        double currentX = unit->location.x;
        double currentY = unit->location.y;

        double newX = currentX + (unit->speed * unit->directionVector.u);
        double newY = currentY + (unit->speed * unit->directionVector.v);

                /*
        b.x += speed * v.x;
        b.y += speed * v.y;
*/


    }

}

