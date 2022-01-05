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

    // you may add additional methods here
    virtual void close() = 0;
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

protected:
    DefaultIO* dio;
};

class uploadCSVCommand : public Command{
    void execute(CommandsDataBase* cdb) override;
public:
    explicit uploadCSVCommand(DefaultIO* dio) : Command(dio){};
};

class updateThresholdCommand : public Command{
    void execute(CommandsDataBase* cdb) override;
public:
    explicit updateThresholdCommand(DefaultIO* dio) : Command(dio){};
};

class anomalyDetectionCommand : public Command{
    void execute(CommandsDataBase* cdb) override;
public:
    explicit anomalyDetectionCommand(DefaultIO* dio) : Command(dio){};
};

class printAnomalyCommand : public Command{
    void execute(CommandsDataBase* cdb) override;
public:
    explicit printAnomalyCommand(DefaultIO* dio) : Command(dio){};
};

class countAnomalyCommand : public Command{
    void execute(CommandsDataBase* cdb) override;
public:
    explicit countAnomalyCommand(DefaultIO *dio) : Command(dio){};
    void generateAnomaliesVector(vector<compactAnomaly> &vec);

};

class terminateCommand : public Command{
    void execute(CommandsDataBase* cdb) override {
        this->dio->close();
    }
public:
    explicit terminateCommand(DefaultIO* dio) : Command(dio){};
};

class commandFactory {
    map<string, Command*> cm;
    DefaultIO* dio;
public:
    explicit commandFactory(DefaultIO* dio) : dio(dio){};
    Command* getCommand(string& key);
};
#endif /* COMMANDS_H_ */
#endif //ANOMALY_DETECTION_UTIL_CPP_COMMANDS_H
