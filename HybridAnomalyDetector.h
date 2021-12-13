//
// Created by asaf4 on 12/12/2021.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H
#define ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
protected:
    void circleInit(int i, const TimeSeries& ts);
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    bool exceeding(Point p,const correlatedFeatures &current) override;

};

#endif //ANOMALY_DETECTION_UTIL_CPP_HYBRIDANOMALYDETECTOR_H
