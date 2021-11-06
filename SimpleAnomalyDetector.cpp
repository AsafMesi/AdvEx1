
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->cf = new vector<correlatedFeatures>;

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){

}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

