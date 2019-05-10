#include "AlgorithmLoader.h"

AlgorithmLoader AlgorithmLoader::instance;

void AlgorithmLoader::registerAlgorithm(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
    factoryVec.push_back(algorithm);
}

void AlgorithmLoader::moveAll() const {
    for(auto algorithmFactory : factoryVec) {
        algorithmFactory()->move();
    }
}
