

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
vector<vector<float>*> *table;
map<string, vector<float>*> *dataBase;
int numOfRows;

public:

    explicit TimeSeries(const char *CSVfileName);

    ~TimeSeries();

    vector<string> *getFeatures();

    int getNumberOfFeatures();

    void fillTable(ifstream &file);

    static vector<string> *splitByComma(string &line);

    void printTable();

    void fillMap();

    vector<float> *getFeatureData(const string& feature);

};

#endif /* TIMESERIES_H_ */
