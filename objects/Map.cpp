//
// Created by ct_co on 01/02/2021.
//

#include "Map.h"
#include "../data/TraversalVectors.h"
#include "Unit.h"
#include "../data/PriorityQueue.h"
#include <cmath>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <string>
#include <iostream>


Map::Map(int aMapSizeX, int aMapSizeY) {

    mapSizeX = aMapSizeX;
    mapSizeY = aMapSizeY;

    for (int i = 0; i < mapSizeX; ++i) {
        for (int j = 0; j < mapSizeY; ++j) {
            auto *centre = new Coordinate( i + 0.5, j + 0.5, createRandomHeight(0,30));
            MapSquare square(*centre, (i * mapSizeX) + j);
            mapSquares.push_back(square);
        }
    }
    mapSquares[target].directionToTarget = TraversalVectors::TARGET;

    for (int i = 0; i < mapSizeX; ++i) {

        for (int j = 0; j < mapSizeY; ++j) {

            if(i == 0 && j == 0){
                // do nothing
            }
            else if(i > 0 && j == 0){
                mapSquares[getIndexInto(i, j)].heights.nw = mapSquares[getIndexInto(i - 1, j)].heights.ne;
                mapSquares[getIndexInto(i, j)].heights.sw = mapSquares[getIndexInto(i - 1, j)].heights.se;
            }
            else if (i == 0 && j > 0){
                mapSquares[getIndexInto(i, j)].heights.nw = mapSquares[getIndexInto(i, j - 1)].heights.sw;
                mapSquares[getIndexInto(i, j)].heights.ne = mapSquares[getIndexInto(i, j - 1)].heights.se;
            }
            else{
                mapSquares[getIndexInto(i, j)].heights.ne = mapSquares[getIndexInto(i, j - 1)].heights.se;
                mapSquares[getIndexInto(i, j)].heights.nw = mapSquares[getIndexInto(i, j - 1)].heights.sw;
                mapSquares[getIndexInto(i, j)].heights.sw = mapSquares[getIndexInto(i - 1, j)].heights.se;
            }

        }

    }

    for(MapSquare start : mapSquares) {
        start.calculateCentralHeight();
    }

    updatePath();

    //output paths
    for (int j = 0; j < mapSizeY; ++j) {
        std::string line;
        for (int i = 0; i < mapSizeX; ++i) {
            switch(mapSquares[getIndexInto(i, j)].directionToTarget){

                case TraversalVectors::vectorN_S :
                    line.append("↓\t");
                    break;
                case TraversalVectors::vectorS_N :
                    line.append("↑\t");
                    break;
                case TraversalVectors::vectorNE_SW :
                    line.append("⬋\t");
                    break;
                case TraversalVectors::vectorSW_NE :
                    line.append("↗\t");
                    break;
                case TraversalVectors::vectorE_W :
                    line.append("⬅\t");
                    break;
                case TraversalVectors::vectorW_E :
                    line.append("➡\t");
                    break;
                case TraversalVectors::vectorSE_NW :
                    line.append("↖\t");
                    break;
                case TraversalVectors::vectorNW_SE :
                    line.append("↘\t");
                    break;
                case TraversalVectors::TARGET :
                    line.append("@\t");
                    break;
            }
        }
        line.append("\n");
        std::cout << line;

    }



}

void Map::updatePath(){


    for(MapSquare start : mapSquares) {
        start.hasUpdatedPath = false;
    }

    for(MapSquare start : mapSquares) {
        if(start.hasUpdatedPath || start.UID == target){
            // skip
        }
        else
        {
            std::unordered_map<int, int> came_from;
            std::unordered_map<int, double> cost_so_far;

            PriorityQueue<int, double> frontier;
            frontier.put(start.UID, 0);

            came_from[start.UID] = start.UID;

            cost_so_far[start.UID] = 0;

            while (!frontier.empty()) {
                int current = frontier.get();

                // TODO check for .hasUpdatedPath - if so, stop looking and point current towards it
                // if .hasUpdatedPath == true we have already found the best path onwards so just reuse it
                if (mapSquares[current].UID == mapSquares[target].UID) {
                    break;
                }

                for (MapSquare *next : neighbors(mapSquares[current].centre.x, mapSquares[current].centre.y)) {
                    double new_cost = cost_so_far[current] + heightDifference(mapSquares[current], *next);
                    if (cost_so_far.find(next->UID) == cost_so_far.end()
                        || new_cost < cost_so_far[next->UID]) {
                        cost_so_far[next->UID] = new_cost;
                        double priority = new_cost + heuristic(mapSquares[next->UID],mapSquares[target]);
                        frontier.put(next->UID, priority);
                        came_from[next->UID] = current;
                    }
                }
            }
            // process the newly created path

            int previous = target;
            int current = 0;

            while (current != start.UID) {
                current = came_from[previous];
                if(mapSquares[current].hasUpdatedPath){
                    // skip - already has the best path
                }
                else{
                    mapSquares[current].directionToTarget = getDirectionTo(mapSquares[previous], mapSquares[current]);
                    mapSquares[current].hasUpdatedPath = true;
                }
                previous = current;
            }



        }


    }
}

