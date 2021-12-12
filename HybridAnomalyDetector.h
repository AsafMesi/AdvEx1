//
// Created by DanMa on 11/12/2021.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H


#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */

#define ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H

#endif //ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H
