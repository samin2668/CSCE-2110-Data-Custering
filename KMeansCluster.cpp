

#include "KMeansCluster.h"

KMeansCluster::KMeansCluster(int kMin, int kMax, map <int, Data> myPoints, map <int, vector <int> > myCentroids)
{
	this->kMin = kMin;
	this->kMax = kMax;
	this->myPoints = myPoints;
	this->myCentroids = myCentroids;
}

KMeansCluster::~KMeansCluster() {

}

void KMeansCluster::runClusterForK(int k)
{
	// empty the clusters
	clusters.clear();
	// empty the centroids
	centroids.clear();
	int i;
	map<int, Data> nextClusters;

	// initialize the centroids with given parameter values for k
	for(i = 0; i < k; i++)
	{
		int dataPtId = myCentroids[k][i];
		Data dataPt = myPoints[dataPtId];
		centroids[i+1] = dataPt;
	}

	// continue clustering until there is no change
	while(true)
	{
		bool clusterHasChanged = false;
		// empty the clusters
		clusters.clear();

		// process all the input data points
		for(i = 1 ; i <= myPoints.size(); i++)
		{
			// get the next data
			Data *pt = &(myPoints[i]);
			// compute the centroid to which it is closest
			long double minDist = 999999;
			int closestCentroidId;
			for(int j = 1; j <= k; j++)
			{
				Data aCentroid = centroids[j];
				long double dist = distance(aCentroid, *pt);
				if(dist < minDist)
				{
					minDist = dist;
					closestCentroidId = j;
				}
			}
			// update the cluster change flag
			if(pt->getClusterId() != closestCentroidId)
			{
				clusterHasChanged = true;
				pt->setClusterId(closestCentroidId);
			}
			// add the point to respective cluster
			if(clusters.find(closestCentroidId) == clusters.end())
			{
				vector<int> *pointIds = new vector<int>();
				clusters[closestCentroidId] = *pointIds;
			}
			clusters[closestCentroidId].push_back(pt->getId());
		}
		// terminate if there is no change of cluster for any point
		if(!clusterHasChanged) break;
		// recompute the centroids
		computeCentroids();
	}

}

Data KMeansCluster::getNearestToCentroid(int clusterId)
{
	vector<int> cluster = clusters[clusterId];
	Data centroid = centroids[clusterId];
	Data nearest = myPoints[cluster[0]];
	long double minDist = 999999999;
	// iterate over all all data points in cluster
	for(int i = 0; i < cluster.size(); i++)
	{
		// get the next point from cluster
		Data pt = myPoints[cluster[i]];
		// compute its distance from cluster centroid
		long double dist = distance(pt, centroid);
		// update min distance
		if( dist < minDist)
		{
			nearest = pt;
			minDist = dist;
		}
	}
	return nearest;
}

int KMeansCluster::getClusterSize(int clusterId)
{
	return clusters[clusterId].size();
}

vector<int> KMeansCluster::getClusterData(int clusterId)
{
	return clusters[clusterId];
}

Data KMeansCluster::getClusterCentroid(int clusterId)
{
	return centroids[clusterId];
}

void KMeansCluster::computeCentroids()
{
	centroids.clear();
	int k = clusters.size();

	for(int clusterId = 1; clusterId <= k; clusterId++)
	{
		long double sumX = 0;
		long double sumY = 0;
		vector<int> points = clusters[clusterId];
		for(int j = 0; j < points.size(); j++)
		{
			int ptId = points[j];
			Data pt = myPoints[ptId];
			sumX += pt.getX();
			sumY += pt.getY();
		}
		long double centroidX = sumX/(long double)points.size();
		long double centroidY = sumY/(long double)points.size();
		Data *cpt = new Data(centroidX, centroidY);
		centroids[clusterId] = *cpt;
	}
}

vector<cluster> KMeansCluster::transferClusterForDunnIndex() {
    vector<cluster> returnClusters;
    int clusterID;
    map<int,Data> returnPoints;
    for(auto it: clusters)
    {
        for(auto it2: it.second)
        {
            returnPoints.emplace(it2,myPoints.at(it2));
        }
        cluster newClust;
        newClust.setClusterId(it.first);
        newClust.setPoints(returnPoints);
        returnClusters.push_back(newClust);
        returnPoints.clear();
    }

    return returnClusters;
}

// Calculate the distance between two Data
long double KMeansCluster::distance(Data pt1, Data pt2)
{
    long double dx = pt1.getX() - pt2.getX();
    long double dy = pt1.getY() - pt2.getY();
    long double dist = sqrt(dx * dx +  dy * dy);
    return dist;
}




