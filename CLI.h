//
// Created by DanMa on 30/12/2021.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_CLI_H
#define ANOMALY_DETECTION_UTIL_CPP_CLI_H




#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    // you can add data members
public:
    CLI(DefaultIO* dio): dio(dio){};
    void start();
    virtual ~CLI();
};

#endif /* CLI_H_ */
#endif //ANOMALY_DETECTION_UTIL_CPP_CLI_H
