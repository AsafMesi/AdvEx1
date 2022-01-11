//
// Created by DanMa on 30/12/2021.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_COMMANDS_H
#define ANOMALY_DETECTION_UTIL_CPP_COMMANDS_H



#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
#include "timeseries.h"
#include "map"

using namespace std;

struct compactAnomaly{
    int start;
    int end;
    bool TP = false;
    string des;

    compactAnomaly(int s, int e){
        this->start = s;
        this->end = e;
        this->TP = false;
        this->des = "";
    }
};

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO()= default;

    void readAndCreate(const string& fileName, const char* delim){
        ofstream out(fileName);
        string row;
        while ((row = read())!= delim){
            out << row << endl;
        }
        out.close();
    }
};

// you may add here helper classes
struct CommandsDataBase {
    TimeSeries *train{};
    TimeSeries *test{};
    HybridAnomalyDetector had;
    float threshold = 0.9;
    vector<AnomalyReport> reports;
    vector<compactAnomaly> compactReports{};
};

// you may edit this class
class Command{
public:
    explicit Command(DefaultIO* dio):dio(dio){}
    virtual void execute(CommandsDataBase* cdb)=0;
    virtual ~Command()= default;
    static void reGenerateCompactReports(CommandsDataBase* cdb) {
        cdb->compactReports.clear();

        // minus one because we access i+1 in the loop.
        int size = cdb->reports.size() - 1;

        // initialization
        vector<AnomalyReport> rep = cdb->reports;
        cdb->compactReports.emplace_back(compactAnomaly(cdb->reports[0].timeStep, cdb->reports[0].timeStep));
        cdb->compactReports[0].des = cdb->reports[0].description;

        int j = 0;
        for (int i=0; i < size; i++) {
            if ((rep[i].description == rep[i + 1].description) &&
                ((rep[i].timeStep + 1) == (rep[i + 1].timeStep))) {

                // increase compact Report end.
                cdb->compactReports[j].end += 1;
            } else {
                j++;

                // creates new compact anomaly.
                cdb->compactReports.emplace_back(compactAnomaly(cdb->reports[i+1].timeStep, cdb->reports[i+1].timeStep));
                cdb->compactReports[j].des = cdb->reports[i+1].description;
            }
        }
    }

protected:
    DefaultIO* dio;
};

class uploadCSVCommand : public Command{
    void execute(CommandsDataBase* cdb) override {
        string trainPath, testPath;

        this->dio->write("Please upload your local train CSV file.\n");
        // create CSV train file.
        this->dio->readAndCreate(R"(train.csv)", "done");
        // create train time series.
        cdb->train = new TimeSeries(R"(train.csv)");
        this->dio->write("Upload complete.\n");

        this->dio->write("Please upload your local test CSV file.\n");
        // create CSV test file.
        this->dio->readAndCreate("test.csv", "done");
        // create train time series.
        cdb->test = new TimeSeries("test.csv");
        this->dio->write("Upload complete.\n");
    }
public:
    explicit uploadCSVCommand(DefaultIO* dio) : Command(dio){};
};

class updateThresholdCommand : public Command{
    void execute(CommandsDataBase* cdb) override {
        bool validInput = false;
        float f;
        while(!validInput){
            this->dio->write("The current correlation threshold is ");
            this->dio->write(cdb->threshold);
            this->dio->write("\nType a new threshold\n");
            f = stof(this->dio->read());
            if(0 < f && f <= 1){
                validInput = true;
                cdb->threshold = f;
            }
            else{
                this->dio->write("please choose a value between 0 and 1.\n");
            }
        }
    }
public:

    explicit updateThresholdCommand(DefaultIO* dio) : Command(dio){};
};

class anomalyDetectionCommand : public Command{
    void execute(CommandsDataBase* cdb) override {

        // update new threshold.
        cdb->had.setThreshold(cdb->threshold);
        cdb->had.learnNormal(*(cdb->train));
        cdb->reports = cdb->had.detect(*(cdb->test));
        reGenerateCompactReports(cdb);
        this->dio->write("anomaly detection complete.\n");
    }
public:
    explicit anomalyDetectionCommand(DefaultIO* dio) : Command(dio){};
};

