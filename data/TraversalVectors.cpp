//
// Created by ct_co on 22/12/2021.
//

#include "TraversalVectors.h"


TraversalVectors::TraversalVectors() {
    vectors.insert(vectorNW_E , new Vector(0.0, 0.1));

        {vectorNW_SE, Vector(0.0,0.1)},
        {vectorNW_S , Vector(0.0,0.1)},
        {vectorN_W ,  Vector(0.0,0.1)},
        {vectorN_SW , Vector(0.0,0.1)},
        {vectorN_S ,  Vector(0.0,0.1)},
        {vectorN_SE , Vector(0.0,0.1)},
        {vectorN_E , Vector(0.0,0.1)},
        {vectorNE_W , Vector(0.0,0.1)},
        {vectorNE_SW, Vector(0.0,0.1)},
        {vectorNE_S , Vector(0.0,0.1)},
        {vectorE_W , Vector(0.0,0.1)},
        {vectorE_SW , Vector(0.0,0.1)},
        {vectorE_S , Vector(0.0,0.1)},
        {vectorSE_W , Vector(0.0,0.1)},
        {vectorS_W, Vector(0.0,0.1)}};
}
