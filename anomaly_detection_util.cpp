//
// Created by asafmesi on 10/21/21.
//
#include "iostream"
#include <cmath>
#include <vector>
#include "anomaly_detection_util.h"

// calculates the average of x array.
float avg(float* x, int size) {
    float avg = 0;
    for (int i = 0; i < size; ++i) {
        avg += (x[i])/(float(size));
    }
    return avg;
}

//returns the variance of X and Y, output will be non-negative number by definition.
float var(float* x, int size) {
    float var = 0;
    float u = avg(x, size);
    for (int i = 0; i < size; ++i) {
        float temp = (x[i] - u);   // x_i - avg
        temp = powf(temp, 2);  // (x_i - avg)^2
        temp = temp/float(size);  //  ((x_i - avg)^2)/N
        var += temp;
    }
    return var;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float cov = 0, xAvg, yAvg;
    xAvg = avg(x, size);
    yAvg = avg(y, size);
    for (int i = 0; i < size; ++i) {
        cov += (((x[i] - xAvg) * (y[i] - yAvg))) / float(size);
    }
    return cov;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    float covariance, xSigma, ySigma;
    covariance = cov(x, y, size);
    xSigma = sqrtf(var(x, size));
    ySigma = sqrtf(var(y, size));
    return (covariance / (xSigma * ySigma));
}

// create
std::vector<Point*> createPointVector (std::vector<float> x, std::vector<float> y, int size) {
    std::vector<Point*> points;
    for (int i=0; i < size; i++) {
        Point *p = new Point(x[i], y[i]);
        points.push_back(p);
    }
    return points;
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {
    float xValue[size], yValue[size], a, b, xAvg, yAvg;

    // extract x and y values to different arrays, and sums up both averages.
    for (int i = 0; i < size; ++i) {
        xValue[i] = points[i]->x;
        yValue[i] = points[i]->y;
    }
    xAvg = avg(xValue, size);
    yAvg = avg(yValue, size);
    a = (cov(xValue, yValue, size) / var(xValue, size));
    b = yAvg - (a * xAvg);
    return {a, b};
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line regLine = linear_reg(points, size);
    return dev(p, regLine);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    float fx = l.f(p.x);
    return fabs(fx-p.y);
}

// returns the maximum deviation between an array of points and their linear regression line

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
