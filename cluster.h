//
// Created by Andrew on 10/26/2019.
//
#ifndef CLUSTER_H

#include <map>
#include <iterator>
#include "Data.h"

using namespace std;

class cluster {
    private:
        int clusterID;
        map<int,Data> points;
        long double centerX;
        long double centerY;

    public:

    explicit cluster(int newClusterId, Data newPoint) {clusterID = newClusterId; centerX = 0.0; centerY = 0.0; points.emplace(newClusterId,newPoint);}

    cluster() {clusterID = -1; centerX = 0.0; centerY = 0.0;}

    void generateCentroid();

    int getClusterId() const {
        return clusterID;
    }

    void setClusterId(int clusterId) {
        clusterID = clusterId;
    }

    const map<int,Data> &getPoints() const {
        return points;
    }

    void setPoints(const map<int,Data>&newPoints) {
        cluster::points = newPoints;
    }

    long double getCenterX() const {
        return centerX;
    }

    void setCenterX(float newCenterX) {
        cluster::centerX = newCenterX;
    }

    long double getCenterY() const {
        return centerY;
    }

    void setCenterY(float newCenterY) {
        cluster::centerY = newCenterY;
    }

};

#endif


