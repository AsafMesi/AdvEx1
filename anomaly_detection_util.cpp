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
        sum += sum + x[i];
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
    float testArr1[size], testArr2[size];

    for (int i = 0; i < size; ++i) {
        a += x[i];
        b += y[i];
    }
    mean1 = a / (float) size;
    mean2 = b / (float) size;

    for (int i = 0; i < size; ++i) {

        //test
        testArr1[i] = x[i] - mean1;
        testArr2[i] = y[i] - mean2;

        sum += (x[i] - mean1) * (y[i] - mean2);
    }
    return sum / (float) size;
}

float pearson(float* x, float* y, int size) {
    float covariance = cov(x, y, size);
    float xSigma = sqrtf(var(x, size)), ySigma = sqrtf(var(y, size));
    return (covariance / (xSigma * ySigma));
}
