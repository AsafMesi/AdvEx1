/**
 * Authors:
 *  name: Asaf Mesilaty.
 *  ID: 318646072.
 *
 *  name: Dan Marom.
 *  ID: 208995035.
 */

#include "timeseries.h"
#include <vector>
#include <string>
#include <sstream>
#include "unordered_map"

/**
 * @param dest a string vector.
 * @param text is the string that should be split.
 *
 * Adding strings to dest by iterating over text and splitting it by the delimiter ','.
 */
void TimeSeries:: splitByComma(vector <string> &dest, const string& text){
    std::stringstream ss(text);
    while (ss.good()) {
        string elem;
        getline(ss, elem, ',');
        dest.push_back(elem);
    }
}

/**
 * @param db is an unordered map that consist data for each feature.
 * @param row is a string consist of new data for each feature.
 *
 * We add a new value for every feature data vector in "db".
 * We get the values from "row".
 */
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
TimeSeries::TimeSeries() {
    this->numOfRows = 0;
}


/**
 * Constructor.
 * @param CSVfileName is the path of the csv input file.
 *
 * The input file contains data needed to create a TimeSeries object.
 * The 1st line contains the features names.
 * Rest of the lines are data matching those features.
 */
TimeSeries::TimeSeries(const char *CSVfileName){
    numOfRows = 0;
    ifstream file;
    file.open(CSVfileName);
    if (!file.is_open()){
        exit(-1);
    }
    string firstLine ;
    getline(file, firstLine);
    splitByComma(this->features, firstLine);
    for (const auto& feature : this->features) {
        this->dataBase[feature];
    }
    while (file.good()) {
        string row;
        getline(file, row);
        if (!row.empty()) {
        addRow(this->dataBase, row);
        this->numOfRows++;
        }
    }
    file.close();
}

/**
 * Getter.
 * @return a copy of the TimeSeries features vector.
 */
vector<string> TimeSeries::getFeatures() const {
    return this->features;
}

/**
 * Getter.
 * @return TimeSeries number of features.
 */
int TimeSeries::getNumberOfFeatures() const{
    return (int) this->features.size();
}

/**
 * Getter.
 * @return TimeSeries number of rows. (number of values for each feature)
 */
int TimeSeries::getNumberOfRows() const {
    return this->numOfRows;
}

/**
 * Getter.
 * @param feature is the feature we want to retrieve data from.
 * @return a copy of this feature values vector (data).
 */
vector<float> TimeSeries ::getFeatureData (const string& feature) const{
    return this->dataBase.find(feature)->second;
}

TimeSeries :: ~TimeSeries() = default;