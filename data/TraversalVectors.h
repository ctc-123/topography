//
// Created by ct_co on 22/12/2021.
//

#ifndef TOPOGRAPHY_TRAVERSALVECTORS_H
#define TOPOGRAPHY_TRAVERSALVECTORS_H


#include <map>
#include "../objects/VectorPath.h"

class TraversalVectors {
public:
    enum VectorDirection{   vectorNW_E ,
                            vectorNW_SE,
                            vectorNW_S ,
                            vectorN_W ,
                            vectorN_SW ,
                            vectorN_S ,
                            vectorN_SE ,
                            vectorN_E ,
                            vectorNE_W ,
                            vectorNE_SW,
                            vectorNE_S ,
                            vectorE_W ,
                            vectorE_SW ,
                            vectorE_S ,
                            vectorSE_W ,
                            vectorS_W,
                            LAST};

    const static std::map<VectorDirection, Vector> vectors;
    TraversalVectors();


};


#endif //TOPOGRAPHY_TRAVERSALVECTORS_H
