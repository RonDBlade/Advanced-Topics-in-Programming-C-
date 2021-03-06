#include "maze.h"

Maze::Maze(int maxSteps_, int rows_, int cols_): maxSteps(maxSteps_), rows(rows_), cols(cols_), mazeValid(true){
    mazeData.reserve(rows);
}

bool Maze::parse_maze(ifstream &input_file){
    bool is_valid_maze = true;
    readMaze(input_file);
    if (!findCharInMaze('@')){
        is_valid_maze = false;
    }
    if (!findCharInMaze('$')){
        is_valid_maze = false;
    }
    return checkWrongChars("@$# ") || is_valid_maze;
}

pair<int, int> Maze::getStart()const{
    return startPos;
}

pair<int, int> Maze::getTreasure()const{
    return treasurePos;
}

int Maze::getMaxSteps()const{
    return maxSteps;
}

int Maze::getRows()const{
    return rows;
}

int Maze::getCols()const{
    return cols;
}

char Maze::getChar(pair<int, int> mazePos)const{
    return mazeData[mazePos.second][mazePos.first];
}

