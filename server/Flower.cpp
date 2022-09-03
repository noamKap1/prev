#include "Flower.h"
#include "CsvReader.h"
#include <cmath>

//Returns the flower type
std::string Flower::getFlowerType() const {
    return type;
}

//calculates the euclidean distance
double Flower::distance(const Flower &other) const {
    return this->calcEucDistance(other);

}

//calculates the euclidean distance
double Flower::calcEucDistance(const Flower &other) const {
    return std::sqrt(std::pow(this->widthOfSepal - other.widthOfSepal, 2)
                     + std::pow(this->lengthOfSepal - other.lengthOfSepal, 2) +
                     std::pow(this->lengthOfPetal - other.lengthOfPetal, 2)
                     + std::pow(this->widthOfPetal - other.widthOfPetal, 2));
}

//calculates the chebyshev distance
double Flower::calcChevDistance(const Flower &flower) const {
    return std::max(std::max(std::abs(this->widthOfPetal - flower.widthOfPetal),
                             std::abs(this->widthOfSepal - flower.widthOfSepal)),
                    std::max(std::abs(this->lengthOfPetal - flower.lengthOfPetal),
                             std::abs(this->lengthOfSepal - flower.lengthOfSepal)));
}

//calculates the manhattan distance
double Flower::calcManDistance(const Flower &flower) const {
    return std::abs(this->widthOfPetal - flower.widthOfPetal) +
           std::abs(this->widthOfSepal - flower.widthOfSepal) +
           std::abs(this->lengthOfPetal - flower.lengthOfPetal) +
           std::abs(this->lengthOfSepal - flower.lengthOfSepal);
}

//Construct a Flower s a vector that contains its coordinates
Flower::Flower(const std::vector<std::string> &v) :
        lengthOfSepal(std::stod(v[0])),
        widthOfSepal(std::stod(v[1])),
        widthOfPetal(std::stod(v[2])),
        lengthOfPetal(std::stod(v[3])) {
    if (v.size() == 5) {
        this->type = v.at(4);
    }

}

//Construct a Flower according to s and the separated s.
Flower::Flower(const std::string &s) : Flower(stringSplitter(s, ' ')) {

}

//build and return flower vector which contains data which we get s the function
std::vector<Flower> flowerVector(const std::vector<std::vector<std::string>> &data) {
    std::vector<Flower> result;
    for (const auto &v: data) {
        Flower iris(v);
        result.push_back(iris);
    }
    return result;
}

Flower::Flower(const std::vector<std::string> &v, bool isClassified) : isClf(isClassified) {
    if (isClassified) {
        for (int i = 0; i < v.size() - 1; i++) {
            this->coordinates.push_back(std::stod(v[i]));
        }
        this->type = v[v.size() - 1];
    } else {
        for (const auto &i: v) {
            this->coordinates.push_back(std::stod(i));
        }
    }
}


Flower::Flower(const Flower &unclassified, std::string classification) : coordinates(unclassified.getVector()),
                                                                   type(std::move(classification)),
                                                                   isClf(true) {}

std::vector<double> Flower::getVector() const {
    return this->coordinates;
}

std::vector<Flower> stringToFlowersVector(const std::string &encoding, bool isClassified) {
    std::vector<std::string> flowerEncodings = stringSplitter(encoding, '\n');
    std::vector<Flower> flowers;
    int coorNum = stringSplitter(flowerEncodings[0], ',').size();
    for (const std::string &coordinatesEncoding: flowerEncodings) {
        std::vector<std::string> coor = stringSplitter(coordinatesEncoding, ',');
        if (coor.size() < 2) {
            throw std::invalid_argument("Iris should have at least one coordinate");
        }
        if (coor.size() != coorNum) {
            throw std::invalid_argument("All Irises should have the same amount of coordinates");
        }
        try {
            flowers.emplace_back(coor, isClassified);
        }
        catch (const std::exception &e) {
            throw std::invalid_argument("Invalid coordinates");
        }
    }
    return flowers;
}



