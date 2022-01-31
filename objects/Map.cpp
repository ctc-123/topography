//
// Created by ct_co on 01/02/2021.
//

#include "Map.h"
#include "../data/TraversalVectors.h"
#include "Unit.h"
#include "../data/PriorityQueue.h"
#include "../controller/MapIOHandler.h"
#include <cmath>
#include <unordered_map>
#include <set>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>

Map::Map(std::string &mapName) {
    mapSquares = MapIOHandler::getMap(mapName);

    mapSizeX = static_cast<int>(sqrt(mapSquares.size()));
    mapSizeY = mapSizeX;
    lastUID = (mapSizeX * mapSizeY) - 1;
    target = lastUID;

    mapSquares[target].directionToTarget = TraversalVectors::TARGET;

    for (int i = 0; i < mapSizeX; ++i) {

        for (int j = 0; j < mapSizeY; ++j) {

            if(i == 0 && j == 0){
                // do nothing
            }
            else if(i > 0 && j == 0){
                getAt(i, j)->heights.nw = getAt(i - 1, j)->heights.ne;
                getAt(i, j)->heights.sw = getAt(i - 1, j)->heights.se;
            }
            else if (i == 0 && j > 0){
                getAt(i, j)->heights.nw = getAt(i, j - 1)->heights.sw;
                getAt(i, j)->heights.ne = getAt(i, j - 1)->heights.se;
            }
            else{
                getAt(i, j)->heights.ne = getAt(i, j - 1)->heights.se;
                getAt(i, j)->heights.nw = getAt(i, j - 1)->heights.sw;
                getAt(i, j)->heights.sw = getAt(i - 1, j)->heights.se;
            }

        }

    }

    for (int k = 0; k < mapSquares.size(); ++k) {
        mapSquares[k].update();
    }

    connectSquares();

    calculateIntegrationField();


}



Map::Map(int aMapSizeX, int aMapSizeY) {

    mapSizeX = aMapSizeX;
    mapSizeY = aMapSizeY;
    lastUID = (mapSizeX * mapSizeY) - 1;
    target = lastUID;


    for (int i = 0; i < mapSizeX; ++i) {
        for (int j = 0; j < mapSizeY; ++j) {
            auto *centre = new Coordinate( i + 0.5, j + 0.5, createRandomHeight(0, 10));
            MapSquare square(*centre, (i * mapSizeX) + j);
            mapSquares.push_back(square);
        }
    }


    mapSquares.at(target).directionToTarget = TraversalVectors::TARGET;

    for (int i = 0; i < mapSizeX; ++i) {

        for (int j = 0; j < mapSizeY; ++j) {
            // TODO refactor
            if(i == 0 && j == 0){
                // do nothing
            }
            else if(i > 0 && j == 0){
                getAt(i, j)->heights.nw = getAt(i - 1, j)->heights.ne;
                getAt(i, j)->heights.sw = getAt(i - 1, j)->heights.se;
            }
            else if (i == 0 && j > 0){
                getAt(i, j)->heights.nw = getAt(i, j - 1)->heights.sw;
                getAt(i, j)->heights.ne = getAt(i, j - 1)->heights.se;
            }
            else{
                getAt(i, j)->heights.ne = getAt(i, j - 1)->heights.se;
                getAt(i, j)->heights.nw = getAt(i, j - 1)->heights.sw;
                getAt(i, j)->heights.sw = getAt(i - 1, j)->heights.se;
            }
        }
    }

    for (int UID = 0; UID < lastUID; UID++) {
        getAt(UID)->update();
    }

    connectSquares();
    calculateIntegrationField();
    printDirections();
}

