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

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    // you may add additional methods here
};

// you may add here helper classes
class CommandsDataBase {
    TimeSeries *train{};
    TimeSeries *test{};
    float threshold;
    vector<AnomalyReport> reports;
public:
    CommandsDataBase(){
        this->train = nullptr;
        this->test = nullptr;
        this->threshold = 0.9;
    }

    void setTrain(string path);
    TimeSeries* getTrain(){
        return this->train;
    }

    void setTest(string path);

    TimeSeries* getTest(){
        return this->test;
    }

    vector<AnomalyReport> getReports(){
        return this->reports;
    }

    void setThreshold(float f);
};






// you may edit this class
class Command{
public:
    Command(DefaultIO* dio, CommandsDataBase* cdb):dio(dio),cdb(cdb){}
    virtual void execute()=0;
    virtual ~Command(){}

protected:
    DefaultIO* dio;
    CommandsDataBase* cdb;
};

class uploadCommand : public Command{
    void execute() override;
public:
    uploadCommand(DefaultIO* dio, CommandsDataBase* cdb) : Command(dio, cdb){};
    void generateCSV(const char *s, const char *delim, const char *name);
};

class updateThresholdCommand : public Command{
    void execute() override;
public:
    updateThresholdCommand(DefaultIO* dio, CommandsDataBase* cdb) : Command(dio, cdb){};
};

class anomalyDetectionCommand : public Command{
    void execute() override;
public:
    anomalyDetectionCommand(DefaultIO* dio, CommandsDataBase* cdb) : Command(dio, cdb){};
};

class printAnomalyCommand : public Command{
    void execute() override;
public:
    printAnomalyCommand(DefaultIO* dio, CommandsDataBase* cdb) : Command(dio, cdb){};
};

#endif /* COMMANDS_H_ */
#endif //ANOMALY_DETECTION_UTIL_CPP_COMMANDS_H
