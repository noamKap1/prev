#include "SocketIO.h"
#include "Csv.h"
#include "string"
#include <unistd.h>

SocketIO::SocketIO(int socket) : i(socket) {}

void SocketIO::IOWrite(std::string message) {
    sender(this->i, message);
}

std::string SocketIO::IORead() {
    return receiver(this->i);
}

SocketIO::~SocketIO() {
    close(this->i);
}