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
