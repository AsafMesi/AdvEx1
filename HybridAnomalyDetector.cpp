//
// Created by asaf4 on 12/12/2021.
//


#include "HybridAnomalyDetector.h"

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
        learnNormalHelper(ts);

        // delete every cf that has correlation less than CIRCLE_CORRELATION
        auto isHybrid = [](correlatedFeatures e) {return e.corrlation > CIRCLE_CORRELATION;};
        cf.erase(std::remove_if(begin(cf), end(cf), isHybrid), end(cf));

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



