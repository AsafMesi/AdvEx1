/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

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
unordered_map<string, vector<float>> dataBase;
int numOfRows;

public:
    explicit TimeSeries(const char *CSVfileName);
    int getNumberOfRows() const;
    int getNumberOfFeatures() const;
    void addRow(unordered_map<string, vector<float>> &db, const string& row);
    vector<float> getFeatureData (const string& feature) const;
    vector<string> getFeatures() const;
    ~TimeSeries();
};

#endif /* TIMESERIES_H_ */
