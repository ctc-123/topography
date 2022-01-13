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

        int upperBound = 30;
        int lowerBound = 3;
        int x = rand()%(upperBound-lowerBound + 1) + lowerBound;
        int y = rand()%(upperBound-lowerBound + 1) + lowerBound;
        auto unit = new Unit(Coordinate(x, y,0));

        units.push_back(unit);
    }
}


void UnitManager::update(Map *map) {
    for(Unit* unit : units){
        //move the unit along its path
        MapSquare occupiedSquare = map->mapSquares[map->getIndexInto(unit->location.x, unit->location.y)];
        if(occupiedSquare.UID == map->target){
            // do nothing - reached target
        }
        else
        {
            double squareSpeed = (100 + occupiedSquare.speed) * 0.0001;
            Vector direction = TraversalVectors::vectorUV[occupiedSquare.directionToTarget];
            unit->location.x += (direction.u * (unit->speed + squareSpeed));
            unit->location.y += (direction.v * (unit->speed + squareSpeed));
            unit->location.z = occupiedSquare.centre.z;
            // TODO figure out how to use mapSquare height to set unit.z
        }
    }
}





