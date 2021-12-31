//
// Created by DanMa on 30/12/2021.
//
# include "timeseries.h"
#include "commands.h"
#include "timeseries.h"
// implement here your command classes


// if user chose 2

void updateThresholdCommand ::execute() {
    float f;
    cout << "The current correlation threshold is 0.9\n";
    f = stof(this->dio->read());
    if (f < 0 || f > 1){
        do{
            cout << "please choose a value between 0 and 1.\n";
            f = stof(this->dio->read());
        } while (f < 0 || f > 1);
    }
    this->cdb->setThreshold(f);
}


// if user chose 1
void uploadCommand :: execute() {
    string trainPath, testPath;

    cout << "Please upload your local train CSV file.\n";
    // get train path.
    trainPath = dio->read();

    // create CSV train file.
    generateCSV(trainPath.c_str(), "done", "trainData.csv");

    // create train time series.
    this->cdb->setTrain(trainPath);
    cout << "Upload Complete.\n";


    cout << "Please upload your local test CSV file.\n";
    // get train path.
    testPath = dio->read();

    // create CSV test file.
    generateCSV(trainPath.c_str(), "done", "testData.csv");

    // create test time series.
    this->cdb->setTest(dio->read());
    cout << "Upload Complete.\n";

}

void uploadCommand ::generateCSV(const char *s, const char *delim, const char *name) {
    vector<string> dest;
    ifstream file;
    file.open(s);
    if (!file.is_open()) {
        exit(-1);
    }
    ofstream out(name);
    string row;
    while (row != delim) {
        getline(file, row);
        TimeSeries::splitByComma(dest, row);
        for (auto &i: dest) {
            out << i << ",";
        }
        out << endl;
    }
    file.close();
}

void CommandsDataBase::setTrain(string path) {
    this->train = new TimeSeries(path.c_str());
}

void CommandsDataBase ::setThreshold(float f) {
    this->threshold = f;
}