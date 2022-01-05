//
// Created by DanMa on 30/12/2021.
//

#include "CLI.h"

void CLI::start(){
    string key;
    auto* cdb = new CommandsDataBase();
    commandFactory cf(this->dio);
    Command* c;
    do {
        key = dio->read();
        c = cf.getCommand(key);
        c->execute(cdb);
    } while (typeid(*c) != typeid(terminateCommand));
}


CLI::~CLI() = default;

