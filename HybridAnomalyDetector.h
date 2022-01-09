/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

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
