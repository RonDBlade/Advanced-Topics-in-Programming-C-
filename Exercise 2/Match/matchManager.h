#ifndef MATCHMANAGER_H_INCLUDED
#define MATCHMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include "gameManager.h"
#include "parser.h"


using std::string;

class matchManager(){
    std::vector<std::function<std::unique_ptr<AbstractAlgorithm>()>> loadedAlgorithms;
};

#endif // MATCHMANAGER_H_INCLUDED
