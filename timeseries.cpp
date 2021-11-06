#include "timeseries.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
    this->features = *splitByComma(firstLine);

    // gets table
    this->fillTable(file);
    this->fillMap();
    file.close();
}

vector<float>* stringVecToFloatVec(const vector<string>& strV) {
    auto* floV = new vector<float>;
    for (auto &val: strV) {
        floV->push_back(std::stof(val));
    }
    return floV;
}

/**
 * Splits line by Comma
 * @param line to split
 * @return splited vector
 */
vector<string>* TimeSeries :: splitByComma(string& line) {
    std::stringstream ss(line);
    auto* values = new vector<string>;
    while (ss.good()) {
        string feature;
        getline(ss, feature, ',');
        values->push_back(feature);
    }
    return values;
}

// gets opended ifstream
void TimeSeries ::fillTable(ifstream& file){
    while(file.good()) {
        string line;
        getline(file, line);
        vector<string>* strVec = splitByComma(line);
        this->table.push_back(stringVecToFloatVec(*strVec));
        delete strVec;
        this->numOfRows ++;
    }
}

void TimeSeries :: printTable(){
    for (const auto& val : this->features){
        cout << val + ", ";
    }
    cout << endl;
    cout << "____________________";
    cout << endl;
   for (const auto& row : this->table){
       for(auto val : *row) {
           cout << to_string(val) + ", ";
       }
       cout << endl;
   }
}


vector<string> TimeSeries::getFeatures() const {
    vector<string> copy;
    for(const auto& feature : this->features){
        copy.push_back(feature);
    }
    return copy;
}


int TimeSeries::getNumberOfFeatures() const{
    return (int) this->features.size();
}

int TimeSeries::getNumberOfRows() const {
    return this->numOfRows;
}

vector<float> TimeSeries ::getFeatureData (const string& feature) const{
    vector<float>* source = this->dataBase.find(feature)->second;
    vector<float> copy;
    for(auto val : *source){
        copy.push_back(val);
    }
    return copy;
}

void TimeSeries :: fillMap() {
    for (int i = 0; i < this->getNumberOfFeatures(); i++) {
        auto *col = new vector<float>;
        for (int j = 0; j < numOfRows; j++) {
            float val = (*(this->table[j]))[i];
            col->push_back(val);
        }
        this->dataBase.insert({features[i], col});
    }
}

/**
 * Destructor
 */
TimeSeries :: ~TimeSeries(){
    this->features.clear();
    for (auto row : this->table)
    {
        delete row;
    }
    this->table.clear();

    for (auto & x : this->dataBase)
    {
        delete x.second;
    }
}