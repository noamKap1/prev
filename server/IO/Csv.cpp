#include <fstream>
#include <sstream>
#include "Csv.h"
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <regex>

std::string receiver(int s) {
    char buff[1];
    std::string end = "<end>";
    std::string message;
    while (!std::equal(end.rbegin(), end.rend(), message.rbegin())) {
        buff[0] = 0;
        ssize_t bytes = recv(s, buff, 1, 0);
        if (bytes < 0) {
            perror("Error in writing to the i!");
        }
        message.append(buff);
    }
    return message.substr(0, message.length() - 5);
}

void sender(int s, const std::string &str) {
    std::string message = str + "<end>";
    size_t bytes = send(s, message.c_str(), strlen(message.c_str()), 0);
    if (bytes < 0) {
        perror("Error in sending to the client!");
    }

}
