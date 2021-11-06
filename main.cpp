#include <iostream>
#include "string"
#include "timeseries.h"




int main(){
//    const char* name = R"(C:\Users\asaf4\CLionProjects\AdvEx2\test.csv)";
    const char* name = R"(C:\Users\asaf4\CLionProjects\AdvEx2\test.csv)";
    auto* data = new TimeSeries(name);
    data->printTable();
    vector<float> v = data->getFeatureData(data->getFeatures()[0]);
    for (auto val : v){
        cout << to_string(val) + ", ";
    }
    cout << endl;
    delete data;
    return 0;
}