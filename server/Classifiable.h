#ifndef ASS2_CLASSIFIABLE
#define ASS2_CLASSIFIABLE

//Classifiable interface
template<class T>
class Classifiable {
    //calculates the euclidean distance
    virtual double distance(const T &other) const = 0;

    //calculates the euclidean distance
    virtual double calcEucDistance(const T &other) const = 0;

    //calculates the chebyshev distance
    virtual double calcChevDistance(const T &other) const = 0;

    //calculates the manhattan distance
    virtual double calcManDistance(const T &other) const = 0;

    //returns the flower type
    virtual std::string getFlowerType() const = 0;

    virtual std::vector<double> getVector() const = 0;
};


#endif //ASS2_CLASSIFIABLE_H
