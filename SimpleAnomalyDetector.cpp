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
#define LINEAR_CORRELATION 0.9

SimpleAnomalyDetector::SimpleAnomalyDetector() = default;

/**
 * @param ts is a reference to a TimeSeries object.
 *
 * This function take ts object with a given data that considers to be normal data,
 * and model it's mode.
 * That way, when live data will be analyzed, ts will have this data to compare with,
 * and in some cases report an anomaly.
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

    // fill cf without type, correlation > MIN_CORRELATION_VALUE
    learnNormalHelper(ts, LINEAR_CORRELATION);

    /*
     * Goes through each correlated features found in learnNormalHelper
     * and initialize its members.
     */
    int size = cf.size();
    for (int i=0; i<size; i++){
        linearInit(i, ts);
    }
}

void SimpleAnomalyDetector::linearInit(int i, const TimeSeries& ts){
    vector<float> xVec = ts.getFeatureData(cf[i].feature1);
    vector<float> yVec = ts.getFeatureData(cf[i].feature2);
    vector<Point*> pVec = createPointVector(xVec, yVec, ts.getNumberOfRows());
    cf[i].lin_reg = linear_reg(&pVec[0], ts.getNumberOfRows());
    cf[i].threshold = PRECISION * maxDev(&pVec[0], ts.getNumberOfRows(), cf[i].lin_reg);
}

/**
 * @param ts is a reference to a TimeSeries object.
 * @param minCorrelation is the minimum threshold to declare correlation.
 *
 * For features i,j s.t j > i (as seen in the nested for loop):
 * check if the pearson between them is larger than the given minCorrelation.
 * If does, it means the features have correlation.
 * Therefore add it to the Detector correlated features vector with the needed data.
 */
void SimpleAnomalyDetector::learnNormalHelper(const TimeSeries& ts, float minCorrelation){

    // set up
    vector<string> features = ts.getFeatures();
    int c; // if equals (-1) no correlation found.
    float m;
    vector<float> cVec, xVec;

    /*
     * For each feature - goes through all features and get maximal correlative feature.
     */
    for (int i = 0; i < ts.getNumberOfFeatures(); i++) {
        m = minCorrelation; // a floor limit to declare correlation.
        c = (-1);
        xVec = ts.getFeatureData(features[i]);
        for(int j = (i+1); j < ts.getNumberOfFeatures(); j++) {
            vector<float> yVec = ts.getFeatureData(features[j]);
            //pearson(x, y, ts.getNumberOfRows());
            float p = fabs(pearson(&xVec[0], &yVec[0], ts.getNumberOfRows()));
            if (p > m) {
                m = p; c = j;
                cVec = yVec;
            }
        }
        correlatedFeatures temp = {};

        /*
         * If found correlative feature - add them to the correlation feature vector.
         */
        if (c != -1) {
            temp.corrlation = m;
            temp.feature1 = features[i];
            temp.feature2 = features[c];
            cf.push_back(temp);
        }
    }
}

/**
 * @param p is the point needed to check if exceeding from the defined correlation.
 * @param current is the correlated feature p is checked with.
 * @return true if exceeding, else false.
 *
 * This function checks if a given point p is exceeding from the allowed threshold.
 */
bool SimpleAnomalyDetector::exceeding(Point p, const correlatedFeatures &current) {
    return (dev(p, current.lin_reg) > current.threshold);
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
void SimpleAnomalyDetector::addReport(vector<AnomalyReport> &reports, const correlatedFeatures &current
                                        ,const TimeSeries& ts) {
    long timeStep = 1;
    vector<float> cf1Vec = ts.getFeatureData(current.feature1);
    vector<float> cf2Vec = ts.getFeatureData(current.feature2);
    int size = (int) cf1Vec.size();
    vector<Point *> points = createPointVector(cf1Vec, cf2Vec, size);
    for (Point *p: points){
        if(exceeding(*p, current)){
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



