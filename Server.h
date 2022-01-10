#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include<signal.h>
#include "commands.h"
#include "CLI.h"
#include <sstream>

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    // Could get message from client and send response, as well as communicate with the client until the end of
    // the conversion/data transfer. In our case, we don't have to implement it.
    virtual void handle(int clientID)=0;
};

class socketIO:public DefaultIO{
    int clientID;
public:
    socketIO(int clientID):clientID(clientID){}
    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);

};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        socketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    int fd; // file descriptor
    sockaddr_in server; // server's socket
    sockaddr_in client; // client's socket
	thread* t; // the thread to run the start() method in
    bool isStopped = false; // When we call stop - True. As long as it's true, we can accept new clients.

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
