#ifndef ASS2_CSVREADER_H
#define ASS2_CSVREADER_H

#include "vector"
#include "string"

std::vector<std::vector<std::string> > readFromCSV(const std::string &path);

void writeToCSV(const std::string &filePath, const std::vector<std::string> &dataVector);

std::vector<std::string> stringSplitter(const std::string &, char);

std::string readF(const std::string &);

void writeF(const std::string &path, const std::string &string);

std::string receiver(int);

void sender(int, const std::string &);


#endif //ASS2_CSVREADER_H
