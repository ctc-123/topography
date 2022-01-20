//
// Created by ct_co on 22/12/2021.
//

#include "TraversalVectors.h"

std::map<TraversalVectors::VectorDirection, Vector> TraversalVectors::vectorUV;

TraversalVectors::TraversalVectors() {
    vectorUV.emplace(TraversalVectors::vectorN_S, Vector(0,1));
    vectorUV.emplace(TraversalVectors::vectorS_N, Vector(0,-1));
    vectorUV.emplace(TraversalVectors::vectorNE_SW, Vector(-0.7071,0.7071));
    vectorUV.emplace(TraversalVectors::vectorSW_NE, Vector(0.7071,-0.7071));
    vectorUV.emplace(TraversalVectors::vectorE_W, Vector(-1,0));
    vectorUV.emplace(TraversalVectors::vectorW_E, Vector(1,0));
    vectorUV.emplace(TraversalVectors::vectorSE_NW, Vector(-0.7071,-0.7071));
    vectorUV.emplace(TraversalVectors::vectorNW_SE, Vector(0.7071,0.7071));

}

bool TraversalVectors::isDiagonal(VectorDirection direction){
    return !(direction == vectorN_S
             || direction == vectorS_N
             || direction == vectorE_W
             || direction == vectorW_E);
}


/*
 * returns the vector direction enum for the direction *from* point represented by xOne,yOne *to* point xTwo, yTwo
 * assumes that the given points are adjacent to each other (including diagonally) and are aligned with a grid
 *
 * returns false if the given points are invalid
 */
bool TraversalVectors::getDirectionForConnection(int xOne, int yOne, int xTwo, int yTwo,
                                                 TraversalVectors::VectorDirection &direction) {
    if(xOne < xTwo){
        if(yOne < yTwo){
            direction = TraversalVectors::vectorNW_SE;
            return true;
        }
        else if(yOne == yTwo){
            direction = TraversalVectors::vectorW_E;
            return true;
        }
        else if(yOne > yTwo){
            direction = TraversalVectors::vectorSW_NE;
            return true;
        }
    }
    else if(xOne > xTwo){
        if(yOne < yTwo){
            direction = TraversalVectors::vectorNE_SW;
            return true;
        }
        else if(yOne == yTwo){
            direction = TraversalVectors::vectorE_W;
            return true;
        }
        else if(yOne > yTwo){
            direction = TraversalVectors::vectorSE_NW;
            return true;
        }
    }
    else if(xOne == xTwo){
        if(yOne > yTwo){
            direction = TraversalVectors::vectorS_N;
            return true;
        }
        else if(yOne < yTwo){
            direction = TraversalVectors::vectorN_S;
            return true;
        }
    }

    return false;
}



