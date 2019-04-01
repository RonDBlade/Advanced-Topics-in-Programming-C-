#include "maze.h"

Maze::Maze(unsigned int maxSteps_, unsigned int rows_, unsigned int cols_): maxSteps(maxSteps_), rows(rows_), cols(cols_), mazeValid(true){
    mazeData.resize(rows);
    for(unsigned int i = 0; i < rows; i++){
        mazeData[i].resize(cols);
    }
}

bool Maze::parse_maze(ifstream input_file){
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

char Maze::getChar(pair<unsigned int, unsigned int> mazePos)const{
    return mazeData<mazePos.first><mazePos.second>;
}

bool Maze::printErrorHeader(){
    if (mazeValid){
        cout << "Bad maze in maze file:" << endl;
        mazeValid = false;
    }
}
