#include <fstream>
#include <sstream>
#include "CsvReader.h"
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <regex>

//Read a csv file and return a matrix of its lines
std::vector<std::vector<std::string>> readFromCSV(const std::string &path) {
    std::ifstream fin(path);
    if (!fin.is_open()){
        std::cout << "cannot open the file" << std::endl;
    }
    std::vector<std::vector<std::string>> data;
    std::string line;
    while (fin.good()) {
        std::getline(fin, line);
        std::stringstream ss(line);
        std::vector<std::string> row = stringSplitter(line, ',');
        if (!row.empty())
            data.push_back(row);
    }
    return data;
}

//Write to a csv file
void writeToCSV(const std::string &path, const std::vector<std::string> &data) {
    std::ofstream fout(path);

    for (const std::string &line: data) {
        fout << line << std::endl;
    }
}

std::vector<std::string> stringSplitter(const std::string &string, const char c) {
    std::stringstream stringStream(string);
    std::string str;
    std::vector<std::string> vector;
    while (std::getline(stringStream, str, c)) {
        vector.push_back(str);
    }
    return vector;
}

std::string readF(const std::string &path) {
    std::ifstream fin(path);
    if (!fin.is_open()){
        std::cout << "cannot open the file" << std::endl;
    }
    std::stringstream out;
    out << fin.rdbuf();
    return out.str();
}

void writeF(const std::string &path, const std::string &string) {
    std::ofstream fout(path);
    fout << string;
}

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