#include "../Server.h"
#include "DefaultIO.h"
#include "string"

#ifndef CLIENT_SOCKETIO_H
#define CLIENT_SOCKETIO_H


class SocketIO : public DefaultIO {
private:
    int i;
public:
    SocketIO(int socket);

    void IOWrite(std::string) override;

    std::string IORead() override;

    ~SocketIO();

};


#endif //CLIENT_SOCKETIO_H
