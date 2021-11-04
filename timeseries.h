

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string>
#include <vector>
#include "fstream"
#include "string"

using namespace std;


class TimeSeries {

vector<string> *features;
vector<vector<double>> *table;

public:

    TimeSeries(const char *CSVfileName);

    vector<string> *getFeatures();

    int getNumberOfFeatures();

    void fillTable(ifstream &file);

    vector<string> *splitByComma(string &line);

    void printTable();

};

#endif /* TIMESERIES_H_ */
