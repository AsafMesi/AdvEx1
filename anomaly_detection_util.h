/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

#ifndef ADVEX1_ANOMALY_DETECTION_UTIL_H
#define ADVEX1_ANOMALY_DETECTION_UTIL_H
#include "vector"

using namespace std;

// 'a' is the slope, 'b' is the y-axis intersection.
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

float var(float* x, int size);
float cov(float* x, float* y, int size);
float pearson(float* x, float* y, int size);
Line linear_reg(Point** points, int size);
float dev(Point p,Point** points, int size);
float dev(Point p,Line l);
float maxDev(Point** points,  int size, Line &l);
std::vector<Point*> createPointVector (std::vector<float> x, std::vector<float> y, int size);


#endif //ADVEX1_ANOMALY_DETECTION_UTIL_H
