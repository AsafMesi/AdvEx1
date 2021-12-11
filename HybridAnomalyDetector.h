//
// Created by asaf4 on 12/12/2021.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H
#define ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    void circleInit(correlatedFeatures &circleCf , const TimeSeries& ts); // todo - protected
};

#endif //ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H
