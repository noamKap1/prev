#ifndef ASS2_CLIENT_H
#define ASS2_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "string"

class Client {
private:
    bool connected = false;
    int socket;
    struct sockaddr_in in;
public:
    void stringSender(std::string) const;

    std::string stringReceiver() const;

    void closer() const;

    Client(in_addr_t, in_port_t);

    ~Client() = default;
};


#endif //ASS2_CLIENT_H
