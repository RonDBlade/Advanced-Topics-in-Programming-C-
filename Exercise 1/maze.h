#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <utility>

using std::vector;
using std::string;
using std::ifstream;
using std::pair;

class Maze{
    unsigned int maxSteps;
    unsigned int rows;
    unsigned int cols;
    bool mazeValid;
    pair<unsigned int, unsigned int> startPos;
    pair<unsigned int, unsigned int> treasurePos;
    vector<vector<char>> mazeData;

public:
    Maze(unsigned int maxSteps_, unsigned int rows_, unsigned int cols_);
    void parse_maze(ifstream input_file); /*why do we need this?or atleast why here?*/
    pair<unsigned int, unsigned int> getStart()const;
    unsigned int getMaxSteps()const;
    char getChar(pair<unsigned int, unsigned int>)const;
};

#endif // MAZE_H_INCLUDED
