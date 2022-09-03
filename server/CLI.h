#include "vector"
#include <utility>
#include "commands/Command.h"

#ifndef ASS3_CLI_H
#define ASS3_CLI_H


template<class T>
class CLI {
private:
    DefaultIO *io_ptr;
    std::vector<std::shared_ptr<Command<Flower>>> commandVec;

    std::string cliMenu() {
        std::string line = "Welcome to the KNN Classifier Server. Please choose an option:";
        for (int j = 0; j < this->commandVec.size(); j++) {
            line.append("\n" + std::to_string(j + 1) + ". " + commandVec[j]->getDescription());
        }
        line.append("\n" + std::to_string(commandVec.size() + 1) + ". exit");
    }

public:
    void start() {
        while (true) {
            io_ptr->IOWrite(cliMenu());
            std::string chosen = io_ptr->IORead();
            int opt = std::stoi(chosen) - 1;
            if (opt == commandVec.size()) {
                break;
            }

            if (opt > commandVec.size() || opt < 0){
                this->io_ptr->IOWrite("Please enter a valid command.");
                continue;
            }
                commandVec[std::stoi(chosen)]->execute();
        }

    }

    //ctor
    CLI(DefaultIO *io_ptr, std::vector<std::shared_ptr<Command<Flower>>> commandVec) :
            io_ptr(io_ptr), commandVec(std::move(commandVec)) {}

};


#endif //ASS3_CLI_H
