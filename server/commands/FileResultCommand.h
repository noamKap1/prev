#include "Command.h"
#include "sstream"

#ifndef CLIENT_FILERESULTCOMMAND_H
#define CLIENT_FILERESULTCOMMAND_H

template<class T>
class FileResultsCommand : public Command<T> {
public:
    FileResultsCommand(DefaultIO *io, Data<T> *data) : Command<T>("Download data", io, data) {}

    void execute() override {
        if (this->getData()->getClassified().empty()) {
            this->getIO()->IOWrite("Error: you need to Classify first to get the results.");
            return;
        }
        this->getIO()->IOWrite("Enter output file Path.");
        std::string filePath = this->getIO()->IORead();
        std::stringstream message;
        message << "SAVE <";
        for (int i = 0; i < this->getData()->getClassified().size(); i++) {
            message << std::to_string(i + 1) + '\t' + this->getData()->getClassified()[i] << "\n";
        }
        message << "Done." << "TO <" << filePath << ">";
        this->getIO()->IOWrite(message.str());
        this->getIO()->IORead();
    }
};

#endif //CLIENT_FILERESULTCOMMAND_H