void Map::connectSquares(){
    for (int i = 0; i < mapSizeX; ++i) {
        for (int j = 0; j < mapSizeY; ++j) {

            if (i == 0 && j > 0){
                // first column - and after first row
                // connect to N
                int diff = heightDifference(getAt(i, j)->UID, getAt(i, j - 1)->UID);
                getAt(i, j)->neighbors[getAt(i, j - 1)->UID] = diff;
                diff = heightDifference(getAt(i, j - 1)->UID, getAt(i, j)->UID);
                getAt(i, j - 1)->neighbors[getAt(i, j)->UID] = diff;
            }
            else if(i > 0 && j == 0){
                // after first column, and on first row
                // connect to squares to W, SW
                int diff = heightDifference(getAt(i, j)->UID, getAt(i - 1, j)->UID);
                getAt(i, j)->neighbors[getAt(i - 1, j)->UID] = diff;
                diff = heightDifference(getAt(i - 1, j)->UID, getAt(i, j)->UID);
                getAt(i - 1, j)->neighbors[getAt(i, j)->UID] = diff;

                diff = heightDifference(getAt(i, j)->UID, getAt(i - 1, j + 1)->UID);
                getAt(i, j)->neighbors[getAt(i - 1, j + 1)->UID] = diff;
                diff = heightDifference(getAt(i - 1, j + 1)->UID, getAt(i, j)->UID);
                getAt(i - 1, j + 1)->neighbors[getAt(i, j)->UID] = diff;
            }
            else if(i > 0 && j > 0 && j < mapSizeY - 1){
                // after first column and after first row
                // connect to squares to N, NW, W, SW
                int diff = heightDifference(getAt(i, j)->UID, getAt(i, j - 1)->UID);
                getAt(i, j)->neighbors[getAt(i, j - 1)->UID] = diff;
                diff = heightDifference(getAt(i, j - 1)->UID, getAt(i, j)->UID);
                getAt(i, j - 1)->neighbors[getAt(i, j)->UID] = diff;

                diff = heightDifference(getAt(i, j)->UID, getAt(i - 1, j - 1)->UID);
                getAt(i, j)->neighbors[getAt(i - 1, j - 1)->UID] = diff;
                diff = heightDifference(getAt(i - 1, j - 1)->UID, getAt(i, j)->UID);
                getAt(i - 1, j - 1)->neighbors[getAt(i, j)->UID] = diff;

                diff = heightDifference(getAt(i, j)->UID, getAt(i - 1, j)->UID);
                getAt(i, j)->neighbors[getAt(i - 1, j)->UID] = diff;
                diff = heightDifference(getAt(i - 1, j)->UID, getAt(i, j)->UID);
                getAt(i - 1, j)->neighbors[getAt(i, j)->UID] = diff;

                diff = heightDifference(getAt(i, j)->UID, getAt(i - 1, j + 1)->UID);
                getAt(i, j)->neighbors[getAt(i - 1, j + 1)->UID] = diff;
                diff = heightDifference(getAt(i - 1, j + 1)->UID, getAt(i, j)->UID);
                getAt(i - 1, j + 1)->neighbors[getAt(i, j)->UID] = diff;

            }
            else if(j == mapSizeY - 1){
                // on bottom row
                // connect to square N, NW, W

                int diff = heightDifference(getAt(i, j)->UID, getAt(i, j - 1)->UID);
                getAt(i, j)->neighbors[getAt(i, j - 1)->UID] = diff;
                diff = heightDifference(getAt(i, j - 1)->UID, getAt(i, j)->UID);
                getAt(i, j - 1)->neighbors[getAt(i, j)->UID] = diff;

                diff = heightDifference(getAt(i, j)->UID, getAt(i - 1, j - 1)->UID);
                getAt(i, j)->neighbors[getAt(i - 1, j - 1)->UID] = diff;
                diff = heightDifference(getAt(i - 1, j - 1)->UID, getAt(i, j)->UID);
                getAt(i - 1, j - 1)->neighbors[getAt(i, j)->UID] = diff;

                diff = heightDifference(getAt(i, j)->UID, getAt(i - 1, j)->UID);
                getAt(i, j)->neighbors[getAt(i - 1, j)->UID] = diff;
                diff = heightDifference(getAt(i - 1, j)->UID, getAt(i, j)->UID);
                getAt(i - 1, j)->neighbors[getAt(i, j)->UID] = diff;
            }
            else{
                // ?
            }

        }

    }
}

