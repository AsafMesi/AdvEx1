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

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
    Circle minCircle;
	float threshold;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{

protected:
    vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector();
	virtual void learnNormal(const TimeSeries& ts);
    void learnNormalHelper(const TimeSeries& ts); // todo - private
    void linearInit(correlatedFeatures &linearCf ,const TimeSeries& ts); //todo - protected
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	vector<correlatedFeatures> getNormalModel(){ return cf;}
    virtual ~SimpleAnomalyDetector();
};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
