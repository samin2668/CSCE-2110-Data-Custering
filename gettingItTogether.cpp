//
// Created by Andrew on 10/31/2019.
//

#include "gettingItTogether.h"


extern int kMin;
extern int kMax;
extern map <int, Data> myPoints;
extern map <int, vector <int> > myCentroids;
long double highestKMeansDIndex = 0;
int highestKMeansDIndex_ID;

//run all parts of the program and output the Dunn Index analysis at the edn
void generateSummary()
{
    // read all data points from config file
    getPoints();
    pair<int,long double> bestCentroidClusterDIndex;
    calculatePointDistances(myPoints);

    cout << "The total number of k values to be tested is " << (kMax - kMin + 1) << endl;
    cout << "The total number of points in this file is " << myPoints.size() << endl << endl;

    runKmeans();
    cout << endl;
    bestCentroidClusterDIndex = runCentroidClustering(myPoints);

    //Output analysis and final summary
    cout << endl;
    cout << "The final analysis shows:" << endl;
    cout << "For k-means, a k value of " << highestKMeansDIndex_ID << " had the highest Dunn index of " << highestKMeansDIndex << endl;
    cout << "For centroid-linkage clustering, " << bestCentroidClusterDIndex.first << " clusters had the highest Dunn index of " << bestCentroidClusterDIndex.second << endl;
    cout << "Complete!" << endl;
}

void runKmeans()
{
    int k, i;
    int clusterSize;
    Data nearest;
    // run and display output for k-means clustering algorithm
    KMeansCluster kMeans(kMin, kMax, myPoints, myCentroids);
    cout << "For k-means clustering:" << endl;
    for( k = kMin ; k <= kMax; k++)
    {
        cout << "For a k value of " << k << ", here is the information regarding its clusters:" << endl;
        kMeans.runClusterForK(k);
        for(i = 1; i <= k; i++)
        {
            clusterSize = kMeans.getClusterSize(i);
            nearest = kMeans.getNearestToCentroid(i);
            cout << "Cluster " << i << " contains " << clusterSize << " points and the point " << nearest.getId() << " is closest to its centroid." << endl;
        }
        long double dunnIndex =  runDunnIndex(kMeans.transferClusterForDunnIndex());
        cout << "The Dunn index for a k value of " << k << " is " << dunnIndex << endl;

        if(dunnIndex > highestKMeansDIndex)
        {
            highestKMeansDIndex = dunnIndex;
            highestKMeansDIndex_ID = k;
        }
    }
}