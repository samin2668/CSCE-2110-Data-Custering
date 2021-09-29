//
// Created by Andrew on 10/28/2019.
//

#include "KMeansCluster.h"

#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>



long double runDunnIndex(vector<cluster>);

map<int,vector<pair<pair<int,int>,long double>>> calculatePointDistance(cluster);

void calculatePointDistances(map<int,Data>);

bool checkPairs(pair<pair<int,int>,long double>,pair<pair<int,int>,long double>);

