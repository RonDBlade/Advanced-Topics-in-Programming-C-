#ifndef ALGORITHMLOADER_H_INCLUDED
#define ALGORITHMLOADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

class AlgorithmLoader{
    static AlgorithmLoader instance;
    std::vector<std::function<std::unique_ptr<AbstractAlgorithm>()>> factoryVec;

public:
    void registerAlgorithm();
    void sayAll() const;

    static AlgorithmLoader& getInstance() {
        return instance;
    }
};

#endif // ALGORITHMLOADER_H_INCLUDED
