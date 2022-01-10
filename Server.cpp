

#include "Server.h"

// implement socketIO methods:

// We want to read a line, so we read char by char until will read "\n"
string socketIO::read(){
    char c = ' ';
    string line = "";
    while(c != '\n'){
        recv(clientID,&c,sizeof(char),0);
        line+=c;
    }
    line.pop_back();
    return line;
}

void socketIO::write(string text){
    // c_str() convert string type to const char *.
    send(clientID,text.c_str(),strlen(text.c_str()),0);
}

void socketIO::write(float f){
    ostringstream ss;
    ss << f;
    string s(ss.str());
    write(s);
}

void socketIO::read(float* f){
    char c = ' ';
    string line = "";
    while(c != '\n'){
        recv(clientID,&c,sizeof(char),0);
        line+=c;
    }
    line.pop_back();
    *f = stof(line);
}


Server::Server(int port) throw (const char*) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
        cerr << "Server's socket creation failed" << endl;

    // Set communication addresses type to Internet Protocol v4 addresses. (IPV4).
    server.sin_family = AF_INET;
    // When we don't know the IP address of our machine, we can use the special IP address "INADDR_ANY".
    server.sin_addr.s_addr = INADDR_ANY;
    // Translates the int "port" from host byte order, to network byte order; and set socket's port.
    server.sin_port = htons(port);

    // Try to assign the local socket address to the socket file descriptor.
    if(bind(fd,(struct sockaddr*)&server,sizeof(server)) < 0)
        cerr << "Server's socket bind failed" << endl;

    // Prepare the server for incoming client requests.
    // backlog (second arg) defines the maximum length for the queue of pending connections.
    if(listen(fd, 6) < 0)
        cerr << "Server's socket listen failed" << endl;

    this->isStopped = false;
    // The server is ready!
}

void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch, this](){
        while (!this->isStopped) {
            alarm(1);
            //Waiting for a client..., try accept client
            socklen_t clientSize = sizeof(client);
            int aClient = accept(fd, (struct sockaddr *) &client, &clientSize);
            alarm(0);
            // need to set alarm!!
            // if it was successful:
            if (aClient > 0) {
                // manage communication
                ch.handle(aClient);

                // when done - handle will terminate, and we close the connection, getting ready for another client,
                // as long as stop hasn't been called yet.
                close(aClient); // close client's socket.
            }
            alarm(0);
        }
        close(fd); // close server side server-client socket.
    });
}

void Server::stop(){
    isStopped = true;
	t->join(); // do not delete this!
}

Server::~Server() {
}

