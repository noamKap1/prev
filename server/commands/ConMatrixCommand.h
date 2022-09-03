
#ifndef ASS3_CONMATRIXCOMMAND_H
#define ASS3_CONMATRIXCOMMAND_H

#include "Command.h"
#include "memory"
#include "../Flower.h"
#include "../Classifier.h"
#include <map>

#define DESC "display algorithm confusion matrix"

template<class T>
class ConMatrixCommand : public Command<T> {

public:
    ConMatrixCommand(DefaultIO *io_ptr, Data<T> *dataManager) : Command<T>(DESC, io_ptr, dataManager) {}

    std::string MatToString(std::vector<std::vector<double>> mat) {
        std::string str;
        for (int i = 0; i < this->getData()->getTest().size(); i++) {
            std::string row = this->getData()->getTest()[i].getFlowerType();
            for (const auto &e: mat[i]) {
                row += "\t" + std::to_string(e) + "%";
            }
            str += row + "\n";
        }
        return str;
    }

    void execute() override {
        std::vector<std::string> classified = this->getData()->getClassified();
        std::vector<T> testVec = this->getData()->getTest();
        std::vector<std::string> flowerTypes;

        if (classified.empty()) {
            this->getIO()->IOWrite("Please classify first.");
            return;
        }
        const int N = testVec.size();

        std::map<std::string, std::map<std::string, double>> elementsMap;
        for (int i = 0; i < N; i++) {
            if (!elementsMap[testVec[i].getFlowerType()].count(classified[i])) {
                elementsMap[testVec[i].getFlowerType()][classified[i]] = 0;
            }
            elementsMap[testVec[i].getFlowerType()][classified[i]]++;
        }

        for (const auto &p: elementsMap) {
            double sumOfApperances = 0;
            for (const auto &k: p.second) {
                sumOfApperances += k.second;
            }

            for (const auto &k: p.second) {
                elementsMap[p.first][k.first] = (k.second * 100) / sumOfApperances;
            }

            flowerTypes.push_back(p.first);
        }

        for (const auto &p: elementsMap) {
            for (const std::string &flowerType: flowerTypes) {
                if (!elementsMap.at(p.first).count(flowerType)) {
                    elementsMap[p.first][flowerType] = 0;
                }
            }
        }

        std::vector<std::vector<double>> mat;

        for(const auto &percentages : elementsMap){
            std::vector<double> prediction;
            for(const auto &predict : percentages.second){
                prediction.push_back(predict.second);
            }
            mat.push_back(prediction);
        }
        
        this->getIO()->IOWrite(MatToString(mat));
        this->getIO()->IOWrite(this->getData()->getClassifier()->toString());
        this->getIO()->IORead();
    }


};


#endif //ASS3_CONMATRIXCOMMAND_H
