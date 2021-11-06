

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string>
#include <vector>
#include "fstream"
#include "string"
#include "unordered_map"
using namespace std;


class TimeSeries {

vector<string> features;
vector<vector<float>*>table;
unordered_map<string, vector<float>*> dataBase;
int numOfRows;

public:

    explicit TimeSeries(const char *CSVfileName);

    ~TimeSeries();

    int getNumberOfRows() const;

    int getNumberOfFeatures() const;

    void fillTable(ifstream &file);

    static vector<std::string> * splitByComma(string &line);

    void printTable();

    void fillMap();

    vector<float> getFeatureData (const string& feature) const;

    vector<string> getFeatures() const;
};

#endif /* TIMESERIES_H_ */
