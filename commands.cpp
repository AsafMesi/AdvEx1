//
// Created by DanMa on 30/12/2021.
//
# include "timeseries.h"
#include "commands.h"
#include "timeseries.h"
// implement here your command classes

Command* commandFactory ::getCommand(string& key) {
    Command* c = nullptr;
    if(this->cm.find(key) != this->cm.end()){
        return this->cm[key];
    } else{
        switch(stoi(key)){
            case 1:
                c = new uploadCSVCommand(this->dio);
                break;
            case 2:
                c = new updateThresholdCommand(this->dio);
                break;
            case 3:
                c = new anomalyDetectionCommand(this->dio);
                break;
            case 4:
                c = new printAnomalyCommand(this->dio);
                break;
            case 5:
                c = new countAnomalyCommand(this->dio);
                break;
            case 6:
                c = new terminateCommand(this->dio);
                break;
            default:
                dio->write("Invalid Option\n");
                break;
        }
        cm[key] = c;
        return c;
    }
}

void terminateCommand ::execute(CommandsDataBase *cdb) {
    this->dio->close();
}

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

/**
 * @param ca is the expectedAnomalies vector
 * @param anomaly is the detected anomaly.
 * @return true if exist at least one expectedAnomaly s.t it is intersecting with the detected anomaly.
 *
 * Given a anomaly detected by a TimeSeries Anomaly Detector and a given expectedAnomalies vector,
 * checks if there exist at least one expectedAnomaly that intersect the detected one.
 * If does - update both TP fields of detectedAnomaly and ExpectedAnomaly which intersect to be true, and return true.
 * Else - return false.
 */
static void checkAnomaliesIntersection(vector<compactAnomaly> ca, compactAnomaly anomaly) {
    for (auto &elem: ca) {
        if (anomaly.end >= elem.start && elem.end >= anomaly.start) {
            elem.TP = true;
            anomaly.TP = true;
        }
    }
}


void countAnomalyCommand ::execute(CommandsDataBase *cdb) {
    unsigned long long TPRate, FPRate,numOfNonExc, numOfExc = 0;

    // initialize both expected and detected vectors.
    vector<compactAnomaly> expectedAnomalies;
    generateAnomaliesVector(expectedAnomalies);

    for(auto &anomaly : cdb->compactReports){
        checkAnomaliesIntersection(expectedAnomalies, anomaly);

        // calculate number of exceptions. +1 because we want to count anomaly that occurs separately.
        numOfExc += (anomaly.end - anomaly.start + 1); //leshanot
    }

    /*
     * Let P be number of expected anomalies (expectedAnomalies.size()).
     * TP = expected anomaly which had a detected anomaly intersected with.
     * TPRate = TP/P
     */
    TPRate = std::count_if(expectedAnomalies.begin(), expectedAnomalies.end(),
                        [expectedAnomalies](compactAnomaly& e){return e.TP;}) / expectedAnomalies.size();

    //numOfNonExc = number of lines (timesteps) in the csv file that did not have an anomaly in.
    numOfNonExc = cdb->test->getNumberOfRows() - numOfExc; //verify ==N

    /*
     * Let N be numOfNonExc
     * FP = detected report which was not expected -> counted with count_if
     * FPRate = FP/N.
     */
    FPRate = std::count_if(cdb->compactReports.begin(), cdb->compactReports.end(),
                           [expectedAnomalies](compactAnomaly& e){return !e.TP;}) / numOfNonExc;

    this->dio->write("True Positive Rate: " + to_string(TPRate));
    this->dio->write("False Positive Rate: " + to_string(FPRate));
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
void anomalyDetectionCommand :: generateCompactReports(CommandsDataBase* cdb, vector<compactAnomaly>& ca) {
    int i = 0, j = 0;

    // minus one because we access i+1 in the loop.
    int size = cdb->reports.size() - 1;

    // initialization
    vector<AnomalyReport> rep = cdb->reports;
    ca[0] = compactAnomaly(cdb->reports[0].timeStep, cdb->reports[0].timeStep);
    ca[0].des = cdb->reports[0].description;

    for (i; i < size; i++) {
        if ((rep[i].description == rep[i + 1].description) &&
            ((rep[i].timeStep + 1) == (rep[i + 1].timeStep))) {

            // increase compact Report end.
            ca[j].end += 1;
        } else {
            j++;

            // creates new compact anomaly.
            ca[j] = compactAnomaly(cdb->reports[i+1].timeStep, cdb->reports[i+1].timeStep);
            ca[j].des = cdb->reports[i+1].description;
        }
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
    this->dio->readAndCreate(R"(C:\Users\DanMa\CLionProjects\APProject\train.csv)", "done");
    // create train time series.
    cdb->train = new TimeSeries(R"(C:\Users\DanMa\CLionProjects\APProject\train.csv)");
    this->dio->write("Upload Complete.\n");

    this->dio->write("Please upload your local test CSV file.\n");
    // create CSV test file.
    this->dio->readAndCreate("test.csv", "done");
    // create train time series.
    cdb->test = new TimeSeries("test.csv");
    this->dio->write("Upload Complete.\n");
}