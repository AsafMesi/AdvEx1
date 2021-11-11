
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() = default;

SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    vector<string> features = ts.getFeatures();
    int c; // if equals (-1) no correlation found.
    float m;
    vector<float> cVec, xVec;
    for (int i = 0; i < ts.getNumberOfFeatures(); i++) {
        m = 0.8;
        c = (-1);
        xVec = ts.getFeatureData(features[i]);
        //float *x = xVec.data();
        for(int j = (i+1); j < ts.getNumberOfFeatures(); j++) {
            vector<float> yVec = ts.getFeatureData(features[j]);
            //float *y = yVec.data();
            float p = fabs(pearson(&xVec[0], &yVec[0], ts.getNumberOfRows())); //pearson(x, y, ts.getNumberOfRows());
            if (p > m) {
                m = p; c = j;
                cVec = yVec;
            }
        }
        correlatedFeatures temp = {};
        if (c != -1) {
                temp.corrlation = m;
                temp.feature1 = features[i];
                temp.feature2 = features[c];
                vector<Point*> pVec = createPointVector(xVec, cVec, ts.getNumberOfRows());
                //Point** points = pVec.data();
                temp.lin_reg = linear_reg(&pVec[0], ts.getNumberOfRows());
                temp.threshold = maxDev(&pVec[0], ts.getNumberOfRows(), temp.lin_reg);
                cf.push_back(temp);
            }
        }
    }

void addReport(vector<AnomalyReport> &reports, const correlatedFeatures &current,
               vector<float> &cf1Vec, vector<float> &cf2Vec, int size){
    vector<Point*> points = createPointVector(cf1Vec, cf2Vec, size);
    for (Point* p: points){
        if (dev(*p, current.lin_reg) > current.threshold){
            string description = "Exeption in features: " + current.feature1 + "and " + current.feature2;
            const long timeStep = 0.1;
            reports.push_back(AnomalyReport(description, timeStep));
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> reports;
    for (correlatedFeatures current: this->cf){
        string cf1 = current.feature1;
        string cf2 = current.feature2;
        vector<float> cf1Vec = ts.getFeatureData(cf1);
        vector<float> cf2Vec = ts.getFeatureData(cf2);
        int size = (int)cf1Vec.size();
        addReport(reports, current, cf1Vec, cf2Vec, size);
    }
    return reports;
}



