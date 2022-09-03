#include "string"

#ifndef CLIENT_DEFAULTIO_H
#define CLIENT_DEFAULTIO_H

class DefaultIO {
public:

    virtual void IOWrite(std::string) = 0;

    virtual std::string IORead() = 0;

};

#endif //CLIENT_DEFAULTIO_H
