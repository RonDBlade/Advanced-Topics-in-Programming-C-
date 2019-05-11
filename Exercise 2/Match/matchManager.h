#ifndef MATCHMANAGER_H_INCLUDED
#define MATCHMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include "gameManager.h"
#include "parser.h"


using std::string;

class matchManager{
    static matchManager instance;
    std::vector<pair <string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> loadedAlgorithms;

public:
    void registerAlgorithm(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
        loadedAlgorithms.push_back(std::make_pair("", algorithm));
    }
    static matchManager& getInstance() {
        return instance;
    }
    void processMatch (int num_of_arguments, char *arguments[]);
};

#endif // MATCHMANAGER_H_INCLUDED
