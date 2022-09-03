#include "Command.h"
#include "../Classifier.h"
#include "../CsvReader.h"
#include "../distances/EucDistance.h"
#include "../distances/CheDistance.h"
#include "../distances/ManDistance.h"
#include "stdexcept"
#include "algorithm"
#include <memory>

#ifndef CLIENT_CHANGEALGORITHMCOMMAND_H
#define CLIENT_CHANGEALGORITHMCOMMAND_H

template<class T>
class ChangeAlgorithmCommand : public Command<T> {
public:
    explicit ChangeAlgorithmCommand(DefaultIO *io, Data<T> *data) : Command<T>("algorithm settings", io,
                                                                                        data) {}

    void execute() override {
        this->getIO()->IOWrite(this->getData()->getClassifier()->toString());
        std::string str = this->getIO()->IORead();
        if (str.empty()) {
            this->getIO()->IOWrite(this->getData()->getClassifier()->toString());
            return;
        }
        std::vector<std::string> param = stringSplitter(str, ' ');
        if (param.size() != 2) {
            this->getIO()->IOWrite("Error: the program expects 2 parameters.");
            return;
        }
        int k;
        try {
            k = std::stoi(param[0]);
        } catch (const std::invalid_argument &exception) {
            this->getIO()->IOWrite("Invalid value for K");
            return;
        }
        if (k > 10 || k < 1) {
            this->getIO()->IOWrite("Invalid value for K");
            return;
        }
        std::unique_ptr<Distance<T>> distance;
        std::string distanceType = param[1];
        std::transform(distanceType.begin(), distanceType.end(), distanceType.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (distanceType == "euc" || distanceType == "EUC") {
            distance = std::unique_ptr<EucDistance < T>>();
        } else if (distanceType == "man" || distanceType == "MAN") {
            distance = std::unique_ptr<ManDistance < T>>();
        } else if (distanceType == "che" || distanceType == "CHE") {
            distance = std::unique_ptr<CheDistance<T>>();
        } else {
            this->getIO()->IOWrite("Invalid distance metric for distance type");
            return;
        }
        this->getData()->getClassifier()->setDistance(distance);
        this->getData()->getClassifier()->setK(k);
        this->getIO()->IOWrite(this->getData()->getClassifier()->toString());
    }
};

#endif //CLIENT_CHANGEALGORITHMCOMMAND_H
