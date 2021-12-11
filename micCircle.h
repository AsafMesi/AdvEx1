//
// Created by DanMa on 11/12/2021.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_MICCIRCLE_H
#define ANOMALY_DETECTION_UTIL_CPP_MICCIRCLE_H


#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */


#endif //ANOMALY_DETECTION_UTIL_CPP_MICCIRCLE_H
