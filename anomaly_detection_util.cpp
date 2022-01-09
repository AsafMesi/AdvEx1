/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

#include <cmath>
#include <vector>
#include "anomaly_detection_util.h"

/**
 * @param x is pointer to the 1st element in the array.
 * @param size is the size of the array.
 * @return the average of the values in the array.
 *
 * We divide every element in the size of the array to achieve maximum precision.
 */
float avg(const float* x, int size) {
    float avg = 0;
    for (int i = 0; i < size; ++i) {
        avg += (x[i])/(float(size));
    }
    return avg;
}

/**
 * @param x is the random variable represented as array.
 * @param size is the size of the array.
 * @return the variance of X.
 *
 * The covariance is calculated with this formula to achieve maximum precision.
 * We use the fact that arithmetic operations on small numbers give us more.
 * accuracy considering finite memory.
 * Summing all the multiplication before dividing with "size" can cause a division between two large numbers.
 * Instead in each iteration we divide the multiplication in "size", therefore minimizing deviation.
 */
float var(float* x, int size) {
    float var = 0;
    float u = avg(x, size);
    for (int i = 0; i < size; ++i) {
        var += (((x[i] - u) * (x[i] - u))) / (float)size;   // ((x_i - avg)^2)/N;
    }
    return var;
}

/**
 * @param x is the 1st random variable.
 * @param y is the 2nd random variable.
 * @param size is the size of both x and y.
 * @return the covariance of X and Y.
 *
 * for more info about the calculation precision, read "var" function documentation.
 */
float cov(float* x, float* y, int size){
    float cov = 0, xAvg, yAvg;
    xAvg = avg(x, size);
    yAvg = avg(y, size);
    for (int i = 0; i < size; ++i) {
        cov += (((x[i] - xAvg) * (y[i] - yAvg))) / float(size); // (((x_i - avg(x)) * ((y_i - avg(y)))/N
    }
    return cov;
}

/**
 * @param x is the 1st random variable.
 * @param y is the 2nd random variable.
 * @param size is the size of both x and y.
 * @return the Pearson correlation coefficient of X and Y.
 *
 * By definition pearson output will belong to the interval [-1,1].
 */
float pearson(float* x, float* y, int size) {
    float xSigma, ySigma;
    xSigma = sqrtf(var(x, size));  // sigma is the standard deviation.
    ySigma = sqrtf(var(y, size));
    return (cov(x, y, size) / (xSigma * ySigma));
}

/**
 * @param points is a pointer to array of Point pointers.
 * @param size is the size of "points" array.
 * @return linear regression line created by those points.
 *
 * For a line with slope a, and y-axis intersection b,
 * The linear regression will be:
 * a = (cov(x,y)/ var(x)).
 * b = avg(y) - (a * avg(x)).
 */
Line linear_reg(Point** points, int size) {
    float xValues[size], yValues[size], a, b, xAvg, yAvg;

    // extract x and y values to different arrays, and sums up both averages.
    for (int i = 0; i < size; ++i) {
        xValues[i] = points[i]->x;
        yValues[i] = points[i]->y;
    }
    xAvg = avg(xValues, size);
    yAvg = avg(yValues, size);
    a = (cov(xValues, yValues, size) / var(xValues, size));
    b = yAvg - (a * xAvg);
    return {a, b};
}

/**
 * @param p is a point.
 * @param points is a point array that defines linear regression.
 * @param size is the number of points in points array.
 * @return the deviation between point p and the linear regression line equation of the points.
 */
float dev(Point p,Point** points, int size){
    Line regLine = linear_reg(points, size);
    return dev(p, regLine);
}

/**
 * @param p is a point.
 * @param l is a line equation representing linear regression line.
 * @return the deviation between point p and the line.
 */
float dev(Point p,Line l){
    float fx = l.f(p.x);
    return std::fabs(fx-p.y);
}

/**
 * @param points is a point array of linear regression "l".
 * @param size is the number of points in points array.
 * @param l is the linear regression line created by "points".
 * @return the maximum deviation between "points" and their linear regression line "l".
 */
float maxDev(Point** points,  int size, Line &l){
    float max=0, curr;
    for (int i = 0; i < size; i++){
        curr = dev(*points[i], l);
        if (curr > max){
            max = curr;
        }
    }
    return max;
}
/**
 * @param x is the 1st vector.
 * @param y is the 2nd vector.
 * @param size is the size of both x and y.
 * @return vector of Pointers of Points in the form of -> (x_i, y_i).
 */
std::vector<Point*> createPointVector (std::vector<float> x, std::vector<float> y, int size) {
    std::vector<Point*> points;
    points.reserve(size);
    for (int i=0; i < size; i++) {
        auto *p = new Point(x[i], y[i]);
        points.push_back(p);
    }
    return points;
}

