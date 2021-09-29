

#include "Data.h"

Data::Data(){}
Data::Data(long double X, long double Y)
{
    x = X;
    y = Y;
}
Data::~Data(){}
//getters and setters
void Data::setX(long double num){x = num;}
long double Data::getX(){return x;}
long double Data::getY(){return y;}
void Data::setY(long double num){y = num;}