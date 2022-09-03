#include "Command.h"

#ifndef CLIENT_SCREENRESULTCOMMAND_H
#define CLIENT_SCREENRESULTCOMMAND_H

template<class T>
class ScreenResultsCommand : public Command<T> {
public:
    ScreenResultsCommand(DefaultIO *io, Data<T> *data) : Command<T>("display data", io, data) {}

    void execute() override {
        if (this->getData()->getClassified().empty()) {
            this->getIO()->IOWrite("Error: you need to Classify first to get the results.");
            return;
        }
        for (int i = 0; i < this->getData()->getClassified().size(); i++) {
            this->getIO()->IOWrite(std::to_string(i + 1) + '\t' + this->getData()->getClassified()[i]);
        }
        this->getIO()->IOWrite("Done.");
        this->getIO()->IORead();
    }

};

#endif //CLIENT_SCREENRESULTCOMMAND_H
