

#ifndef ANOMALYDETECTOR_H_
#define ANOMALYDETECTOR_H_

#include <string>
#include <vector>
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "minCircle.h"
#include <cmath>
using namespace std;
struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    float threshold;
    Line lin_reg;
    Circle minCircle;

};

class AnomalyReport{
public:
	const string description;
	const long timeStep;
	AnomalyReport(string description, long timeStep):description(description),timeStep(timeStep){}

    friend ostream& operator<<(ostream& os, const AnomalyReport &ar ) {
        os << ar.description + to_string(ar.timeStep);
        return os;
    }
};

class TimeSeriesAnomalyDetector {
public:
	virtual void learnNormal(const TimeSeries& ts)=0;
	virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    // get corrleation
	virtual ~TimeSeriesAnomalyDetector()= default;
};

#endif /* ANOMALYDETECTOR_H_ */
