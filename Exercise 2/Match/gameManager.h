#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "parser.h"
#include "maze.h"
#include "AbstractAlgorithm.h"
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>

using std::pair;

class gameInstance{
    pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> algorithm;
    pair<int, int> playerPos;
    vector<pair<int, int>> bookmarkPositions;
    bool foundTreasure;
    std::ostream outputFile;
    int stepsTaken;

public:
    gameInstance(std::shared_ptr<Maze> gameMaze_, pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> algorithm_, string outputFolder_);
};

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

vector<gameInstance> runAlgorithmsOnMaze(std::shared_ptr<Maze> gameMaze, vector<pair<string, vector<std::function<std::unique_ptr<AbstractAlgorithm>()>>>> loadedAlgorithms, string outputFolder);

#endif // GAMEMANAGER_H_INCLUDED
