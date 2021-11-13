/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

#include "SimpleAnomalyDetector.h"
#define PRECISION 1.1

SimpleAnomalyDetector::SimpleAnomalyDetector() = default;

/**
 * @param ts is a reference to a TimeSeries object.
 *
 * For features i,j s.t j > i (as seen in the nested for loop):
 * check if the pearson between them is larger than 'm' - which mean the features have correlation.
 * if so add it to the Detector correlated features vector with the needed data.
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    vector<string> features = ts.getFeatures();
    int c; // if equals (-1) no correlation found.
    float m;
    vector<float> cVec, xVec;
    for (int i = 0; i < ts.getNumberOfFeatures(); i++) {
        m = 0.9; // a floor limit to declare correlation.
        c = (-1);
        xVec = ts.getFeatureData(features[i]);
        for(int j = (i+1); j < ts.getNumberOfFeatures(); j++) {
            vector<float> yVec = ts.getFeatureData(features[j]);
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
                temp.lin_reg = linear_reg(&pVec[0], ts.getNumberOfRows());
                temp.threshold = PRECISION * maxDev(&pVec[0], ts.getNumberOfRows(), temp.lin_reg);
                cf.push_back(temp);
            }
        }
    }

/**
 * @param reports is the Anomaly Reports vector that gathers all anomalies so far.
 * @param current is the current correlated features to check for anomalies.
 * @param ts is the reference to the TimeSeries object.
 *
 * This function is an util function which creates a report that contains an anomaly, detected
 * by our anomaly detector and prints its description.
 * The function adds the report to the Anomaly Reports vector, "reports",
 * that contains all anomalies that occurred so far.
 * Each report contains description and timeStep of the anomaly.
 */
void addReport(vector<AnomalyReport> &reports, const correlatedFeatures &current
                                        ,const TimeSeries& ts) {
    long timeStep = 1;
    vector<float> cf1Vec = ts.getFeatureData(current.feature1);
    vector<float> cf2Vec = ts.getFeatureData(current.feature2);
    int size = (int) cf1Vec.size();
    vector<Point *> points = createPointVector(cf1Vec, cf2Vec, size);
    float temp;
    for (Point* p : points) {
        temp = dev(*p, current.lin_reg);
        if ( temp > current.threshold) {
            string description = current.feature1 + "-" + current.feature2;
            reports.emplace_back(description, timeStep);
        }
        timeStep++;
    }
}

/**
 * @param ts is a reference to a TimeSeries object.
 * @return vector of Anomaly Reports.
 *
 * This function gets a reference to a TimeSeries object, and scans it for anomalies.
 * If anomaly detected - create a report of the anomaly, and adds it to "reports".
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> reports;
    for (const correlatedFeatures& current: this->cf) {
        addReport(reports, current, ts);
    }
    return reports;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;