class printAnomalyCommand : public Command{
    void execute(CommandsDataBase* cdb) override {
        vector<AnomalyReport> reports =  cdb->reports;
        for(auto & report : reports){
            this->dio->write(to_string(report.timeStep) + "\t" + report.description + "\n");
        }
        this->dio->write("Done.\n");
    }
public:
    explicit printAnomalyCommand(DefaultIO* dio) : Command(dio){};
};

class countAnomalyCommand : public Command{
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
    static void checkAndUpdateAnomaliesIntersection(vector<compactAnomaly>& ca, compactAnomaly& anomaly) {
        for (auto &elem: ca) {
            if (anomaly.end >= elem.start && elem.end >= anomaly.start) {
                elem.TP = true;
                anomaly.TP = true;
            }
        }
    }

/**
 * @param vec is the vector we inject compact anomalies to.
 *
 * This function inject compat anomalies received to a given compactAnomaly vector.
 */
    void generateAnomaliesVector(vector<compactAnomaly> &vec){
        string s;
        vector<string> pair;
        while ((s = this->dio->read()) != "done"){
            TimeSeries ::splitByComma(pair, s);
            vec.emplace_back(stoi(pair[0]),stoi(pair[1])); // create compactAnomaly obj and push it.
            pair.clear();
        }
    }

// if user choose 5
    void execute(CommandsDataBase *cdb) override {
        int numOfExc = 0;
        float TP, FP, P, N, TPRate, FPRate;

        // initialize both expected and detected vectors.
        this->dio->write("Please upload your local anomalies file.\n");
        vector<compactAnomaly> expectedAnomalies;
        generateAnomaliesVector(expectedAnomalies);
        this->dio->write("Upload complete.\n");

        for(auto &compactReport: cdb->compactReports){
            compactReport.TP = false;
        }

        for(auto &anomaly: expectedAnomalies){
            numOfExc += (anomaly.end - anomaly.start + 1);
        }

        for(auto &report : cdb->compactReports) {
            checkAndUpdateAnomaliesIntersection(expectedAnomalies, report);
        }

        //numOfNonExc = number of lines (time steps) in the csv file that did not have an anomaly in.
        N = cdb->test->getNumberOfRows() - numOfExc;

        /*
         * P is the number of expected anomalies pairs (expectedAnomalies.size()).
         * TP is the number of expected anomalies that intersect with one of the detected anomalies.
         * TPRate = TP/P
         */
        TP = std::count_if(expectedAnomalies.begin(), expectedAnomalies.end(),
                           [expectedAnomalies](compactAnomaly& e){return e.TP;});
        P = expectedAnomalies.size();

        /*
         * N = numOfNonExc = number of rows in test - number of expected anomalies time steps.
         * FP = number of detected reports which hasn't intersected with expected anomalies.
         * FPRate = FP/N.
         */
        FP = std::count_if(cdb->compactReports.begin(), cdb->compactReports.end(),
                           [expectedAnomalies](compactAnomaly& e){return !e.TP;});

        // set to 3 precision
        TPRate = floorf(TP/P * 1000) / 1000;
        FPRate = floorf((FP)/N * 1000) / 1000;
        // we write this way in order to ignore unnecessary zeroes at the end of the number.
        this->dio->write("True Positive Rate: ");
        this->dio->write(TPRate);
        this->dio->write("\n");
        this->dio->write("False Positive Rate: ");
        this->dio->write(FPRate);
        this->dio->write("\n");

        // initialize TP back to 0 good goalkeeper.
        for(auto &ca : cdb->compactReports){
            ca.TP = false;
        }
    }
public:
    explicit countAnomalyCommand(DefaultIO *dio) : Command(dio){};

};

class commandFactory {
    map<string, Command*> cm;
    DefaultIO* dio;
public:
    explicit commandFactory(DefaultIO* dio) : dio(dio){};
    Command* getCommand(string& key) {
        Command* c = nullptr;
        if(this->cm.find(key) != this->cm.end()){  // find will return map.end() if key has not been found.
            return this->cm[key];

            // if the requested command hasn't been used yet - create and add it to the command factory.
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
                default:
                    dio->write("Invalid Option\n");
                    break;
            }
            cm[key] = c;
            return c;
        }
    }

};



#endif /* COMMANDS_H_ */
#endif //ANOMALY_DETECTION_UTIL_CPP_COMMANDS_H