std::vector<MapSquare*> Map::neighbors(int i, int j){
    std::vector<MapSquare*> neighbors;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            //attempt to add connections for all squares in all directions
            if(isValidMapIndex(i + x, j + y)
                && !(x == 0 && y == 0)){
                neighbors.push_back(&mapSquares[getIndexInto(i + x, j + y)]);
            }
        }
    }
    return neighbors;
}

int Map::getIndexInto(int i, int j){
    return (i * mapSizeX) + j;
}

int Map::createRandomHeight(int lowerBound, int upperBound)
{
    return rand()%(upperBound-lowerBound + 1) + lowerBound;
}

void Map::changeSquareHeight(DataTypes::Direction direction){
    int change = (direction == DataTypes::UP) ? 3 : -3;

    int oldHeightNW = mapSquares[getIndexInto(selX, selY)].heights.nw;
    int oldHeightNE = mapSquares[getIndexInto(selX, selY)].heights.ne;
    int oldHeightSW = mapSquares[getIndexInto(selX, selY)].heights.sw;
    int oldHeightSE = mapSquares[getIndexInto(selX, selY)].heights.se;
    int newHeightNW = 0;
    int newHeightNE = 0;
    int newHeightSW = 0;
    int newHeightSE = 0;

    //if all heights are the same
    if(oldHeightNE == oldHeightNW && oldHeightNE == oldHeightSE && oldHeightNE == oldHeightSW){
        newHeightNW = oldHeightNW + change;
        newHeightNE = oldHeightNE + change;
        newHeightSW = oldHeightSW + change;
        newHeightSE = oldHeightSE + change;
    }
    else if(direction == DataTypes::UP)
    {
        int heightLimit = -INT32_MAX;

        //find the highest
        if(oldHeightNE > heightLimit) heightLimit = oldHeightNE;
        if(oldHeightNW > heightLimit) heightLimit = oldHeightNW;
        if(oldHeightSE > heightLimit) heightLimit = oldHeightSE;
        if(oldHeightSW > heightLimit) heightLimit = oldHeightSW;

        if(oldHeightNE + change < heightLimit){
            newHeightNE = oldHeightNE + change;
        }else if(oldHeightNE + change >= heightLimit){
            newHeightNE = heightLimit;
        }
        if(oldHeightNW + change < heightLimit){
            newHeightNW = oldHeightNW + change;
        }else if(oldHeightNW + change >= heightLimit){
            newHeightNW = heightLimit;
        }
        if(oldHeightSE + change < heightLimit){
            newHeightSE = oldHeightSE + change;
        }else if(oldHeightSE + change >= heightLimit){
            newHeightSE = heightLimit;
        }
        if(oldHeightSW + change < heightLimit){
            newHeightSW = oldHeightSW + change;
        }else if(oldHeightSW + change >= heightLimit){
            newHeightSW = heightLimit;
        }

    }
    else if(direction == DataTypes::DOWN)
    {
        int heightLimit = INT32_MAX;

        //find the lowest
        if(oldHeightNE < heightLimit) heightLimit = oldHeightNE;
        if(oldHeightNW < heightLimit) heightLimit = oldHeightNW;
        if(oldHeightSE < heightLimit) heightLimit = oldHeightSE;
        if(oldHeightSW < heightLimit) heightLimit = oldHeightSW;

        if(oldHeightNE + change > heightLimit){
            newHeightNE = oldHeightNE + change;
        }else if(oldHeightNE + change <= heightLimit){
            newHeightNE = heightLimit;
        }
        if(oldHeightNW + change > heightLimit){
            newHeightNW = oldHeightNW + change;
        }else if(oldHeightNW + change <= heightLimit){
            newHeightNW = heightLimit;
        }
        if(oldHeightSE + change > heightLimit){
            newHeightSE = oldHeightSE + change;
        }else if(oldHeightSE + change <= heightLimit){
            newHeightSE = heightLimit;
        }
        if(oldHeightSW + change > heightLimit){
            newHeightSW = oldHeightSW + change;
        }else if(oldHeightSW + change <= heightLimit){
            newHeightSW = heightLimit;
        }

    }


    mapSquares[getIndexInto(selX, selY)].heights.nw = newHeightNW;
    mapSquares[getIndexInto(selX, selY)].heights.ne = newHeightNE;
    mapSquares[getIndexInto(selX, selY)].heights.sw = newHeightSW;
    mapSquares[getIndexInto(selX, selY)].heights.se = newHeightSE;

    if(selX - 1 >= 0){
        mapSquares[getIndexInto(selX - 1, selY)].heights.ne = newHeightNW;
        mapSquares[getIndexInto(selX - 1, selY)].heights.se = newHeightSW;
        if(selY - 1 >= 0){
            mapSquares[getIndexInto(selX - 1, selY - 1)].heights.se = newHeightNW;
        }
        if(selY + 1 < mapSizeY){
            mapSquares[getIndexInto(selX - 1, selY + 1)].heights.ne = newHeightSW;
        }
    }
    if(selX + 1 < mapSizeX){
        mapSquares[getIndexInto(selX + 1, selY)].heights.nw = newHeightNE;
        mapSquares[getIndexInto(selX + 1, selY)].heights.sw = newHeightSE;
        if(selY - 1 >= 0){
            mapSquares[getIndexInto(selX + 1, selY - 1)].heights.sw = newHeightNE;
        }
        if(selY + 1 < mapSizeY){
            mapSquares[getIndexInto(selX + 1, selY + 1)].heights.nw = newHeightSE;
        }
    }
    if(selY - 1 >= 0){
        mapSquares[getIndexInto(selX, selY -1)].heights.sw = newHeightNW;
        mapSquares[getIndexInto(selX, selY -1)].heights.se = newHeightNE;
    }
    if(selY + 1 < mapSizeY){
        mapSquares[getIndexInto(selX, selY + 1)].heights.nw = newHeightSW;
        mapSquares[getIndexInto(selX, selY + 1)].heights.ne = newHeightSE;
    }

}

