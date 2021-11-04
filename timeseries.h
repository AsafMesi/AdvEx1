

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string>
#include <vector>

using namespace std;

class TimeSeries{
vector <string> features;
char* fileName;

public:

    TimeSeries(const char *CSVfileName);

    init();

    vector<string> getFeatures();

    int getNumberOfFeatures();

};



#endif /* TIMESERIES_H_ */
