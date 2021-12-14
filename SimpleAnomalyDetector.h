/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include "timeseries.h"
#include "minCircle.h"
#include <ostream>

struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    float threshold;
    Line lin_reg;
    Circle minCircle;

};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{

protected:
    vector<correlatedFeatures> cf;
    void linearInit(int i, const TimeSeries& ts);
    void learnNormalHelper(const TimeSeries& ts, float minCorrelation);
    void addReport(vector<AnomalyReport> &reports, const correlatedFeatures &current, const TimeSeries& ts);
    virtual bool exceeding(Point p,const correlatedFeatures &current);
public:
	SimpleAnomalyDetector();
	vector<correlatedFeatures> getNormalModel(){ return cf;}
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    virtual ~SimpleAnomalyDetector();
};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
