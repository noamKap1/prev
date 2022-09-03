#include <utility>
#include "../IO/DefaultIO.h"
#include "../Data.h"

#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

template<class T>
class Command {
private:

    Data<T> *data;
    std::string desc;
    DefaultIO *defaultIo;

public:

    Command(std::string description, DefaultIO *io, Data<T> *data) :
            desc(std::move(description)), defaultIo(io), data(data) {}

    DefaultIO *getIO() {
        return defaultIo;
    }

    std::string getDescription() {
        return std::string(desc);
    }

    Data<T> *getData() const {
        return data;
    }

    virtual void execute() = 0;

    virtual ~Command() = default;
};


#endif //CLIENT_COMMAND_H
