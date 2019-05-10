#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "parser.h"
#include "maze.h"
#include "AbstractAlgorithm.h"
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>

using std::pair;

int runAlgorithmsOnMaze(shared_ptr<Maze> gameMaze, vector<AbstractAlgorithm> loadedAlgorithms);

class gameInstance{
    AbstractAlgorithm algorithm;
    pair<int, int> playerPos;
    vector<pair<int, int>> bookmarkPositions;
    bool foundTreasure;
    std::ostream outputFile;
    int stepsTaken;

public:
    gameInstance(shared_ptr<Maze> gameMaze_, pair<string, AbstractAlgorithm> algorithm_, string outputFolder_);
};

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

#endif // GAMEMANAGER_H_INCLUDED
