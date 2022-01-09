//
// Created by DanMa on 09/01/2022.
//

#include "Server.h"


#include "Server.h"

Server::Server(int port)throw (const char*) {

}

void Server::start(ClientHandler& ch)throw(const char*){
}

void Server::stop(){
    t->join(); // do not delete this!
}

Server::~Server() {
}