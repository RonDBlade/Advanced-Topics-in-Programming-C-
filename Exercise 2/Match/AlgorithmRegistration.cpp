#include "AlgorithmRegistration.h"

AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
    AlgorithmLoader::getInstance().registerAlgorithm(algorithm);
}
