#ifndef MATCHMANAGER_H_INCLUDED
#define MATCHMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <cstring>
#include "gameManager.h"
#include "parser.h"

using std::string;

class matchManager{
    static matchManager instance;
    std::vector<pair <string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> loadedAlgorithms;
    std::vector<Maze> loadedMazes;
    string outputFolder;
    int numOfThreads;
    RewindQueue<gameInstance> allGames;

public:
    void registerAlgorithm(std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm) {
        // Since the dlopen occurs right after adding an algorithm to the vector, we can add it at the end of the vector.
        instance.loadedAlgorithms.back().second = algorithm;
    }
    static matchManager& getInstance() {
        return instance;
    }
    std::vector<pair <string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> &getAlgorithms(){
        return instance.loadedAlgorithms;
    }
    vector<void*> registerSoFiles(vector<string>& algoFiles, vector<string>& mazeFiles);
    void setOutputFolder(string outputPath);
    void setNumberOfThreads(int amountOfThreads);
private:
    void loadMazes(vector<string>& mazeFiles);
    void pairGames();
    void printScores();
    void runGames();
    void runThreads();
};

#endif // MATCHMANAGER_H_INCLUDED
