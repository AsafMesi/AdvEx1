//
// Created by asafmesi on 10/21/21.
//

#ifndef ADVEX1_ANOMALY_DETECTION_UTIL_H
#define ADVEX1_ANOMALY_DETECTION_UTIL_H
#include "vector"

//returns the variance of X and Y
float var(float* x, int size);

// returns the covariance of X and Y
float cov(float* x, float* y, int size);

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size);

class Line{
public:
    float a,b;
    Line():a(0),b(0){}
    Line(float a, float b):a(a),b(b){}
    float f(float x){
        return a*x+b;
    }
};

class Point{
public:
    float x,y;
    Point(float x, float y):x(x),y(y){}
};

std::vector<Point*> createPointVector (std::vector<float> x, std::vector<float> y, int size);

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);

// returns the deviation between point p and the line
float dev(Point p,Line l);

float maxDev(Point** points,  int size, Line &l);

#endif //ADVEX1_ANOMALY_DETECTION_UTIL_H
