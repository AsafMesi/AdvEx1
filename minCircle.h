/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */


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

    friend ostream& operator<<(ostream& os, const Circle &c ) {
        os << "Center: (" + to_string(c.center.x) + ", " + to_string(c.center.y) + "), " +
              "Radius: " +to_string(c.radius);
        return os;
    }
};
// --------------------------------------

Circle findMinCircle(Point** points, size_t size);
float distance(Point a, Point b);


#endif /* MINCIRCLE_H_ */

