//
// Created by asafmesi on 10/21/21.
//
#include "iostream"
#include <cmath>
#include "anomaly_detection_util.h"

// calculates the average of x array.
float avg(float* x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum/float(size);
}

//returns the variance of X and Y, output will be non-negative number by definition.
float var(float* x, int size) {
    float val = 0, sum = 0, u;
    for (int i = 0; i < size; ++i) {
        val += powf(x[i], 2);
    }
    u = powf(avg(x, size), 2);
    val = val/float(size);
    return val-u;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float sum = 0, xAvg, yAvg;
    xAvg = avg(x, size);
    yAvg = avg(y, size);
    for (int i = 0; i < size; ++i) {
        sum += (x[i] - xAvg) * (y[i] - yAvg);
    }
    return sum / (float) size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    float covariance, xSigma, ySigma;
    covariance = cov(x, y, size);
    xSigma = sqrtf(var(x, size));
    ySigma = sqrtf(var(y, size));
    return (covariance / (xSigma * ySigma));
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
