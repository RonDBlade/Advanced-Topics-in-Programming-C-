#include "maze.h"

Maze::Maze(unsigned int maxSteps_, unsigned int rows_, unsigned int cols_): maxSteps(maxSteps_), rows(rows_), cols(cols_), mazeValid(true){
    mazeData.resize(rows);
    for(unsigned int i = 0; i < rows; i++){
        mazeData[i].resize(cols);
    }
}

string fixInputLine(string line, int required_length){
    int line_length = line.length();
    if (line_length > required_length){
        return line.substr(0, required_length);
    }
    if (line_length < required_length){
        return line.append(required_length - line_length, '0');
    }
    return line;
}

bool Maze::readMaze(ifstream input_file){
    string line;
    int current_line;
    while (getline(input_file, line) && current_line < rows){
        line = fixInputLine(line, cols);
        mazeData[current_line++] = vector<char>(line.begin(), line.end());
    }
    while (current_line < rows){
        mazeData[current_line++] = vector<char>(fixInputLine("", cols));
    }
}

bool Maze::findCharInMaze(char charToFind)const{
    bool found_char = false;
    iterator place_found_iter;
    for (vector::iterator it = mazeData.begin(); it != mazeData.end(); it++){
        place_found_iter = std::find(it.begin(), it.end(), charToFind);
        if (place_found_iter){
            if(found_char){// We found it twice - not good
                printErrorHeader();
                cout << "More than one " << charToFind << " in maze" << endl;
                return false;
            }
            found_char = true;
            switch (charToFind){
            case '@':
                startPos.first = distance(mazeData.begin(), it);
                startPos.second = distance(it.begin(), place_found_iter);
                break;
            case '$':
                treasurePos.first = distance(mazeData.begin(), it);
                treasurePos.second = distance(it.begin(), place_found_iter);
                break;
            }
            place_found_iter = std::find(place_found_iter, it.end, charToFind);
            if (place_found_iter){// Found the char again in the rest of the line
                printErrorHeader();
                cout << "More than one " << charToFind << " in maze" << endl;
                return false;
            }
        }
    }
    if (!found_char){
        printErrorHeader();
        cout << "Missing " << charToFind << " in maze" << endl;
        return false;
    }
    return true;
}

bool Maze::checkWrongChars(string allowedChars)const{
    for (vector::iterator it = mazeData.begin(); it != mazeData.end(); it++){
        if (it.has_not_of(allowedChars)){
            printErrorHeader();
            return false;
        }
    }
    return true;
}

bool Maze::parse_maze(ifstream input_file){
    unsigned int curr_col, curr_row = 0;
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
