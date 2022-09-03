#include "Server.h"
#include <iostream>
#include <unistd.h>
#include "stdio.h"
#include "cstring"

//Construct a server according to the address and the port
Server::Server(in_addr_t ip, in_port_t port) : id(socket(AF_INET, SOCK_STREAM, 0)), fIn() {
//    if (id >= 0) {
//        struct sockaddr_in in;
//        memset(&in, 0, sizeof(in));
//        in.sin_addr.s_addr = ip;
//        in.sin_family = AF_INET;
//        in.sin_port = port;
//        if (bind(id, (struct sockaddr *) &in, sizeof(in)) < 0) {
//            perror("Error in binding the i!");
//        }
//
//        if (listen(id, this->qLength) < 0) {
//            perror("Error in listening to the socket.");
//        }
//        memset(&t, 0, sizeof(t));
//        t.tv_sec = 145;
//
//        FD_ZERO(&readfds);
//        FD_SET(id, &readfds);
//    } else {
//        perror("Error in creating the i!");
//    }
    //dd
    //Initialize the socket and check it
    if (id < 0) {
        perror("error creating socket");
    }
    //Initialize the data structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;
    //Bind the socket to the port and ip
    if (bind(id, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    if (listen(id, this->qLength) < 0) {
        perror("error listening to a socket");
    }

    memset(&t, 0, sizeof(t));
    // Timeout in seconds
    t.tv_sec = 180;

    FD_ZERO(&readfds);
    FD_SET(id, &readfds);
}

//receives string from the i
//std::string Server::stringReceiver() {
//    if (this->cSocket == 0) {
//        if (listen(id, this->qLength) >= 0) {
//            unsigned int addrLen = sizeof(this->fIn);
//            this->cSocket = ::accept(id, (struct sockaddr *) &fIn, &addrLen);
//            if (this->cSocket < 0) {
//                perror("Error in accepting the client!");
//            }
//        } else {
//            perror("Error in listening to the i!");
//        }
//    }
//    char buff[Socket::buffer_size];
//    int dataLen = Socket::buffer_size;
//    int bytes = recv(this->cSocket, buff, dataLen, 0);
//    if (bytes < 0) {
//        perror("Error in writing to the i!");
//    }
//    std::string string(buff);
//    return string;
//}

//Sends string to the i
void Server::stringSender(std::string string) {
    int sent_bytes = send(this->cSocket, string.c_str(), strlen(string.c_str()), 0);
    if (sent_bytes < 0) {
        perror("Error in sending to the client!");
    }
}
int Server::getNum() const {
    return this->cSocket;
}

int Server::accept() {
    if (select(id + 1, &readfds, nullptr, nullptr, &t) < 0){
        perror("Error in select.");
    }
    if(FD_ISSET(id, &readfds)){
        unsigned int adrLength= sizeof(this->fIn);
        int socket = ::accept(id, (struct sockaddr*) &fIn, &adrLength);

        if(socket < 0){
            perror("Failed to accept the client.");
        }
        this->cSocket++;
        return socket;
    }
    return -1;
}

void Server::disClient() {
    this->cSocket--;
}

void Server::close() {
    ::close(this->id);
}

