#include "timeseries.h"
#include <iostream>
#include <vector>
#include <fstream>

    TimeSeries:TimeSeries(char *CSVfileName){

};
    init(){
        ifstream file;
        file.open(CSVfileName);
        if (!file.is_open()){
            cout << "Error" << endl;
        }
        this.fillFeatures();
        this.fillTable();
    }

    fillFeatures() {
        ifstream file;
        file.open(CSVfileName);
        if (file.good()) {
            string line;
            getline(file, line);
        }
        file.close();
        std::stringstream ss(line);
        for (int i; ss >> i;) {
            features.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }
    }

    fillTable(){
        ifstream file;
        file.open(CSVfileName);
        while(file.good()) {
            string line;
            getline(test, line, ',');
            cout << line << endl;
        }
    }

    vector getFeatures() {
        return features;
    }

    int getNumberOfFeatures() {
        return features.size();
    }
