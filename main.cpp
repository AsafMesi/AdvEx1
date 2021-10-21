#include <iostream>
#include "anomaly_detection_util.h"

int main() {
    float  arr1[] = {10.5, 9.2, 8.1, 7.6, 6.2};
    float arr2[] = {1.2, 2.1, 3.1, 4.6, 5.2};

    // should be =~ -2.1108
    std :: cout << cov(arr1, arr2, 5) << std :: endl;

    // should be =~ 2.1176
    std :: cout << var(arr1, 5) << std :: endl;

    // should be =~ 2.2344
    std :: cout << var(arr2, 5) << std :: endl;

    // should be =~ -0.970386...
    std :: cout << pearson(arr1, arr2, 5) << std :: endl;
}
