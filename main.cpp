#include <iostream>
#include "string"
#include "timeseries.h"




int main(){
//    const char* name = R"(C:\Users\asaf4\CLionProjects\AdvEx2\test.csv)";
    const char* name = R"(C:\Users\asaf4\CLionProjects\AdvEx2\test.csv)";
    auto* data = new TimeSeries(name);
    for (int i = 0; i<data->getNumberOfFeatures(); i++){
        vector<float> v =  data->getFeatureData(data->getFeatures()[i]);
        float *ptr =v.data();
        for (int i=0; i<data->getNumberOfRows(); i++) {
            cout << to_string(*ptr) + ", ";
            ptr++;
        }
        cout << endl;
        cout << " _______________________"  << endl;
    }
    delete data;
    return 0;
}