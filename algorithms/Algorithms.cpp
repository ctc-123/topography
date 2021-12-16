//
// Created by ct_co on 19/11/2021.
//

#include <cstdlib>
#include <math.h>
#include "Algorithms.h"

void Algorithms::createSlopeFromPointToPoint(int point1Height, int point2Height, int edgeResolution)
{
    int difference = point1Height - point2Height;
    int edgesInSlope = edgeResolution;
    int newSlope[edgeResolution];

    if(difference == 0)
    {
        for (int i = 0; i < edgeResolution; ++i)
        {
            newSlope[i] = point1Height;
        }
    }
    else
    {
        float stepSize = abs(difference / edgeResolution);
        if(stepSize >= 1.0)
        {
            stepSize = ceil(stepSize);
            int newHeight = point1Height;
            for (int i = 1; i < edgesInSlope; ++i)
            {
                newHeight += stepSize;
                newSlope[i]  = newHeight;
            }
        }
        else
        {
            bool done = false;
            float totalHeight = 0.0;
            int stepsUntilIncrement = 1;
            while(!done)
            {
                totalHeight += stepSize;
                stepsUntilIncrement++;
                if(totalHeight > 1.0)
                {
                    done = true;
                }
            }

            int stepsPerformed = 0;
            int newHeight = point1Height;
            for (int i = 0; i < edgeResolution; ++i)
            {
                if(stepsPerformed == stepsUntilIncrement)
                {
                    newHeight -= stepSize;
                }
                newSlope[i] = newHeight;
            }

        }
    }
}
