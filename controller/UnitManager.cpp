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


UnitManager::UnitManager(int numOfUnits, int mapSize) {
    for (int i = 0; i < numOfUnits; ++i) {

        int upperBound = mapSize - 2;
        int lowerBound = 3;
        int x = rand()%(upperBound-lowerBound + 1) + lowerBound;
        int y = rand()%(upperBound-lowerBound + 1) + lowerBound;
        auto unit = new Unit(Coordinate(x + 0.5, y + 0.5,0));

        units.push_back(unit);
    }
}

void UnitManager::init(Map *map){
    for(Unit* unit : units){
        updateUnit(unit, map);
    }
}

void UnitManager::updateUnit(Unit *unit, Map *map){
    MapSquare *occupiedSquare = map->getAt(unit->location.x, unit->location.y);
    MapSquare *nextSquare = map->getAt(occupiedSquare->intendedNextSquareUID);
    unit->occupiedSquareUID = occupiedSquare->UID;

    unit->currentDirection = TraversalVectors::vectorUV[occupiedSquare->directionToTarget];

    // find the total num of steps that should be taken
    // fewer steps = quicker movement
    double diffOne = 0;
    double diffTwo = 0;
    map->heightDifference(*occupiedSquare, *nextSquare, diffOne, diffTwo);

    unit->stepsTakenOne = 0;
    unit->stepsTakenTwo = 0;


    unit->totalNumOfStepsOne = minNumOfSteps + (maxNumOfSteps - map->normaliseSpeed(diffOne));
    unit->totalNumOfStepsTwo = minNumOfSteps + (maxNumOfSteps - map->normaliseSpeed(diffTwo));
    unit->stepHeightOne = diffOne / unit->totalNumOfStepsOne;
    unit->stepHeightTwo = diffTwo / unit->totalNumOfStepsTwo;
    unit->location.z = occupiedSquare->centre.z;


    if(TraversalVectors::isDiagonal(occupiedSquare->directionToTarget)){
        // TODO height calculation already accounts for diagonal - is this going to cancel it out?
        unit->stepDistanceOne = DIAGONAL_STEP_DISTANCE_HALF / unit->totalNumOfStepsOne;
        unit->stepDistanceTwo = DIAGONAL_STEP_DISTANCE_HALF / unit->totalNumOfStepsTwo;
    }
    else{
        unit->stepDistanceOne = VERTICAL_HORIZONTAL_STEP_DISTANCE_HALF / unit->totalNumOfStepsOne;
        unit->stepDistanceTwo = VERTICAL_HORIZONTAL_STEP_DISTANCE_HALF / unit->totalNumOfStepsTwo;
    }

}


// TODO figure out how to use mapSquare height to set unit.z
// TODO remember to make step sizes different for diagonal movement
// TODO calculate "heightStep" e.g. divide height difference for transition between
void UnitManager::update(Map *map) {
    for(Unit* unit : units){
        //move the unit along its path

        if(unit->occupiedSquareUID == map->target){
            // do nothing
        } else{


            // keep moving
            if(unit->stepsTakenOne < unit->totalNumOfStepsOne){
                unit->location.x += (unit->currentDirection.u * (unit->stepDistanceOne));
                unit->location.y += (unit->currentDirection.v * (unit->stepDistanceOne));
                unit->location.z += unit->stepHeightOne;
                unit->stepsTakenOne++;
            }
            else{
                unit->location.x += (unit->currentDirection.u * (unit->stepDistanceTwo));
                unit->location.y += (unit->currentDirection.v * (unit->stepDistanceTwo));
                unit->location.z += unit->stepHeightTwo;
                unit->stepsTakenTwo++;
            }

            if(unit->stepsTakenOne == unit->totalNumOfStepsOne
               && unit->stepsTakenTwo == unit->totalNumOfStepsTwo){
                //we've arrived at the centre of next square

                MapSquare *occupiedSquare = map->getAt(unit->location.x, unit->location.y);

                //ensure that unit location doesnt "wander" due to fractional float maths
                unit->location.x = occupiedSquare->centre.x;
                unit->location.y = occupiedSquare->centre.y;
                unit->location.z = occupiedSquare->centre.z;
                unit->occupiedSquareUID = occupiedSquare->UID;

                updateUnit(unit, map);
            }

        }

    }
}





