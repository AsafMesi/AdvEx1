/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

#include "HybridAnomalyDetector.h"
#define CIRCLE_CORRELATION 0.5
#define PRECISION 1.1

HybridAnomalyDetector::HybridAnomalyDetector() = default;

HybridAnomalyDetector::~HybridAnomalyDetector() = default;

/**
 * @param ts is a reference to a TimeSeries object.
 *
 * This function take ts object with a given data that considers to be normal data,
 * and model it's mode.
 * That way, when live data will be analyzed, ts will have this data to compare with,
 * and in some cases report an anomaly.
 */
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

/**
 * @param i is the index of the correlated feature in the correlated features vector (=cf).
 * @param ts is the Time Series object containing cf.
 */
void HybridAnomalyDetector:: circleInit(int i, const TimeSeries& ts){
    vector<float> xVec = ts.getFeatureData(cf[i].feature1);
    vector<float> yVec = ts.getFeatureData(cf[i].feature2);
    vector<Point*> pVec = createPointVector(xVec, yVec, ts.getNumberOfRows());
    Point** points = pVec.data();
    cf[i].minCircle = findMinCircle(points, ts.getNumberOfRows());
    cf[i].threshold = PRECISION * cf[i].minCircle.radius;
}

/**
 * This function checks whether or not a given point is exceeding from the maximal allowed threshold.
 * If the correlation is smaller or equal than 0.9, it means that in the learn normal mode,
 * the correlated features are detected with a relation of enclosing circle closing them.
 * Therefore, the deviation will check if the distance of their MEC is bigger than allowed threshold.
 * Else, they are related with a linear regression, therefore we check deviation by calling dev.
 *
 * @param p is the point needed to check if exceeding from the defined correlation.
 * @param current is the correlated feature p is checked with.
 * @return true if exceeding, else false.
 */
bool HybridAnomalyDetector::exceeding(Point p,const correlatedFeatures &current) {
        if (current.corrlation <= 0.9){
            return distance(current.minCircle.center, p) > (current.threshold);
        }
        else {
            return (dev(p, current.lin_reg) > current.threshold);
        }
}

