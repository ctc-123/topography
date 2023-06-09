//
// Created by ct_co on 13/01/2022.
//

#include <fstream>
#include <sstream>
#include "MapIOHandler.h"
#include "../objects/Map.h"

// TODO how to handle target? just have z value with "T" after it?
std::vector<MapSquare> MapIOHandler::getMap(std::string &mapName, int &aMaxHeightDiff){
    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::vector<MapSquare>> map;

    // Create an input filestream
    std::ifstream myFile(mapName);

    std::string line;
    int val;
    int colY = 0;
    int mapSize = 0;
    bool lengthFound = false;

    // keep track of max and min heights
    int maxHeight = -INT32_MAX;
    int minHeight = INT32_MAX;


    // Read the column names
    if(myFile.good() && myFile.is_open()) {

        // Read data, line by line
        while (std::getline(myFile, line)) {


            if(!lengthFound){
                std::stringstream ss_temp(line);
                while (ss_temp >> val) {
                    if (ss_temp.peek() == ',') ss_temp.ignore();
                    mapSize++;
                }
                lengthFound = true;
            }

            std::stringstream ss(line);

            int colX = 0;

            std::vector<MapSquare> row;
            while (ss >> val) {
                if(val > maxHeight){
                    maxHeight = val;
                }
                if(val < minHeight){
                    minHeight = val;
                }

                Coordinate coordinate(colX + 0.5, colY + 0.5, val);

                int UID = (colX * mapSize) + colY;
                MapSquare square(coordinate, UID);
                row.push_back(square);

                // If the next token is a comma, ignore it and move on
                if (ss.peek() == ',') ss.ignore();

                // Increment the column index
                colX++;
            }
            map.push_back(row);
            colY++;

        }
    }

    aMaxHeightDiff = maxHeight - minHeight;

    myFile.close();

    std::vector<MapSquare> finalMap;
    for (int j = 0; j < mapSize; ++j) {
        for (int i = 0; i < mapSize; ++i) {
            finalMap.push_back(map[i][j]);
        }
    }

    return finalMap;

}