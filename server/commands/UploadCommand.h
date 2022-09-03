#include "Command.h"
#include "vector"
#include "../Flower.h"
#include "../Data.h"
#include "../IO/DefaultIO.h"

#ifndef CLIENT_UPLOADCOMMAND_H
#define CLIENT_UPLOADCOMMAND_H

template<class T>
class UploadCommand : public Command<T> {
public:
    UploadCommand(DefaultIO *io, Data<Flower> *data) :
            Command<T>("upload an unclassified csv data file", io, data) {}


    void execute() override {
        this->getIO()->IOWrite("Please upload your local train CSV file.");
        std::string str = this->getIO()->IORead();
        if (str.empty()) {
            this->getIO()->IOWrite("Error: no file found");
            return;
        }
        try {
            this->getData()->setTrain(stringToFlowersVector(str, true));
        } catch (std::exception &e) {
            this->getIO()->IOWrite("Error: Invalid file");
            return;
        }
        this->getIO()->IOWrite("Upload Complete.");
        this->getIO()->IOWrite("Please upload your local test CSV file.");
        str = this->getIO()->IORead();
        if (str.empty()) {
            this->getIO()->IOWrite("Error: no file found");
            return;
        } try {
            this->getData()->setTest(stringToFlowersVector(str, true));
        } catch (std::exception &e) {
            this->getIO()->IOWrite("Error: Invalid file");
            return;
        }
        this->getIO()->IOWrite("Upload Complete");
    }
};

#endif //CLIENT_UPLOADCOMMAND_H
