
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() = default;

SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;

/**
 * This function gets a TimeSeries object, and models it by learning
 * its normal data.
 *
 * @param ts is the reference to a TimeSeries object.
 */
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

    /**
     * This function is an util function that creates a report that contains an anomaly
     * detected by our anomaly detector and prints its description.
     * It adds the report to a given vector that contains all anomalies that occurred this far.
     * The anomaly contains description and timeStep of the anomaly.
     *
     * @param reports is the Anomaly Reports vector that gathers all anomalies so far.
     * @param current is the current corelated featurs to check anomailes with.
     * @param ts is the reference to the TimeSeries object.
     */
void addReport(vector<AnomalyReport> &reports, const correlatedFeatures &current
                                        ,const TimeSeries& ts) {
    long timeStep = 1;
    string cf1 = current.feature1;
    string cf2 = current.feature2;
    vector<float> cf1Vec = ts.getFeatureData(cf1);
    vector<float> cf2Vec = ts.getFeatureData(cf2);
    int size = (int) cf1Vec.size();
    vector<Point *> points = createPointVector(cf1Vec, cf2Vec, size);
    float temp;
    for (Point* p : points) {
        temp = dev(*p, current.lin_reg);
        if ( temp > current.threshold) {
            string description = current.feature1 + "-" + current.feature2 + "\n";
            reports.emplace_back(description, timeStep);
        }
        timeStep ++;
    }
}

/**
 * This function gets a reference to a TimeSeries object, and scans it
 * for anomalies.
 * If exception detected - create a report of the anomaly and saves it
 * into vector of reports.
 * Finally, returns all reports in a vector.
 *
 * @param ts is the reference to a TimeSeries object.
 * @return vector of Anomaly Reports.
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> reports;
    for (correlatedFeatures current: this->cf) {
        addReport(reports, current, ts);
    }
    return reports;
}



