#ifndef MATCHMANAGER_H_INCLUDED
#define MATCHMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include <dlfcn.h>
#include <cstring>
#include "gameManager.h"
#include "parser.h"

using std::string;

class matchManager{
    static matchManager instance;
    std::vector<pair <string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> loadedAlgorithms;

public:
    void registerSoFiles(vector<string> algoFiles, vector<string> mazeFiles, string outputPath);
    void runMatches(vector<string> mazeFiles, string outputFolder);
    void registerAlgorithm(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
        instance.loadedAlgorithms.back().second = algorithm;
    }
    static matchManager& getInstance() {
        return instance;
    }
    std::vector<pair <string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> &getAlgorithms(){
        return loadedAlgorithms;
    }
    void processMatch(int num_of_arguments, char *arguments[]);
};

#endif // MATCHMANAGER_H_INCLUDED
