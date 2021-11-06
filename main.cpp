#include <iostream>
#include <fstream>
#include "string"
#include "timeseries.h"




int main(){
//    const char* name = R"(C:\Users\asaf4\CLionProjects\AdvEx2\test.csv)";
    const char* name = R"(C:\Users\DanMa\CLionProjects\APProject\test.csv)";
    auto* data = new TimeSeries(name);
    data->printTable();
    delete data;
    return 0;
}