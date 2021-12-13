//
// Created by asaf4 on 12/12/2021.
//


#include "HybridAnomalyDetector.h"
#include "minCircle.h"

#define CIRCLE_CORRELATION 0.5
#define PRECISION 1.1

HybridAnomalyDetector::HybridAnomalyDetector() {


}

HybridAnomalyDetector::~HybridAnomalyDetector() {

}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){

        // fill cf without type, correlation > MIN_CORRELATION_VALUE
        learnNormalHelper(ts, CIRCLE_CORRELATION);

        for (auto currentCf: cf){
            if (currentCf.corrlation <= 0.9){
                circleInit(currentCf, ts);
        }
            else {
                linearInit(currentCf, ts);
            }
    }
}

void HybridAnomalyDetector:: circleInit(correlatedFeatures &circleCf , const TimeSeries& ts){
    vector<float> xVec = ts.getFeatureData(circleCf.feature1);
    vector<float> yVec = ts.getFeatureData(circleCf.feature2);
    vector<Point*> pVec = createPointVector(xVec, yVec, ts.getNumberOfRows());
    Point** points = pVec.data();
    circleCf.minCircle = findMinCircle(points, ts.getNumberOfRows());
    circleCf.threshold = PRECISION * circleCf.minCircle.radius;
}

bool HybridAnomalyDetector::exceeding(Point p,const correlatedFeatures &current) {
        if (current.corrlation <= 0.9){
            return isInside(current.minCircle, p);
        }
        else {
            return (dev(p, current.lin_reg) > current.threshold);
        }
}

