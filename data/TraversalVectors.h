//
// Created by ct_co on 22/12/2021.
//

#ifndef TOPOGRAPHY_TRAVERSALVECTORS_H
#define TOPOGRAPHY_TRAVERSALVECTORS_H


#include <map>
#include "../objects/Vector.h"

class TraversalVectors {
public:

     enum VectorDirection{   vectorN_S ,
                            vectorS_N,
                            vectorNE_SW ,
                            vectorSW_NE,
                            vectorE_W ,
                            vectorW_E ,
                            vectorSE_NW ,
                            vectorNW_SE,
                            LAST};


    static std::map<VectorDirection, Vector> vectorUV;
    TraversalVectors();


};


#endif //TOPOGRAPHY_TRAVERSALVECTORS_H
