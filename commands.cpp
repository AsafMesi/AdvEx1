//
// Created by DanMa on 30/12/2021.
//
# include "timeseries.h"
#include "commands.h"
#include "timeseries.h"
// implement here your command classes


/**
 * @param vec is the vector we inject compact anomalies to.
 *
 * This function inject compat anomalies received to a given compactAnomaly vector.
 */
void countAnomalyCommand :: generateAnomaliesVector(vector<compactAnomaly> &vec){
    string s = "";
    vector<string> pair;
    while ((s = this->dio->read()) != "done"){
        TimeSeries ::splitByComma(pair, s);
        vec.push_back(compactAnomaly(stoi(pair[0]),stoi(pair[1])));
    }
}

bool countAnomalyCommand :: checkAnomaliesIntersection(vector<compactAnomaly> ca, compactAnomaly anomaly){

    bool flag = false;
    for(auto &elem : ca){

        /*
         * takes care of elem fully contained anomaly, and elem intersect with nomaly
         */
        if(elem.start <= anomaly.start && elem.end >= anomaly.start){
            elem.TP = true;
            anomaly.TP = true;
            return flag;
        }
        if(anomaly.start <= elem.start && anomaly.end >= elem.start){
            elem.TP = true;
            anomaly.TP = true;
            flag = true;
            return flag;
        }
        return flag;
    }
}

void countAnomalyCommand ::execute(CommandsDataBase *cdb) {

    // initialize both expected and detected vectors.
    vector<compactAnomaly> expectedAnomalies;
    vector<compactAnomaly> detectedAnomalies;
    generateAnomaliesVector(expectedAnomalies);

    for(auto &anomaly : detectedAnomalies){
        checkAnomaliesIntersection(expectedAnomalies, anomaly);
    }
    // to fucking do - check tp number
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
void anomalyDetectionCommand :: generateCompactReports(CommandsDataBase* cdb, vector<compactAnomaly>& ca){
    int i = 1, j = 1;

    // minus one because we access i+1 in the loop.
    int size = cdb->reports.size() - 1;

    vector<AnomalyReport> rep = cdb->reports;
    ca[0] = compactAnomaly(cdb->reports[0].timeStep,cdb->reports[0].timeStep);
    ca[0].des = cdb->reports[0].description;

    for (i; i < size; i++){
       if((rep[i].description == rep[i+1].description) &&
               ((rep[i].timeStep + 1) == (rep[i+1].timeStep))){

           // increase compact Report end.
           ca[j].end += 1;
       }
       else{
           j++;

           // creates new compact anomaly.
           ca[j] = compactAnomaly(cdb->reports[i].timeStep,cdb->reports[i].timeStep);
           ca[j].des = cdb->reports[i].description;
    }
}

// if user chose 3
void anomalyDetectionCommand :: execute(CommandsDataBase* cdb) {

    // update new threshold.
    cdb->had.setThreshold(cdb->threshold);

    cdb->had.learnNormal(*(cdb->train));
    cdb->reports= cdb->had.detect(*(cdb->test));

    generateCompactReports(cdb, cdb->compactReports);
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