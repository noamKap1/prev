#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vector"
#include "CsvReader.h"
#include "Client.h"
#include "thread"
#include <regex>

void MessagesHandler(const std::string &message, Client *c);

void receive(Client *c);

int main(int argc, char *argv[]) {
    Client client(inet_addr("127.0.0.1"), htons(1234));
    std::thread thread(receive, &client);
    while (true) {
        std::string str;
        getline(std::cin, str);
        str = readF(str);

        client.stringSender(str);
    }
}

void MessagesHandler(const std::string &message, Client *c) {
    if(message != "exit"){
        std::smatch results;
        std::regex regex("SAVE <((.|\\n)+)> TO <(.*)>");
        if (std::regex_search(message, results, regex)) {
            writeF(results[3].str(), results[1].str());
        } else {
            std::cout << message << std::endl;
        }
    } else {
        c->closer();
        exit(0);
    }
}
void receive(Client *c) {
    while (true) {
        const std::string &message = c->stringReceiver();
        MessagesHandler(message, c);
    }
}
