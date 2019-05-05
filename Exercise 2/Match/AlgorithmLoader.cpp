#include "AlgorithmLoader.h"

AlgorithmLoader AlgorithmLoader::instance;

void registerAlgorithm(std::string algorithmFileName) {
    void *handle;
    std::unique_ptr<AbstractAlgorithm> algorithm;
    char *error;
    handle = dlopen (algorithmFileName, RTLD_LAZY);
    if (!handle) {
        fprintf (stderr, "%s\n", dlerror());
        exit(1);
    }
    dlerror();
    algorithm = dlsym(handle, "NEED TO ADD ALGORITHM SYMBOL HERE");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    dlclose(handle);
    factoryVec.push_back(algorithm);
}

void AlgorithmLoader::loadAll() const {
    for(auto algorithmFactory : factoryVec) {
        algorithmFactory()->loadAlgorithm();
    }
}
