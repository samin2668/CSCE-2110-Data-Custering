
#ifndef DATA_H

//This class will be used to create objects for the data points


class Data
{
    //x and y cords using long double to be able to store large floating point nums
private:
    long double x;
    long double y;
    int id;
    int clusterId;
public:
    //getters setters constructor and destructor
    Data();
    Data(long double X, long double Y);
    ~Data();
    void setX(long double num);
    long double getX();
    void setY(long double num);
    long double getY();
    void setId(int id) { this->id = id;};
    int getId() const { return id;};
    void setClusterId(int clusterId){ this->clusterId = clusterId;}
    int getClusterId(){ return clusterId;}

};

#endif


