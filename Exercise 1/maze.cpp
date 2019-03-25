#include "maze.h"

using std::vector;
using std::string;

Maze::Maze(unsigned int maxSteps_, unsigned int rows_, unsigned int cols_): maxSteps(maxSteps_), rows(rows_), cols(cols_){
    mazeData.resize(rows);
    for(unsigned int i = 0; i < rows; i++){
        mazeData[i].resize(cols);
    }
}

void Maze::parse_maze(ifstream input_file){
    unsigned int curr_col, curr_row = 0;
    string line;
    while (curr_row < rows){
        getline(input_file, line);
        curr_col = 0;
        while ((curr_col < cols) && (curr_col < line.length())){
        }
    }
}

pair<unsigned int, unsigned int> Maze::getStart()const{
    return startPos;
}

unsigned int Maze::getMaxSteps()const{
    return maxSteps;
}

char Maze::getChar(pair<unsigned int, unsigned int> mazePos)const{
    return mazeData<mazePos.first><mazePos.second>;
}
