#include "string"

#ifndef CLIENT_DISTANCE_H
#define CLIENT_DISTANCE_H

template<class T>
class Distance {
public:
    virtual std::string toString() const = 0;

    virtual double distance(T firstT, T secondT) const = 0;

    virtual ~Distance() = default;
};

#endif //CLIENT_DISTANCE_H
