//
// Created by DanMa on 30/12/2021.
//

#include "CLI.h"
#include "MainTrain_Ex5.cpp"


CLI::CLI(DefaultIO* dio) {
}

void CLI::start(){
    auto* cdb = new CommandsDataBase();
    DefaultIO* dio = new STDtest("input.txt", "output.txt");
    Command *cmd1 = new uploadCommand(dio, cdb);
    cmd1->execute();
    Command *update = new updateThresholdCommand(dio,cdb)

}


CLI::~CLI() {
}

