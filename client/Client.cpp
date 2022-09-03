#include <string>
#include <unistd.h>
#include <cstring>
#include "Client.h"
#include "CsvReader.h"

Client::Client(in_addr_t ip, in_port_t port) : socket(::socket(AF_INET, SOCK_STREAM, 0)), in() {
    if(socket >= 0){
        memset(&in, 0, sizeof(in));
        in.sin_family = AF_INET;
        in.sin_addr.s_addr = ip;
        in.sin_port = port;
    } else {
        perror("Error in creating the i!");

    }
}

void Client::stringSender(std::string str) const {
    sender(socket, str);
}


std::string Client::stringReceiver() const {
    return receiver(socket);
}

void Client::closer() const {
    close(this->socket);
}