void Map::calculateIntegrationField()
{
    auto start_time_total = std::chrono::system_clock::now();

    std::list<int> openList;

    //Set goal node cost to 0 and add it to the open list
    getAt(target)->score = 0;
    openList.push_back(target);

    while (!openList.empty())
    {
        //Get the next node in the open list
        unsigned currentID = openList.front();
        openList.pop_front();

        //Iterate through the neighbors of the current node
        for (std::pair<int, int> neighbor : getAt(currentID)->neighbors)
        {
            int neighborID = neighbor.first;
            //Calculate the new cost of the neighbor node
            // based on the cost of the current node and the weight of the next node
            unsigned int endNodeCost = getAt(currentID)->score + getAt(neighborID)->neighbors[currentID];

            //If a shorter path has been found, add the node into the open list
            if (endNodeCost < getAt(neighborID)->score)
            {
                //Check if the neighbor cell is already in the list.
                //If it is not then add it to the end of the list.
                if (! (std::find(openList.begin(), openList.end(), neighborID) != openList.end()))
                {
                    mapSquares[neighborID].directionToTarget = getDirectionTo(mapSquares[currentID], mapSquares[neighborID]);
                    mapSquares[neighborID].intendedNextSquareUID = currentID;
                    openList.push_back(neighborID);
                }

                //Set the new cost of the neighbor node.
                getAt(neighborID)->score = endNodeCost;
            }
        }
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start_time_total;
    std::cout << elapsed.count() << '\n' << std::flush;
}

void Map::updatePath(){

    auto start_time_total = std::chrono::system_clock::now();

    for(MapSquare start : mapSquares) {
        start.hasUpdatedPath = false;
    }

    for(MapSquare start : mapSquares) {
        auto start_time = std::chrono::system_clock::now();
        if(start.hasUpdatedPath || start.UID == target){
            // skip
        }
        else {
            std::unordered_map<int, int> came_from;
            std::unordered_map<int, int> cost_so_far;

            PriorityQueue<int, int> frontier;
            frontier.put(start.UID, 0);

            came_from[start.UID] = start.UID;

            cost_so_far[start.UID] = 0;
            int final = 0;

            while (!frontier.empty()) {
                int current = frontier.get();

                if (mapSquares[current].UID == mapSquares[target].UID) {
                    final = target;
                    break;
                }

                for (std::pair<int, int> neighbor : getAt(current)->neighbors)
                {
                    int nextUID = neighbor.first;

                    int diff = neighbor.second;
                    int new_cost = cost_so_far[current] + diff;
                    if (cost_so_far.find(nextUID) == cost_so_far.end()
                        || new_cost < cost_so_far[nextUID]) {
                        mapSquares[current].score = normaliseSpeed(diff);
                        cost_so_far[nextUID] = new_cost;
                        int priority = new_cost;
                        frontier.put(nextUID, priority);
                        came_from[nextUID] = current;
                    }
                }
            }

            // process the newly created path
            int previous = final;
            int current = -1;

            while (current != start.UID) {
                current = came_from[previous];
                if (mapSquares[current].hasUpdatedPath) {
                    // skip - already has the best path
                } else {
                    mapSquares[current].directionToTarget = getDirectionTo(mapSquares[previous], mapSquares[current]);
                    mapSquares[current].hasUpdatedPath = true;
                    mapSquares[current].intendedNextSquareUID = previous;
                }
                previous = current;
            }


        }

        auto end = std::chrono::system_clock::now();
        auto elapsed = end - start_time;
        std::cout << elapsed.count() << '\n' << std::flush;
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start_time_total;
    std::cout << elapsed.count() << '\n' << std::flush;
}

int Map::normaliseSpeed(int aSpeed){

    int fromMin = -1000;
    int fromMax = 1000;
    int toMin = 1;
    int toMax = 100;

    return ((aSpeed - fromMin) * (toMax - toMin)) / ((fromMax - fromMin) + toMin);
}

std::vector<MapSquare*> Map::getNeighbors(int i, int j){
    std::vector<MapSquare*> neighbors;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            //attempt to add neighbors for all squares in all directions
            if(isValidMapIndex(i + x, j + y)
                && !(x == 0 && y == 0)){
                neighbors.push_back(getAt(i + x, j + y));
            }
        }
    }
    return neighbors;
}

int Map::getIndexInto(int i, int j){
    return (i * mapSizeX) + j;
}

MapSquare* Map::getAt(int UID){
    return &mapSquares.at(UID);
}

MapSquare* Map::getAt(int i, int j){
    return &mapSquares.at(getIndexInto(i, j));
}

int Map::createRandomHeight(int lowerBound, int upperBound)
{
    return rand()%(upperBound-lowerBound + 1) + lowerBound;
}

