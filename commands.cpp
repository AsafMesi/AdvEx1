//
// Created by DanMa on 30/12/2021.
//
# include "timeseries.h"
#include "commands.h"
#include "timeseries.h"
// implement here your command classes



void countAnomalyCommand :: generateAnomaliesVector(vector<compactAnomaly> &vec){
    string s = "";
    vector<string> pair;
    while ((s = this->dio->read()) != "done"){
        TimeSeries ::splitByComma(pair, s);
        vec.push_back(compactAnomaly(stoi(pair[0]),stoi(pair[1])));
    }
}

void countAnomalyCommand ::execute(CommandsDataBase *cdb) {
    vector<compactAnomaly> anomalies;
    generateAnomaliesVector(anomalies);

}


// if user chose 4
void printAnomalyCommand :: execute(CommandsDataBase* cdb) {
    vector<AnomalyReport> reports =  cdb->reports;
    for(auto & report : reports){
        this->dio->write(to_string(report.timeStep) + "\t" + report.description + "\n");
    }
    this->dio->write("Done.");
}

// for every cf - the anomalies are ordered in an increasing order.
void anomalyDetectionCommand :: generateCompactReports(CommandsDataBase* cdb){
    int size = cdb->reports.size();
    for(int i = 0; i < size; i++){
        // fucking loop man.
    }
}

// if user chose 3
void anomalyDetectionCommand :: execute(CommandsDataBase* cdb) {

    cdb->train.setThreshold(cdb->threshold);
    cdb->test.setThreshold(cdb->threshold);

    cdb->had.learnNormal(*(cdb->train));
    cdb->reports= cdb->had.detect(*(cdb->test));
    generateCompactReports(CommandsDataBase* cdb);
}

// if user chose 2
void updateThresholdCommand :: execute(CommandsDataBase* cdb) {
    bool validInput = false;
    float f;
    this->dio->write("The current correlation threshold is " + to_string(cdb->threshold) + "\n");
    while(!validInput){
        f = stof(this->dio->read());
        if(0<=f && f>=1){
            validInput = true;
        }
        else{
            this->dio->write("please choose a value between 0 and 1.\n");
        }
    }
    cdb->threshold = f;
}

// if user chose 1
void uploadCSVCommand :: execute(CommandsDataBase* cdb) {
    string trainPath, testPath;

    this->dio->write("Please upload your local train CSV file.\n");
    // create CSV train file.
    this->dio->readAndCreate("train.csv", "done\n");
    // create train time series.
    cdb->train = new TimeSeries("train.csv");
    this->dio->write("Upload Complete.\n");

    this->dio->write("Please upload your local test CSV file.\n");
    // create CSV test file.
    this->dio->readAndCreate("test.csv", "done\n");
    // create train time series.
    cdb->test = new TimeSeries("test.csv");
    this->dio->write("Upload Complete.\n");
}