#include "timeseries.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "iterator"



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
    this->features =    TimeSeries :: splitByComma(firstLine);

    // gets table
    TimeSeries :: fillTable(file);
    fillMap();
    file.close();
}

vector<float>* stringVecToDoubleVec(vector <string>* strV) {
    auto doubleV = new vector<float>;
    for (auto &val: *strV) {
        doubleV->push_back(std::stof(val));
    }
    return doubleV;
}

// gets opended ifstream
void TimeSeries ::fillTable(ifstream& file){
    this->table = new vector<vector<float>*>;
    while(file.good()) {
        string line;
        getline(file, line);
        (this->table)->push_back((stringVecToDoubleVec(splitByComma(line))));
        this->numOfRows ++;
    }
}

void TimeSeries :: printTable(){
    for (const auto& val : *this->features){
        cout << val + ", ";
    }
    cout << endl;
    cout << "____________________";
    cout << endl;
   for (const auto& row : *this->table){
       for(auto val : *row) {
           cout << to_string(val) + ", ";
       }
       cout << endl;
   }
}


vector<string>* TimeSeries::getFeatures() {
    return this->features;
}


int TimeSeries::getNumberOfFeatures() {
    return (int) this->features->size();
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

/**
 * Destructor
 */
TimeSeries :: ~TimeSeries(){
    delete this->features;
    for (auto row : *this->table)
    {
        delete row;
    }
    delete this->table;

    for (auto & x : *this->dataBase)
    {
        delete x.second;
    }
    delete this->dataBase;
}

vector<float>* TimeSeries ::getFeatureData(const string& feature){
    return this->dataBase->find(feature)->second;


}

void TimeSeries :: fillMap() {
    this->dataBase = new map<string, vector<float> *>;
    for (int i = 0; i < this->getNumberOfFeatures(); i++) {
        auto *col = new vector<float>;
        for (int j = 0; j < numOfRows; j++) {
            float val = (*((*this->table)[j]))[i];
            col->push_back(val);
        }
        this->dataBase->insert({(*features)[i], col});
    }
}