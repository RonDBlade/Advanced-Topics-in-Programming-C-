#include "AlgorithmRegistration.h"
#include "matchManager.h"

AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
    std::cout << "YAY" << std::endl;
    matchManager::getInstance().registerAlgorithm(algorithm);
}