void Map::changeSquareHeight(DataTypes::Direction direction){
    //TODO update the central height value for any squares that are changed
    int change = (direction == DataTypes::UP) ? 3 : -3;

    int oldHeightNW = getAt(selX, selY)->heights.nw;
    int oldHeightNE = getAt(selX, selY)->heights.ne;
    int oldHeightSW = getAt(selX, selY)->heights.sw;
    int oldHeightSE = getAt(selX, selY)->heights.se;
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


    getAt(selX, selY)->heights.nw = newHeightNW;
    getAt(selX, selY)->heights.ne = newHeightNE;
    getAt(selX, selY)->heights.sw = newHeightSW;
    getAt(selX, selY)->heights.se = newHeightSE;

    if(selX - 1 >= 0){
        getAt(selX - 1, selY)->heights.ne = newHeightNW;
        getAt(selX - 1, selY)->heights.se = newHeightSW;
        if(selY - 1 >= 0){
            getAt(selX - 1, selY - 1)->heights.se = newHeightNW;
        }
        if(selY + 1 < mapSizeY){
            getAt(selX - 1, selY + 1)->heights.ne = newHeightSW;
        }
    }
    if(selX + 1 < mapSizeX){
        getAt(selX + 1, selY)->heights.nw = newHeightNE;
        getAt(selX + 1, selY)->heights.sw = newHeightSE;
        if(selY - 1 >= 0){
            getAt(selX + 1, selY - 1)->heights.sw = newHeightNE;
        }
        if(selY + 1 < mapSizeY){
            getAt(selX + 1, selY + 1)->heights.nw = newHeightSE;
        }
    }
    if(selY - 1 >= 0){
        getAt(selX, selY - 1)->heights.sw = newHeightNW;
        getAt(selX, selY - 1)->heights.se = newHeightNE;
    }
    if(selY + 1 < mapSizeY){
        getAt(selX, selY + 1)->heights.nw = newHeightSW;
        getAt(selX, selY + 1)->heights.ne = newHeightSE;
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
    else{
        //shouldnt be here?
        int i = 0;
    }

    return direction;
}



int Map::heightDifference(int UIDOne, int UIDTwo, int &aDiffOne, int &aDiffTwo) {

    TraversalVectors::VectorDirection direction;
    MapSquare *one = getAt(UIDOne);
    MapSquare *two = getAt(UIDTwo);

    TraversalVectors::getDirectionForConnection(one->centre.x, one->centre.y, two->centre.x, two->centre.y, direction);
    bool isDiagonal = false;
    int diffOne = 0;
    int diffTwo = 0;

    switch (direction){
        case TraversalVectors::vectorN_S :
            diffOne = one->heights.s - one->centre.z;
            diffTwo = two->centre.z - two->heights.n;
            break;
        case TraversalVectors::vectorS_N :
            diffOne = one->heights.n - one->centre.z;
            diffTwo = two->centre.z - two->heights.s;
            break;
        case TraversalVectors::vectorE_W :
            diffOne = one->heights.w - one->centre.z;
            diffTwo = two->centre.z - two->heights.e;
            break;
        case TraversalVectors::vectorW_E :
            diffOne = one->heights.e - one->centre.z;
            diffTwo = two->centre.z - two->heights.w;
            break;
        case TraversalVectors::vectorNE_SW :
            diffOne = one->heights.sw - one->centre.z;
            diffTwo = two->centre.z - two->heights.ne;
            isDiagonal = true;
            break;
        case TraversalVectors::vectorNW_SE:
            diffOne = one->heights.se - one->centre.z;
            diffTwo = two->centre.z - two->heights.nw;
            isDiagonal = true;
            break;
        case TraversalVectors::vectorSE_NW:
            diffOne = one->heights.nw - one->centre.z;
            diffTwo = two->centre.z - two->heights.se;
            isDiagonal = true;
            break;
        case TraversalVectors::vectorSW_NE:
            diffOne = one->heights.ne - one->centre.z;
            diffTwo = two->centre.z - two->heights.sw;
            isDiagonal = true;
            break;

        case TraversalVectors::LAST :
        case TraversalVectors::TARGET :
            // should never happen
            break;
    }

    aDiffOne = diffOne;
    aDiffTwo = diffTwo;

    if(diffOne < 0){
        diffOne = abs(diffOne);
    }
    else if(diffOne > 0){
        diffOne = diffOne * 2;
    }
    else{
        diffOne = 1;
    }

    if(diffTwo < 0){
        diffTwo = abs(diffTwo);
    }
    else if(diffTwo > 0){
        diffTwo = diffTwo * 2;
    }
    else{
        diffTwo = 1;
    }


    if(isDiagonal){
        return (diffOne + diffTwo) * 1.4; // TODO does this math make sense?
    }

    return diffOne + diffTwo;
}

int Map::heightDifference(int UIDOne, int UIDTwo) {
    int diffOne = 0;
    int diffTwo = 0;
    return heightDifference(UIDOne, UIDTwo, diffOne, diffTwo);
}

void Map::printDirections(){
    for (int j = 0; j < mapSizeY; ++j) {
        std::string line;
        for (int i = 0; i < mapSizeX; ++i) {
            switch(getAt(i, j)->directionToTarget){
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
                default:
                    line.append("X\t");
                    break;
            }
        }
        line.append("\n");
        std::cout << line << std::flush;
    }
}

bool Map::isValidUID(int UID){
    return (UID >= 0 && UID <= lastUID);
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



