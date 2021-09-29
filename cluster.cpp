//
// Created by Andrew on 10/26/2019.
//

#include "cluster.h"

//generate the center of a cluster
void cluster::generateCentroid() {

    if(!points.empty())
    {
        long double sumX = 0;
        long double sumY = 0;
        for(auto it: points)
        {
            sumX += it.second.getX();
            sumY += it.second.getY();
        }
        centerX = sumX/points.size();
        centerY = sumY/points.size();
    }

}
