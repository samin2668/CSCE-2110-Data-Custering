//
// Created by Andrew on 10/26/2019.
//

#include "centroidClustering.h"

map<int,Data> points;

vector<cluster> clusters;


//run Centroid Linkage clustering on a set of data points coming from DataStore
pair<int, long double> runCentroidClustering(map<int,Data> newPoints)
{
    int level = 0;
    points = newPoints;
    int bestDunnIndexClusterCount;
    long double bestDunnIndex = 0;

    generateClusters();

    vector<pair<pair<int,int>,long double>> clusterDists;
    int count = 0;

    cout << "For centroid-linkage clustering: " << endl;

    //while loop that runs while the count of the clusters is not equal to 1
    while(count != 1) {

        //reset count and clusterDists for the current iteration
        clusterDists.clear();
        count = 0;


        //count the number of clusters that are not merged into other clusters
        for(auto iter: clusters)
        {
            if(iter.getClusterId() != -1)
            {
                count++;
            }
        }

        //output information at every 10 levels
        if(level % 10 == 0)
        {

            //if over half of the clusters have been merged, begin outputting the Dunn Index
            if(count < (clusters.size()/2) && count != 1)
            {
                cout << "Hierarchy level " << level << " with " << count << " clusters inside";
                long double dunnIndex = runDunnIndex(clusters);
                if(dunnIndex > bestDunnIndex)
                {
                    bestDunnIndexClusterCount = count;
                    bestDunnIndex = dunnIndex;
                }
                cout << " and a Dunn index of " << dunnIndex << endl;
            }
            else
            {
                cout << "Hierarchy level " << level << " with " << count << " clusters inside" << endl;
            }

        }



        //loop through the clusters and grab the X1/Y1 cluster
        for (auto it: clusters) {
            //check if the cluster being observed has not already been merged
            if (it.getClusterId() != -1) {
                    //loop through the clusters again and grab the X2/Y2 cluster
                    for (auto it2: clusters) {

                        //make sure that the 2 clusters are not the same while also not being already merged
                        if (it2.getClusterId() != it.getClusterId() && it2.getClusterId() != -1) {

                            it.generateCentroid();
                            it2.generateCentroid();

                            //add the distance between the 2 clusters to the map of cluster distances
                                clusterDists.emplace_back(make_pair(it.getClusterId(), it2.getClusterId()),
                                                          pow(pow(it2.getCenterX() - it.getCenterX(), 2) +
                                                              pow(it2.getCenterY() - it.getCenterY(), 2), 0.5));

                        }
                    }
                }
            }

        //sort the cluster distances by the smallest distance value
        sort(clusterDists.begin(),clusterDists.end(),checkPairs);

        //merge the two clusters with the smallest distance and check for ties in the distance and merge accordingly
        if(!clusterDists.empty()) {
            int sameClusterCount = 0;
            float smallestAvgID;
            int savedClusterDistsIndex = 0;
            if (clusterDists.at(0).second != clusterDists.at(1).second) {
                mergeClusters(clusters.at(clusterDists.at(0).first.first - 1),
                              clusters.at(clusterDists.at(0).first.second - 1));
            }
            else
            {
                //counts the number of clusters that share the same distance
                for(int i = 1; i < clusterDists.size(); i++) {
                    if (clusterDists.at(0).second == clusterDists.at(i).second)
                    {
                        sameClusterCount++;
                    }
                }
            }
            //merges clusters with the same distance based on their the average of their IDs
            if(sameClusterCount != 0)
            {
                //special case for when there are 2 clusters left
                if(clusterDists.size() == 2)
                {
                    mergeClusters(clusters.at(clusterDists.at(0).first.first - 1),
                                  clusters.at(clusterDists.at(0).first.second - 1));
                    break;
                }
                smallestAvgID = (clusterDists.at(0).first.first + clusterDists.at(0).first.second)/2.000;
                for(int i = 1; i < sameClusterCount; i++) {
                    if((clusterDists.at(i).first.first + clusterDists.at(i).first.second)/2.000 <= smallestAvgID)
                    {
                        smallestAvgID = (clusterDists.at(i).first.first + clusterDists.at(i).first.second)/2.000;
                        savedClusterDistsIndex = i;
                    }
                }
                mergeClusters(clusters.at(clusterDists.at(savedClusterDistsIndex).first.first - 1),clusters.at(clusterDists.at(savedClusterDistsIndex).first.second - 1));
            }

            }


        //increment level before starting the while loop again
        level++;
    }
        //when the level is equal to the number of clusters - 1, we have reached the end where there should be only 1 cluster remaining
        return make_pair(bestDunnIndexClusterCount,bestDunnIndex);
    }

//generate a cluster for each point in points
void generateClusters()
{
    for(auto it: points)
    {
        clusters.emplace_back(it.first,it.second);
    }
}

//merge 2 clusters and mark the cluster with the greater ID with a -1
void mergeClusters(cluster clusterA, cluster clusterB)
{
    map<int,Data> mergePoints;
    cluster newClusterB; //new cluster object to replace the old one with if the old one gets tombstoned
    cluster newClusterA; //new cluster object to replace the old one with if the old one gets tombstoned

    //loop through both point vectors from each cluster and put every point into a single map
    for(auto it: clusterA.getPoints())
    {
        mergePoints.emplace(it.first,it.second);
    }
    for(auto it: clusterB.getPoints())
    {
        mergePoints.emplace(it.first,it.second);
    }

    //if cluster A has the smaller ID, tombstone cluster B
    if(clusterA.getClusterId() < clusterB.getClusterId())
    {
        //set newClusterB to clusterB and set its ID to -1
        newClusterB = clusterB;
        newClusterB.setClusterId(-1);

        //set the points in clusterA to the map of merged points
        clusterA.setPoints(mergePoints);

        //update 'clusters' vector
        clusters.at(clusterA.getClusterId()-1) = clusterA;
        clusters.at(clusterB.getClusterId()-1) = newClusterB;
    }

    //opposite of above
   else if(clusterB.getClusterId() < clusterA.getClusterId())
    {
        newClusterA = clusterA;
        newClusterA.setClusterId(-1);
        clusterB.setPoints(mergePoints);
        clusters.at(clusterB.getClusterId()-1) = clusterB;
        clusters.at(clusterA.getClusterId()-1) = newClusterA;
    }
}





