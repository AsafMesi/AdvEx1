
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    vector<string> features = ts.getFeatures();
    int c;
    float max;
    vector<float> cVec;
    for (int i = 0; i < ts.getNumberOfFeatures(); i++) {
        max = 0;
        c = (-1);
        vector<float> xVec = ts.getFeatureData(features[i]);
        float *x = xVec.data();
        for(int j = (i+1); j < ts.getNumberOfFeatures(); j++) {
            vector<float> yVec = ts.getFeatureData(features[j]);
            float *y = yVec.data();
            float p = pearson(x, y, ts.getNumberOfRows());
            if (p > max) {
                max = p; c = j;
                cVec = yVec;
            }
        }
        correlatedFeatures temp = {};
        if (c != -1) {
            if (max > temp.threshold) {
                temp.corrlation = max;
                temp.feature1 = features[i];
                temp.feature2 = features[c];
                vector<Point*> pVec = createPointVector(xVec, cVec, ts.getNumberOfRows());
                Point** points = pVec.data();
                temp.lin_reg = linear_reg(points, ts.getNumberOfRows());
                cf.push_back(temp);
            }
        }
    }
}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

