#include "AlgorithmRegistration.h"
#include "matchManager.h"

AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
    matchManager::getInstance().registerAlgorithm(algorithm);
}
