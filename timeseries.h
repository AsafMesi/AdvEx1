

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string>
#include <vector>
#include "fstream"
#include "string"
#include "map"
using namespace std;


class TimeSeries {

vector<string> *features;
vector<vector<double>*> *table;
map<string, vector<double>*> *dataBase;
int numOfRows;

public:

    TimeSeries(const char *CSVfileName);

    ~TimeSeries();

    vector<string> *getFeatures();

    int getNumberOfFeatures();

    void fillTable(ifstream &file);

    vector<string> *splitByComma(string &line);

    void printTable();

    void fillMap();

    vector<double> *getFeatureData(const string& feature);

};

#endif /* TIMESERIES_H_ */
