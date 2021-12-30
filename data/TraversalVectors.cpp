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


