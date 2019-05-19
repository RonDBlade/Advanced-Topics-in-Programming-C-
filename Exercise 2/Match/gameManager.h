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
    std::function<std::unique_ptr<AbstractAlgorithm>()> algorithmGenerator;
    string algoName;
    pair<int, int> playerPos;
    vector<pair<int, pair<int, int>>> bookmarkPositions;
    bool foundTreasure;
    vector<string> gameOutput;
    int stepsTaken;
    int bookmarkCount;

public:
    gameInstance(std::shared_ptr<Maze> gameMaze_, pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> &algorithm_);

    std::unique_ptr<AbstractAlgorithm> generateAlgorithm();
    string getAlgorithmName();
    pair<int, int> getPlayerPos();
    int getPlayerRow();
    int getPlayerCol();
    vector<pair<int, pair<int, int>>> getBookmarkPositions();
    bool getFoundTreasure();
    vector<string> getGameOutput();
    int getStepsTaken();

    AbstractAlgorithm::Move moveAlgorithm(std::unique_ptr<AbstractAlgorithm> &algorithmPtr);
	void hitAlgorithmWall(std::unique_ptr<AbstractAlgorithm> &algorithmPtr);
	void hitAlgorithmBookmark(std::unique_ptr<AbstractAlgorithm> &algorithmPtr, int seq, int index);

    void setPlayerPos(pair<int, int> position);
    void setPlayerRow(int row);
    void setPlayerCol(int col);
    void addBookmarkPosition();
    void setFoundTreasure(bool treasureStatus);
    void addToGameOutput(string newLine);
    void setStepsTaken(int steps);
};

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

vector<gameInstance> runAlgorithmsOnMaze(std::shared_ptr<Maze> gameMaze, vector<pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> &loadedAlgorithms);

#endif // GAMEMANAGER_H_INCLUDED
