//
// Created by Andrew on 10/28/2019.
//

#include "dunnIndex.h"

long double largestInterclusterDist = 0;
long double smallestIntraclusterDist = 99999;

vector<cluster> dunnClusters;
map<int,vector<pair<pair<int,int>,long double>>> pointDistances;

//perform the Dunn Index calculation of a vector of clusters
long double runDunnIndex(vector<cluster> clusters)
{
    largestInterclusterDist = 0;
    smallestIntraclusterDist = 99999;
    map<int,vector<pair<pair<int,int>,long double>>> currPoints;
    for(const auto& it: clusters)
    {
        if(it.getClusterId() != -1 && it.getPoints().size() > 1)
        {
            dunnClusters.push_back(it);
        }
    }

    //loop for calculating largest interCluster Distance
    for(const auto& it: dunnClusters)
    {
        currPoints = calculatePointDistance(it);

        for(auto iter: currPoints)
        {
            if(iter.second.at(iter.second.size()-1).second > largestInterclusterDist)
            {
                largestInterclusterDist = iter.second.at(iter.second.size()-1).second;
            }
        }
        currPoints.clear();
    }

    //loop for calculating smallest intra cluster distance
        for(auto iter: pointDistances)
        {
            bool changed = false;
            for(int i = 0; i < iter.second.size(); i++) {
                if (iter.second.at(i).second < smallestIntraclusterDist) {
                    for (const auto &it: dunnClusters) {
                        if (it.getPoints().find(iter.second.at(i).first.first) != it.getPoints().end() &&
                            it.getPoints().find(iter.second.at(i).first.second) == it.getPoints().end()) {
                            smallestIntraclusterDist = iter.second.at(i).second;
                            changed = true;
                        }
                    }
                    if(changed)
                    break;
                }
            }
        }

        dunnClusters.clear();

    return smallestIntraclusterDist/largestInterclusterDist;
}

//calculates the points of all the distances between every point in a particular cluster
map<int,vector<pair<pair<int,int>,long double>>> calculatePointDistance(cluster clusterA)
{
    map<int,vector<pair<pair<int,int>,long double>>> toReturn;
    vector<pair<pair<int,int>,long double>> distBetweenIt1;
    map<int,Data> clusterPoints = clusterA.getPoints();

    for(auto it1: clusterPoints)
    {
        for(auto it2: clusterPoints)
        {
            if(it2.first != it1.first)
            {
                distBetweenIt1.emplace_back(make_pair(it1.first,it2.first),pow(pow(it2.second.getX()-it1.second.getX(),2)+pow(it2.second.getY()-it1.second.getY(),2) ,0.5));
            }
        }
        sort(distBetweenIt1.begin(),distBetweenIt1.end(),checkPairs);
        toReturn.emplace(it1.first,distBetweenIt1);
        distBetweenIt1.clear();
    }

    return toReturn;
}

//takes a map of points and sorts all the distances between each point by smallest to largest
void calculatePointDistances(map<int,Data> points)
{
    vector<pair<pair<int,int>,long double>> currentDists;
    for(auto it: points)
    {
        for(auto it2: points)
        {
            if(it.first != it2.first)
                currentDists.emplace_back(make_pair(it.first,it2.first),pow(pow(it2.second.getX()-it.second.getX(),2)+pow(it2.second.getY()-it.second.getY(),2) ,0.5));
        }
        sort(currentDists.begin(),currentDists.end(), checkPairs);
        pointDistances.emplace(it.first,currentDists);
        currentDists.clear();
    }
}

//function that returns the whether one point distance is less than the other
bool checkPairs(pair<pair<int,int>,long double> pairA,pair<pair<int,int>,long double> pairB)
{
    return (pairA.second < pairB.second);
}


