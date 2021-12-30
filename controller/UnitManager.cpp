//
// Created by ct_co on 21/12/2021.
//

#include <cmath>
#include <cfloat>
#include <random>
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
        int currentMapSquareI = floor(unit->location.x);
        int currentMapSquareJ = floor(unit->location.y);
        double currentX = unit->location.x;
        double currentY = unit->location.y;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(1.0, 20.0);

        MapSquare* unitLocation = map->mapSquares[currentMapSquareI][currentMapSquareJ];

        double newX = currentX + 0.1 * ((unit->speed + 0.1 * (unitLocation->traversals.directionToSpeedMap.at(unit->direction))) * unit->directionVector.u);
        double newY = currentY + 0.1 * ((unit->speed + 0.1 * (unitLocation->traversals.directionToSpeedMap.at(unit->direction))) * unit->directionVector.v);
        int newMapSquareI = floor(newX);
        int newMapSquareJ = floor(newY);
        unit->location.x = newX;
        unit->location.y = newY;

        if(newMapSquareI != currentMapSquareI || newMapSquareJ != currentMapSquareJ){

            // TODO refactor into function
            //if the floor of X||Y is different, we have crossed a boundary into a different square
            //so we need to calculate new target + vector for unit

            //to determine where to go next, first we need to know where we are and which squares are adjacent
            std::vector<MapSquare*> candidateSquares;
            getSurroundingSquares(newMapSquareI, newMapSquareJ, map, candidateSquares);

            double highestScore = -DBL_MAX;
            TraversalVectors::VectorDirection newDirection = unit->direction;


            for(MapSquare* square : candidateSquares){
                if(square->northWest.x == currentMapSquareI && square->northWest.y == currentMapSquareJ) {
                    //ignore - unit just left this square
                }
                else{
                    // generate a "score" for how good the candidate square is

                    // how far is the new square from the target?
                    double distance = calculateDistanceBetween(square->centralX, square->centralY, unit->targetLocation.x, unit->targetLocation.y);

                    // whats the direction to the new square?
                    TraversalVectors::VectorDirection direction = getDirectionTo(newX, newY, square->centralX, square->centralY);

                    // what speed is the vector between the current unit location and the new square?
                    int speed = unitLocation->traversals.directionToSpeedMap.at(direction);

                    // lower distance is good, higher speed is good
                    double score = (speed * 0.5) - (distance) + (dist(mt));
                    if(score > highestScore){
                        highestScore = score;
                        newDirection = direction;
                    }

                }
            }
            unit->directionVector = TraversalVectors::vectorUV.at(newDirection);
            unit->direction = newDirection;
        }


    }
}

TraversalVectors::VectorDirection UnitManager::getDirectionTo(int newI, int newJ, int candidateI, int candidateJ){
    TraversalVectors::VectorDirection direction;
    if(newI == candidateI){
        //same column
        if(newJ == candidateJ + 1){
            direction = TraversalVectors::vectorN_S;
        }
        else if(newJ == candidateJ - 1){
            direction = TraversalVectors::vectorS_N;
        }
    }
    else if(newI == candidateI + 1){
        // +1 on x
        if(newJ == candidateJ){
            direction = TraversalVectors::vectorE_W;
        }
        else if(newJ == candidateJ + 1){
            direction = TraversalVectors::vectorNW_SE;
        }
        else if(newJ == candidateJ - 1){
            direction = TraversalVectors::vectorSW_NE;
        }
    }
    else if(newI == candidateI - 1){
        if(newJ == candidateJ){
            direction = TraversalVectors::vectorW_E;
        }
        else if(newJ == candidateJ + 1){
            direction = TraversalVectors::vectorSE_NW;
        }
        else if(newJ == candidateJ - 1){
            direction = TraversalVectors::vectorNE_SW;
        }
    }
    return direction;
}

double UnitManager::calculateDistanceBetween(double fromX, double fromY, double toX, double toY){
    double distanceX = fromX - toX;
    double distanceY = fromY - toY;
    return fabs(distanceX) + fabs(distanceY);
}

void UnitManager::getSurroundingSquares(int newX, int newY, Map *map, std::vector<MapSquare*> &squares){
    if(newX - 1 >= 0){
        squares.push_back(map->mapSquares[newX - 1][newY]);

        if(newY - 1 >= 0){
            squares.push_back(map->mapSquares[newX - 1][newY - 1]);
        }
        if(newY + 1 < map->mapSizeY){
            squares.push_back(map->mapSquares[newX - 1][newY + 1]);
        }
    }
    if(newX + 1 < map->mapSizeX){
        squares.push_back(map->mapSquares[newX + 1][newY]);

        if(newY - 1 >= 0){
            squares.push_back(map->mapSquares[newX + 1][newY - 1]);
        }
        if(newY + 1 < map->mapSizeY){
            squares.push_back(map->mapSquares[newX + 1][newY + 1]);
        }
    }
    if(newY - 1 >= 0){
        squares.push_back(map->mapSquares[newX][newY - 1]);
        squares.push_back(map->mapSquares[newX][newY - 1]);
    }
    if(newY + 1 < map->mapSizeY){
        squares.push_back(map->mapSquares[newX][newY + 1]);
    }

}