void Map::moveSelectedSquare(DataTypes::Direction direction) {

    switch(direction){
        case DataTypes::Direction::LEFT:
            selX++;
            break;
        case DataTypes::Direction::RIGHT:
            selX--;
            break;
        case DataTypes::Direction::UP:
            selY++;
            break;
        case DataTypes::Direction::DOWN:
            selY--;
            break;
    }

    if(selX >= mapSizeX - 1){
        selX = mapSizeX - 1;
    }
    else if(selX < 0){
        selX = 0;
    }
    if(selY >= mapSizeY - 1){
        selY = mapSizeY - 1;
    }
    else if(selY < 0){
        selY = 0;
    }

}

/*
 * returns the direction that points from MapSquare one towards MapSquare two
 */

TraversalVectors::VectorDirection Map::getDirectionTo(MapSquare from, MapSquare to){
    TraversalVectors::VectorDirection direction;
    if(from.centre.x == to.centre.x){
        //same column
        if(from.centre.y == to.centre.y + 1){
            direction = TraversalVectors::vectorN_S;
        }
        else if(from.centre.y == to.centre.y - 1){
            direction = TraversalVectors::vectorS_N;
        }
    }
    else if(from.centre.x == to.centre.x + 1){
        // +1 on x
        if(from.centre.y == to.centre.y){
            direction = TraversalVectors::vectorW_E;
        }
        else if(from.centre.y == to.centre.y + 1){
            direction = TraversalVectors::vectorNW_SE;
        }
        else if(from.centre.y == to.centre.y - 1){
            direction = TraversalVectors::vectorSW_NE;
        }
    }
    else if(from.centre.x == to.centre.x - 1){
        // -1 on x
        if(from.centre.y == to.centre.y){
            direction = TraversalVectors::vectorE_W;
        }
        else if(from.centre.y == to.centre.y + 1){
            direction = TraversalVectors::vectorNE_SW;
        }
        else if(from.centre.y == to.centre.y - 1){
            direction = TraversalVectors::vectorSE_NW;
        }
    }
    return direction;
}



double Map::distanceBetween(MapSquare one, MapSquare two) {
    int dx = abs(two.centre.x - one.centre.x);
    int dy = abs(two.centre.y - one.centre.y);

    int min = std::min(dx, dy);
    int max = std::max(dx, dy);

    int diagonalSteps = min;
    int straightSteps = max - min;

    return M_SQRT2 * diagonalSteps + straightSteps;
}

//this should return the 'cost' of moving from one to two
// i.e. if two is higher than one,
double Map::heightDifference(MapSquare one, MapSquare two) {
    return two.centre.z - one.centre.z;
}

double Map::heuristic(MapSquare one, MapSquare two){
    //expected that square two is a target square
    // TODO any other factors that could improve heuristic?
    return distanceBetween(one, two);
}

bool Map::isValidMapIndex(int i, int j) {
    if(i < 0 || i >= mapSizeX){
        return false;
    }
    else if(j < 0 || j >= mapSizeY){
        return false;
    }
    return true;
}

