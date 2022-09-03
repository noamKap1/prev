#include "Distance.h"
#include "vector"
#include <cstdio>
#include <cmath>

#ifndef CLIENT_EUCDISTANCE_H
#define CLIENT_EUCDISTANCE_H

template<class T>
class EucDistance : public Distance<T> {
public:
    std::string toString() const override {
        return "EUC";
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
        double d = 0;
        for (int i = 0; i < firstTCoor.size(); i++) {
            d += std::pow(firstTCoor.at(i) - secondTCoor.at(i), 2);
        }
        d = std::pow(d, 0.5);
        return d;
    }
};

#endif //CLIENT_EUCDISTANCE_H
