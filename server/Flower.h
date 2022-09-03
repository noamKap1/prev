#ifndef ASS2_FLOWER_H
#define ASS2_FLOWER_H

#include <string>
#include <vector>
#include "Classifiable.h"

//Flower class
class Flower : public Classifiable<Flower> {
private:
    //coordinates and flowerType
    double lengthOfPetal, widthOfPetal, lengthOfSepal, widthOfSepal;
    bool isClf;
    std::string type = "None";
    std::vector<double> coordinates;
public:
    //calculates the euclidean distance
    double distance(const Flower &) const override;

    //calculates the euclidean distance
    double calcEucDistance(const Flower &) const override;

    //calculates the chebyshev distance
    double calcChevDistance(const Flower &) const override;

    //calculates the manhattan distance
    double calcManDistance(const Flower &) const override;

    std::string getFlowerType() const override;

    std::vector<double> getVector() const override;

    //Construct a Flower s a vector that contains its coordinates
    explicit Flower(const std::vector<std::string> &);

    explicit Flower(const std::vector<std::string> &, bool);

    explicit Flower(const Flower &, std::string);
    //Construct a Flower according to s and the separated s.
    explicit Flower(const std::string &);

    Flower(Flower &&o) = default;

    Flower(const Flower &o) = default;

    Flower &operator=(const Flower &) = default;

    ~Flower() = default;
};

//build and return flower vector which contains data which we get s the function
std::vector<Flower> flowerVector(const std::vector<std::vector<std::string>> &);

std::vector<Flower> stringToFlowersVector(const std::string &, bool);



#endif //ASS2_FLOWER_H
