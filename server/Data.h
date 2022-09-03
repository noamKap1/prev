#include "Classifier.h"
#include "CsvReader.h"

#ifndef CLIENT_DATA_H
#define CLIENT_DATA_H

template<class T>
class Data {
private:
    std::vector<T> test;
    std::vector<std::string> classified;
    Classifier<T> *classifier;

public:
    explicit Data(Classifier<T> *Classifier) : classifier(Classifier) {}

    void setTrain(const std::vector<T> &v) {
        classifier->setData(v);
//        classifier->getDataVector().clear();
//        for (auto object: v) {
//            classifier->getDataVector().push_back(object);
//        }
    }

    const std::vector<std::string> &getTrain() const {
        return classified;
    }

    void setTest(const std::vector<T> &v) {
        this->test = v;
    }

    const std::vector<T> &getTest() const {
        return test;
    }

    Classifier<T> *getClassifier() const {
        return classifier;
    }

    const std::vector<std::string> &getClassified() const {
        return classified;
    }

    void classify() {
        classified.clear();
        std::string str = classifier->getDistance();
        if(str == "EUC"){
            for (auto t: test) {
                classified.push_back(classifier->classify(t,classifier->getDataVector(),
                                                          lengthArrEuc(classifier->getDataVector(),t),
                                                          typeArr(classifier->getDataVector())));
            }
        } else if (str == "MAN"){
            for (auto t: test) {
                classified.push_back(classifier->classify(t,classifier->getDataVector(),
                                                          lengthArrMan(classifier->getDataVector(),t),
                                                          typeArr(classifier->getDataVector())));
            }
        } else {
            for (auto t: test) {
                classified.push_back(classifier->classify(t,classifier->getDataVector(),
                                                          lengthArrChev(classifier->getDataVector(),t),
                                                          typeArr(classifier->getDataVector())));
            }
        }
    }
};

#endif //CLIENT_DATA_H
