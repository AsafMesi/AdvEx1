#include "timeseries.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "string.h"
#include <string>
#include <sstream>



TimeSeries::TimeSeries(const char *CSVfileName){

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
    file.close();
}

vector<double>* stringVecToDoubleVec(vector <string>* strV) {
    auto doubleV = new vector<double>;
    for (auto &val: *strV) {
        doubleV->push_back(std::stod(val));
    }
    return doubleV;
}

// gets opended ifstream
void TimeSeries ::fillTable(ifstream& file){
    this->table = new vector<vector<double>*>;
    while(file.good()) {
        string line;
        getline(file, line);
        (this->table)->push_back((stringVecToDoubleVec(splitByComma(line))));
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
