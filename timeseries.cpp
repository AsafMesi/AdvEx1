#include "timeseries.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "string.h"
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
    for (auto p : *this->table)
    {
        delete p;
    }
    delete this->table;
}

vector<double>* TimeSeries ::getFeatureData(string feature){
    int i = getFeatureIndex(feature);
    vector<double>* temp = new vector<double>;
    for(int j = 0; j < numOfRows; j++){
        double f = (table[0][0][i][j]);
        temp->push_back(f);
    }


}

/**
 * Maps feature to its index
 * @param feature is the feature to map
 * @return its index
 */
int TimeSeries :: getFeatureIndex(string feature) {
    int counter = 0;
    for(auto &f : *this->features){
        if (f == feature){
            break;
        }
        counter++;
    }
    return counter;
}
//void TimeSeries :: fillMap(){
//    this->dataBase = new map<string, vector<double>*>;
//    auto* db = new map<string, vector<double>*>;
//    for(int i = 0; i < this->getNumberOfFeatures(); i++){
//        auto* col = new vector<double>;
//        for(int j = 0; j < numOfRows; j++){
//            col[j] = *this->table[j][i];
//        }
//        string s;
//        std::copy(features[i].begin(), features[i].end(), s);
//        this->dataBase->insert({s, col});
//    }
