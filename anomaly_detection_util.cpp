//
// Created by asafmesi on 10/21/21.
//
#include "iostream"
#include <cmath>
#include "anomaly_detection_util.h"


float avg(float* x, int size) {
    if(size == 0) {
        std::cout << "empty array\n" << std::endl;
        return 0;
    }
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum/float(size);
}

float var(float* x, int size) {
    float val = 0, sum = 0, u;
    for (int i = 0; i < size; ++i, x++) {
        val += val + powf(x[i], 2);
    }
    u = powf(avg(x, size), 2);
    val = val/float(size);
    return val-u;
}

float cov(float* x, float* y, int size){
    float sum = 0, mean1 = 0, mean2 = 0, a = 0, b = 0;

    for (int i = 0; i < size; ++i) {
        a += x[i];
        b += y[i];
    }
    mean1 = a / (float) size;
    mean2 = b / (float) size;

    for (int i = 0; i < size; ++i) {
        sum += (x[i] - mean1) * (y[i] - mean2);
    }
    return sum / (float) size;
}

float pearson(float* x, float* y, int size) {
    float covariance = cov(x, y, size);
    float xSigma = sqrtf(var(x, size)), ySigma = sqrtf(var(y, size));
    return (covariance / (xSigma * ySigma));
}

Line linear_reg(Point** points, int size) {
    float xValue[size], yValue[size], a, b, xAvg = 0, yAvg = 0;

    // extract x and y values to different arrays, and sums up both averages.
    for (int i = 0; i < size; i++) {
        xValue[i] = points[i]->x;
        yValue[i] = points[i]->y;

        xAvg += xValue[i];
        yAvg += yValue[i];
    }

    xAvg = xAvg / (float) size;
    yAvg = yAvg / (float)size;

    a = (cov(xValue, yValue, size) / var(xValue, size));
    b = yAvg - (a * xAvg);

    return {a, b};
}

float dev(Point p,Point** points, int size){
    Line regLine = linear_reg(points, size);
    return dev(p, regLine);
}

float dev(Point p,Line l){
    float fx = l.f(p.x);
    return fabs(fx-p.y);
}
