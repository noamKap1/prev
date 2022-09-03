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
    std::string string;
    std::vector<std::vector<std::string>> dataVector;
    while (fin.good()) {
        std::getline(fin, string);
        std::stringstream stringStream(string);
        std::vector<std::string> vector = stringSplitter(string, ',');
        if (!vector.empty())
            dataVector.push_back(vector);
    }
    return dataVector;
}

//Calculates the euclidean distance of each flower to the unclassified flower
std::vector<double> lengthArrEuc(std::vector<Flower> data, Flower &unclassified) {
    std::vector<double> length;
    for (int i = 0; i < data.size(); i++) {
        length.push_back(data[i].calcEucDistance(unclassified));
    }
    return length;
}

//Calculates the manhattan distance of each flower to the unclassified flower
std::vector<double> lengthArrMan(std::vector<Flower> data, Flower &unclassified) {
    std::vector<double> length;
    for (int i = 0; i < data.size(); i++) {
        length.push_back(data[i].calcManDistance(unclassified));
    }
    return length;
}

//Calculates the chebyshev distance of each flower to the unclassified flower
std::vector<double> lengthArrChev(std::vector<Flower> data, Flower &unclassified) {
    std::vector<double> length;
    for (int i = 0; i < data.size(); i++) {
        length.push_back(data[i].calcChevDistance(unclassified));
    }
    return length;
}

//Returns vector which contains all the flower types
std::vector<std::string> typeArr(std::vector<Flower> data) {
    std::vector<std::string> types;
    for (int i = 0; i < data.size(); i++) {
        types.push_back(data[i].getFlowerType());
    }
    return types;
}


//Write to a csv file
void writeToCSV(const std::string &filePath, const std::vector<std::string> &dataVector) {
    std::ofstream fout(filePath);
    for (const std::string &line: dataVector) {
        fout << line << std::endl;
    }
}

//Splits the string and puts the cells into the vector
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
