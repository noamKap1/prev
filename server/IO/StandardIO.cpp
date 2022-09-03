#include "StandardIO.h"
#include "iostream"

void StandardIO::IOWrite(std::string str) {
    std::cout << str << std::endl;
}

std::string StandardIO::IORead() {
    std::string str;
    getline(std::cin, str);
    return str;
}

