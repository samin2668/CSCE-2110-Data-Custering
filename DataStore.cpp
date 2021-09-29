#include "DataStore.h"
//map to contain the data points
map <int, Data> myPoints;
//map to contain the centroids 
map <int, vector <int> > myCentroids;

// minimum value of k 
int kMin;

// maximum value of k
int kMax;


//this function will read from the config and points file and store all the data
void getPoints()
{
    //file streams
    ifstream config;
    ifstream points;
    //temp values
    string file;
    string temp;
    //int MIN;
    //int MAX;
    int Kval;
    int centroid;

    long double x, y;
    int ID;
    //getting config file
    cout << "Please enter the name of the configuration file:";
    cin >> file;
    config.open(file);
    if(config.fail()){
        cout << "Error opening config file...\n";
        exit(0);
    }

    getline(config, file, ':');
    getline(config, file);
    //getting points file
    points.open(file);
    if(points.fail())
        cout << "Error opening points file...\n";
    //reading in all the points
    while(!points.eof())
    {
        points >> ID >> x >> y;
        Data tmp(x, y);
        tmp.setId(ID);
        tmp.setClusterId(-1);
        myPoints[ID] = tmp;
    }

    //getting min max k-value
    points.close();
    getline(config, temp, ':');
    getline(config, temp);
    kMin = stoi(temp);
    getline(config, temp, ':');
    getline(config, temp);
    kMax = stoi(temp);



    while(Kval != kMax)
    {
        //storing centroids and k-value data
       getline(config, temp, ':');
       Kval = stoi(temp);
       getline(config, temp);
       stringstream str(temp);
       while(str >> centroid)
       {
           myCentroids[Kval].push_back(centroid);
       }
    }
    //closing files
    config.close();
    points.close();

}