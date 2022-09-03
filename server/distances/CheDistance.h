#include "Distance.h"
#include "vector"
#include <cstdio>
#include <cmath>

#ifndef CLIENT_CHEDISTANCE_H
#define CLIENT_CHEDISTANCE_H

template<class T>
class CheDistance : public Distance<T> {
public:
    std::string toString() const override {
        return "CHE";
    }

    double distance(T firstT, T secondT) const override {
        std::vector<double> firstTCoor = firstT.getVector();
        std::vector<double> secondTCoor = secondT.getVector();
        if (firstTCoor.empty()) {
            perror("Error: the vector can't be empty.");
        }
        if (firstTCoor.size() != secondTCoor.size()) {
            perror("Error: the vector lengths have to be equals.");
        }
        double d1 = std::abs(firstTCoor.at(0) - secondTCoor.at(0));
        for (int i = 1; i < firstTCoor.size(); i++) {
            double d2 = std::abs(firstTCoor.at(i) - secondTCoor.at(i));
            if (d2 > d1) {
                d1 = d2;
            }
        }
        return d1;
    }

};

#endif //CLIENT_CHEDISTANCE_H
