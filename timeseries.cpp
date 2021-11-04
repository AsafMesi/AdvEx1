#include "timeseries.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "string.h"
#include <string>
#include <sstream>



TimeSeries::TimeSeries(const char *CSVfileName){

    // gets name
    strcpy(this->fileName, CSVfileName);

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


// gets opended ifstream
void TimeSeries ::fillTable(ifstream& file){
    this->table = new vector<vector<double>>;
    int i = 0;
    while(file.good()) {
        string line;
        getline(file, line);
        vector<string>* row = splitByComma(line);
        for(int j = 0 ; j < row->size(); j++) {
            (*this->table)[i][j] = std :: stod ((*row)[j]);
        }
//        cout << line << endl;
    }
}

void TimeSeries :: printTable(){
    for (auto val : *this->features){
        cout << val + ", ";
    }
    cout << endl;
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
