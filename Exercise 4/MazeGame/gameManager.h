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
    Maze gameMaze;
    string algoName;
    pair<int, int> playerPos;
    vector<pair<int, pair<int, int>>> bookmarkPositions;
    vector<string> gameOutput;
    int stepsTaken;
    int bookmarkCount;

public:
    gameInstance();
    gameInstance(Maze &gameMaze_, pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> &algorithm_);

    void runGame();
    string getAlgorithmName() const;
    string getMazeName()const;
    vector<string> getGameOutput() const;
    int getStepsTaken() const;

private:
    std::unique_ptr<AbstractAlgorithm> generateAlgorithm();
    int getPlayerRow() const;
    int getPlayerCol() const;

    AbstractAlgorithm::Move moveAlgorithm(std::unique_ptr<AbstractAlgorithm> &algorithmPtr);
	void hitAlgorithmWall(std::unique_ptr<AbstractAlgorithm> &algorithmPtr);
	void hitAlgorithmBookmark(std::unique_ptr<AbstractAlgorithm> &algorithmPtr, int seq);

    void setPlayerRow(int row);
    void setPlayerCol(int col);
    void addBookmarkPosition();
    void addToGameOutput(string newLine);
};

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

#endif // GAMEMANAGER_H_INCLUDED
