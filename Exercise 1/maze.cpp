#include "maze.h"

Maze::Maze(unsigned int maxSteps_, unsigned int rows_, unsigned int cols_): maxSteps(maxSteps_), rows(rows_), cols(cols_), mazeValid(true){
    mazeData.reserve(rows);
}

bool Maze::parse_maze(ifstream &input_file){
    readMaze(input_file);
    if (!findCharInMaze('@')){
        return false;
    }
    if (!findCharInMaze('$')){
        return false;
    }
    return checkWrongChars("@$# ");
}

pair<unsigned int, unsigned int> Maze::getStart()const{
    return startPos;
}

pair<unsigned int, unsigned int> Maze::getTreasure()const{
    return treasurePos;
}

unsigned int Maze::getMaxSteps()const{
    return maxSteps;
}

unsigned int Maze::getRows()const{
    return rows;
}

unsigned int Maze::getCols()const{
    return cols;
}

char Maze::getChar(pair<unsigned int, unsigned int> mazePos)const{
    return mazeData[mazePos.first][mazePos.second];
}

