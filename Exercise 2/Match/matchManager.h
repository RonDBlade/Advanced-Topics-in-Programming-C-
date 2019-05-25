#ifndef MATCHMANAGER_H_INCLUDED
#define MATCHMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <dlfcn.h>
#include <cstring>
#include "gameManager.h"
#include "parser.h"
#include "safeQueue.h"

using std::string;

class matchManager{
    static matchManager instance;
    std::vector<pair <string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> loadedAlgorithms;
    std::vector<Maze> loadedMazes;
    string outputFolder;
    int numOfThreads;
    SafeQueue<gameInstance> allGames;

public:
    void registerAlgorithm(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
        instance.loadedAlgorithms.back().second = algorithm;
    }
    static matchManager& getInstance() {
        return instance;
    }
    std::vector<pair <string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> &getAlgorithms(){
        return instance.loadedAlgorithms;
    }
    void processMatch(int num_of_arguments, char *arguments[]);
private:
    void registerSoFiles(vector<string> algoFiles, vector<string> mazeFiles, string outputPath);
    void loadMazes(vector<string> mazeFiles, string outputFolder);
    void pairGames();

};

#endif // MATCHMANAGER_H_INCLUDED
