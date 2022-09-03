#include <vector>
#include <pthread.h>
#include <thread>
#include <memory>
#include "CLI.h"
#include "thread"
#include "IO/SocketIO.h"
#include "IO/DefaultIO.h"
#include "Data.h"
#include "commands/Command.h"
#include "commands/ChangeAlgorithmCommand.h"
#include "commands/ClassifyCommand.h"
#include "commands/ConMatrixCommand.h"
#include "commands/FileResultCommand.h"
#include "commands/ScreenResultCommand.h"
#include "commands/UploadCommand.h"
#include "Flower.h"
#include "CsvReader.h"
#include "Classifier.h"
//#include "../Socket.h"
#include "Server.h"

void clientManagement(int socketID, Server *s);

int main(int argc, char *argv[]) {
    Server s(INADDR_ANY, htons(1234));
    while (true) {
        int cSocket = s.accept();
        if (cSocket == -1) {
            break;
        }
        std::thread clientsManage(clientManagement, cSocket, &s);
        clientsManage.detach();
    }
    while (s.getNum()) {}
    s.close();
}

void clientManagement(int socketID, Server *s) {
    std::vector<Flower> vect;
    Classifier<Flower> cls(vect, 0);
    Data<Flower> data(&cls);
    SocketIO sio(socketID);

    std::vector<std::shared_ptr<Command<Flower>>> commandVec;

    commandVec.push_back(std::make_shared<UploadCommand<Flower>>(&sio, &data));
    commandVec.push_back(std::make_shared<ChangeAlgorithmCommand<Flower>>(&sio, &data));
    commandVec.push_back(std::make_shared<ClassifyCommand<Flower>>(&sio, &data));
    commandVec.push_back(std::make_shared<ScreenResultsCommand<Flower>>(&sio, &data));
    commandVec.push_back(std::make_shared<FileResultsCommand<Flower>>(&sio, &data));
    commandVec.push_back(std::make_shared<ConMatrixCommand<Flower>>(&sio, &data));

    CLI<Flower> cli(&sio, std::move(commandVec));
    cli.start();
    s->disClient();
}