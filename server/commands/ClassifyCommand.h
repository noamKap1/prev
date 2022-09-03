#include "thread"
#include "Command.h"

#ifndef CLIENT_CLASSIFYCOMMAND_H
#define CLIENT_CLASSIFYCOMMAND_H

template<class T>
class ClassifyCommand : public Command<T> {
public:
    ClassifyCommand(DefaultIO *io, Data<T> *data) : Command<T>("classify data", io, data) {}

    void execute() override {
        if (this->getData()->getTest().empty()) {
            this->getIO()->IOWrite("Error: Upload the train and test files first.");
            return;
        }
        std::thread clf([this] { this->getData()->classify(); });
        clf.detach();
        this->getIO()->IOWrite("classifying data complete");
    }
};

#endif //CLIENT_CLASSIFYCOMMAND_H
