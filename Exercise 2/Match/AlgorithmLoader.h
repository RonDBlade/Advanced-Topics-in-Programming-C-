#ifndef ALGORITHMLOADER_H_INCLUDED
#define ALGORITHMLOADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <functional>
#include <memory>
//#include <dlfcn.h>
#include "matchManager.h"

using std::string;

class AlgorithmLoader{
    static AlgorithmLoader instance;
    std::vector<std::function<std::unique_ptr<AbstractAlgorithm>()>> loadedAlgorithms;

public:
    void registerAlgorithm(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm);
    void moveAll() const;

    static AlgorithmLoader& getInstance() {
        return instance;
    }
};

#endif // ALGORITHMLOADER_H_INCLUDED
