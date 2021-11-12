#include <iostream>
#include "timeseries.h"
#include "AnomalyDetector.h"
#include "SimpleAnomalyDetector.h"

/** check print:
    for (int i = 0; i<data->getNumberOfFeatures(); i++){
        vector<float> v =  data->getFeatureData(data->getFeatures()[i]);
        float *ptr = &v[0];
        for (int i=0; i<data->getNumberOfRows(); i++) {
            cout << to_string(*ptr) + ", ";
            ptr++;
        }
        cout << endl;
        cout << " _______________________"  << endl;
    }
 */

int main(){
    //const char* name = R"(C:\Users\DanMa\CLionProjects\APProject\test.csv)";
    const char* name = R"(C:\Users\asaf4\CLionProjects\AdvEx2\test.csv)";
    const char* liveData = R"(C:\Users\asaf4\CLionProjects\AdvEx2\aLiveData.csv)";

    TimeSeries* data = new TimeSeries(name);
    TimeSeries* firstLiveData = new TimeSeries(liveData);
    TimeSeriesAnomalyDetector* detector = new SimpleAnomalyDetector();

    detector->learnNormal(*data);

    vector<AnomalyReport> reports = detector->detect(*firstLiveData);

    for (const auto& report: reports){
        cout << report << endl;
    }

    delete data;
    delete firstLiveData;
    delete detector;
    return 0;
}