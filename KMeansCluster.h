
#include <vector>
#include <map>
#include "DataStore.h"

using namespace std;

// This class will implement the k-means clustering algorithm for given data points, initial
// centroids for each of k in the range kMin, kMax
class KMeansCluster{
	
	public:
		// class constructor that takes the input parameters
		KMeansCluster(int kMin, int kMax, map <int, Data> myPoints, map <int, vector <int> > myCentroids);
		~KMeansCluster();
		
		// return the minimim k value
		int getKMin() { return kMin;}

		// return the maximum k value
		int getKMax() { return kMax; }

		// this method runs the k-means clustering algorithm for a given k
		void runClusterForK(int k);

        int getClusterSize(int clusterId);

        Data getNearestToCentroid(int clusterId);

        vector<cluster> transferClusterForDunnIndex();

        long double distance(Data , Data );

private:
		// input data points
		map <int, Data> myPoints;
		// input initial centroids
		map <int, vector <int> > myCentroids;
		// input k min
		int kMin;
		// input k max
		int kMax;

		// all clusters with their data points
		map<int, vector<int> > clusters;

		// centroid of all clusters
		map<int, Data> centroids;

        void computeCentroids();

        Data getClusterCentroid(int clusterId);

        vector<int> getClusterData(int clusterId);

};