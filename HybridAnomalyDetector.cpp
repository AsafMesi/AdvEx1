//
// Created by asaf4 on 12/12/2021.
//


#include "HybridAnomalyDetector.h"
#include "minCircle.h"

#define CIRCLE_CORRELATION 0.5
#define PRECISION 1.1

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){

        // fill cf without type, correlation > MIN_CORRELATION_VALUE
        learnNormalHelper(ts, CIRCLE_CORRELATION);
        int size = cf.size();
        for (int i=0; i<size; i++){
            if (cf[i].corrlation <= 0.9){
                circleInit(i, ts);
        }
            else {
                linearInit(i, ts);
            }
    }
}

void HybridAnomalyDetector:: circleInit(int i, const TimeSeries& ts){
    vector<float> xVec = ts.getFeatureData(cf[i].feature1);
    vector<float> yVec = ts.getFeatureData(cf[i].feature2);
    vector<Point*> pVec = createPointVector(xVec, yVec, ts.getNumberOfRows());
    Point** points = pVec.data();
    cf[i].minCircle = findMinCircle(points, ts.getNumberOfRows());
    cf[i].threshold = PRECISION * cf[i].minCircle.radius;
}

bool HybridAnomalyDetector::exceeding(Point p,const correlatedFeatures &current) {
        if (current.corrlation <= 0.9){
            return distance(current.minCircle.center, p) > (current.threshold);
        }
        else {
            return (dev(p, current.lin_reg) > current.threshold);
        }
}

