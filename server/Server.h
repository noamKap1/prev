#ifndef ASS2_SERVER_H
#define ASS2_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "string"

class Server {
private:
    int id;
    int qLength = 5;
    struct sockaddr_in fIn;
    int cSocket = 0;
    fd_set readfds;
    struct timeval t;
public:
    //Construct a server according to the address and the port
    Server(in_addr_t ip, in_port_t port);

//    receives string from the i
    std::string stringReceiver();

//    Sends string to the i
    void stringSender(std::string string);

//accept client.
    int accept();

//get the number of clients.
    int getNum() const;

//close the server.
    void close();

//disconnect a client from the server.
    void disClient();


    //destructor
    ~Server() = default;
};


#endif //ASS2_SERVER_H
