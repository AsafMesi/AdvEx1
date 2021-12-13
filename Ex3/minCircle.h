//
// Created by DanMa on 11/12/2021.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_MINCIRCLE_H
#define ANOMALY_DETECTION_UTIL_CPP_MINCIRCLE_H


#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <cassert>
#include <cmath>
#include <vector>
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
    Circle():center(0,0),radius(0){}
};
// --------------------------------------

Circle findMinCircle(Point** points, size_t size);

// you can add here additional methods
Circle findMinCircleHelper(vector<Point>& P, vector<Point> R, int n);
Circle baseCase(vector<Point>& P);
bool is_valid_circle(const Circle& c, const vector<Point>& P);
Circle circle_from(Point A, Point B);
Circle circle_from(const Point& A, const Point& B, const Point& C);
Point getCircleCenter(float bx, float by, float cx, float cy);
bool isInside(const Circle& c, const Point& p);
float distance(const Point& a, const Point& b);




#endif /* MINCIRCLE_H_ */


#endif //ANOMALY_DETECTION_UTIL_CPP_MINCIRCLE_H
