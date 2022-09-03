#ifndef ASS2_CLASSIFIER_H
#define ASS2_CLASSIFIER_H

#include <algorithm>
#include "Flower.h"
#include "vector"
#include "string"
#include "map"
#include "type_traits"
#include "distances/Distance.h"
#include "string"
#include "distances/EucDistance.h"
#include "memory"

template<class T>
class Classifier {
private:
    //List of the classifiables
    std::vector<T> dataVector;
    //The k of the kkl algorithm
    int numOfEll = 5;
    std::unique_ptr<Distance<T>> distance = std::unique_ptr<EucDistance<T>>();


public:
    //Construct a Classifier
    explicit Classifier(const std::vector<T> &data, int k) : numOfEll(k) {
        for (auto object: data) {
            this->dataVector.push_back(object);
        }
    }
    //Sets the vector field
    Classifier()= default;
    void setDataVector(std::vector<T> vector) {
        this->dataVector = vector;
    }
    void setData(const std::vector<T> &d) {
        this->dataVector.clear();
        for (auto object: d) {
            this->dataVector.push_back(object);
        }
    }

    //returns the data vector
    std::vector<T> getDataVector() {
        return this->dataVector;
    }

    void setDistance(std::unique_ptr<Distance<T>> &newDistance) {
        this->distance = std::move(newDistance);
    }

    std::string getDistance() {
        return distance->toString();
    }

    void setK(int newK) {
        this->numOfEll = newK;
    }

    std::string toString() const {
        return "The current KNN parameters are: K = " + std::to_string(numOfEll) + ", distance metric = " +
               distance->toString();
    }

//Classify an unclassified Flower
//    std::string classify(T &unclassified) {
//       std::vector<T> dataClone(dataVector);
//
//        std::stable_sort(dataClone.begin(),  dataClone.end(),
//                         DistanceComparator(unclassified, this->distance));
//
//        std::map<std::string, int> appearances;
//        for(int i=0; i< numOfEll; i++){
//            if(!appearances.count(dataClone[i].))){
//
//            }
//
//        }
    std::string classify(T &unclassified, std::vector<T> vector, std::vector<double> v, std::vector<std::string> s) {
        double temp = 0;
        for (int i = 0; i < vector.size(); i++) {
            for (int j = i + 1; j < vector.size(); j++) {
                if (v[j] < v[i]) {
                    temp = v[i];
                    std::string string = s[i];
                    s[i] = s[j];
                    s[j] = string;
                    v[i] = v[j];
                    v[j] = temp;
                }
            }
        }
        std::map<std::string, int> map;
        for (int i = 0; i < numOfEll; i++) {
            if (map.count(s[i]) == 0) {
                map[s[i]] = 0;
            }
            map[s[i]]++;
        }
        int max = 0;
        std::string type;
        for (const auto &item: map) {
            if (max < item.second) {
                type = item.first;
                max = item.second;
            }
        }
        return type;
    }


//    ~Classifier() = default;
//
//    Classifier(Classifier &&o) noexcept = default;
//
//    Classifier(const Classifier &o) = default;
//
//    Classifier &operator=(const Classifier &) = default;
};


#endif //ASS2_CLASSIFIER_H
