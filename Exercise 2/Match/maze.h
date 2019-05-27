#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include "AbstractAlgorithm.h"


using std::vector;
using std::string;
using std::ifstream;
using std::pair;
using std::endl;
using std::cout;

class Maze{
    string mazeName;
    int maxSteps;
    int rows;
    int cols;
    bool mazeValid;
    pair<int, int> startPos;
    pair<int, int> treasurePos;
    vector<string> mazeData;

public:
    Maze();
    Maze(string mazeName_, int maxSteps_, int rows_, int cols_);
    bool parse_maze(ifstream &input_file);
    pair<int, int> getStart()const;
    pair<int, int> getTreasure()const;
    int getMaxSteps()const;
    int getRows()const;
    int getCols()const;
    char getChar(pair<int, int>)const;
    string getMazeName()const;
    bool isValidMaze()const;

private:
    void readMaze(ifstream& input_file);
    bool findCharInMaze(char charToFind);
    void printErrorHeader();
    bool checkWrongChars(string allowedChars);
};

#endif // MAZE_H_INCLUDED
