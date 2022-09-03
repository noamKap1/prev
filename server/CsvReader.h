#ifndef ASS2_CSVREADER_H
#define ASS2_CSVREADER_H

#include "vector"
#include "string"
#include "Flower.h"
#include "Classifier.h"
template<class T>
std::vector<std::vector<std::string> > readFromCSV(const std::string &path);

void writeToCSV(const std::string &filePath, const std::vector<std::string> &dataVector);

//Calculates the euclidean distance of each flower to the unclassified flower
std::vector<double> lengthArrEuc(std::vector<Flower> data, Flower &unclassified);

//Calculates the chebyshev distance of each flower to the unclassified flower
std::vector<double> lengthArrChev(std::vector<Flower> data, Flower &unclassified);

//Calculates the manhattan distance of each flower to the unclassified flower
std::vector<double> lengthArrMan(std::vector<Flower> data, Flower &unclassified);


//Returns vector which contains all the flower types
std::vector<std::string> typeArr(std::vector<Flower> data);

std::vector<std::string> stringSplitter(const std::string &, char);

std::string readF(const std::string &);

void writeF(const std::string &path, const std::string &string);

std::string receiver(int);

void sender(int, const std::string &);



#endif //ASS2_CSVREADER_H
