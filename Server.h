//
// Created by DanMa on 09/01/2022.
//

#ifndef ANOMALY_DETECTION_UTIL_CPP_SERVER_H
#define ANOMALY_DETECTION_UTIL_CPP_SERVER_H
/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#include <thread>

#ifndef SERVER_H_
#define SERVER_H_


using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){

    }
};


// implement on Server.cpp
class Server {
    thread* t; // the thread to run the start() method in

    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */

#endif //ANOMALY_DETECTION_UTIL_CPP_SERVER_H
