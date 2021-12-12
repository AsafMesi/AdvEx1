
#include "minCircle.h"
// C++ program to find the minimum enclosing
// circle for N integer points in a 2-D plane
#include "anomaly_detection_util.h"
#include <assert.h>
#include <math.h>
#include <vector>
using namespace std;

// Function to return the euclidean distance
// between two points
// distance((x1,y1), (x2,y2)) = sqrt( (x2-x1)^2 + (y2-y1)^2 )
float distance(const Point& a, const Point& b)
{
    float xDif = (a.x-b.x)*(a.x-b.x);
    float yDif = (a.y-b.y)*(a.y-b.y);
    return sqrt(xDif+yDif);
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
// if point p is at most radius + 1 away from C.center
bool isInside(const Circle& c, const Point& p)
{
    return distance(c.center, p) < (c.radius + 1);
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.

// Helper method to get a circle defined by 3 points
// given three points that are not on the same line - there is a unique circle which those three points on it's edge.
// (x1 - h)^2 + (y1 - k)^2 = r^2
// (x2 - h)^2 + (y2 - k)^2 = r^2
// (x3 - h)^2 + (y3 - k)^2 = r^2
// by solving for h,k we get the center of the circle (h,k)
Point getCircleCenter(float bx, float by, float cx, float cy)
{
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return { (cy * B - by * C) / (2 * D),
             (bx * C - cx * B) / (2 * D) };
}

// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point& A, const Point& B,
                   const Point& C) {
    Point I = getCircleCenter(B.x - A.x, B.y - A.y,
                              C.x - A.x, C.y - A.y);

    I.x += A.x;
    I.y += A.y;
    return {I, distance(I, A)};
}




// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point A, const Point B)
{
    float cx = A.x + B.x / 2;
    float cy = A.y + B.y / 2;
    // Set the center to be the midpoint of A and B
    Point C = { cx, cy };

    // Set the radius to be half the distance AB
    return {C, distance(A, B) / 2 };
}

// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle& c,
                     const vector<Point>& P)
{

    // Iterating through all the points
    // to check whether the points
    // lie inside the circle or not
    for (const Point& p : P)
        if (!isInside(c, p))
            return false;
    return true;
}

// Function to return the minimum enclosing
// circle for N <= 3
Circle baseCase(vector<Point>& P)
{
    assert(P.size() <= 3);
    if (P.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (P.size() == 1) {
        return { P[0], 0 };
    }
    else if (P.size() == 2) {
        return circle_from(P[0], P[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle findMinCircleHelper(vector<Point>& P,
                           vector<Point> R, int n)
{
    // if all points processed or |R| = 3, return result
    if (n == 0 || R.size() == 3) {
        return baseCase(R);
    }

    // Pick a random point randomly
    int idx = rand() % n;
    Point p = P[idx];

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[n - 1]);

    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = findMinCircleHelper(P, R, n - 1);

    // If d contains p, return d
    if (isInside(d, p)) {
        return d;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return findMinCircleHelper(P, R, n - 1);
}

Circle findMinCircle(Point** points, size_t size)
{
    vector<Point> P_copy = arrToVect(points, size);
    return findMinCircleHelper(P_copy, {}, P_copy.size());
}


