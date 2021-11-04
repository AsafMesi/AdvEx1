#include <iostream>
#include <fstream>
#include "string"
#include "timeseries.h"



int main(){

    const char* name = R"(C:\Users\DanMa\CLionProjects\APProject\test.csv)";
    auto* data = new TimeSeries(name);
    data->printTable();
    return 0;
}