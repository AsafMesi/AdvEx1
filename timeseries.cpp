#include "timeseries.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "unordered_map"

/**
 * Splits line by Comma
 * @param line to split
 * @return splited vector
 */
void splitByComma(vector <string> &dest, const string& text){
    std::stringstream ss(text);
    while (ss.good()) {
        string elem;
        getline(ss, elem, ',');
        dest.push_back(elem);
    }
}

void TimeSeries::addRow(unordered_map<string, vector<float>> &db, const string& row){
    std::stringstream ss(row);
    for (const string& key : this->features) {
        if (! ss.good()){
            break;
        }
        string val;
        getline(ss, val, ',');
        db[key].push_back(stof(val));
    }
}

TimeSeries::TimeSeries(const char *CSVfileName){

    numOfRows = 0;

    // open file
    ifstream file;
    file.open(CSVfileName);
    if (!file.is_open()){
        cout << "Error" << endl;
    }

    // gets 1st line
    string firstLine ;
    getline(file, firstLine);
    splitByComma(this->features, firstLine);

    // create keys (every key is a feature)
    for (const auto& feature : this->features) {
        this->dataBase[feature];
    }

    while (file.good()) {
        string row ;
        getline(file, row);
        addRow(this->dataBase, row);
        this->numOfRows++;
    }
    file.close();
}

// returns a copy.
vector<string> TimeSeries::getFeatures() const {
    return this->features;
}

int TimeSeries::getNumberOfFeatures() const{
    return (int) this->features.size();
}

int TimeSeries::getNumberOfRows() const {
    return this->numOfRows;
}

// returns a copy.
vector<float> TimeSeries ::getFeatureData (const string& feature) const{
    return this->dataBase.find(feature)->second;
}

/**
 * Destructor
 */
TimeSeries :: ~TimeSeries() = default;