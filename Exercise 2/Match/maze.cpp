#include "maze.h"

Maze::Maze(): mazeName(""), maxSteps(0), rows(0), cols(0), mazeValid(false){
    //Empty constructors used as "Dummy" when no maze exists yet
}

Maze::Maze(string mazeName_, int maxSteps_, int rows_, int cols_): mazeName(mazeName_), maxSteps(maxSteps_), rows(rows_), cols(cols_), mazeValid(true){
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
    return checkWrongChars("@$# \r") && is_valid_maze;
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

string Maze::getMazeName()const{
    return mazeName;
}

bool Maze::isValidMaze()const{
    return mazeValid;
}

string fixInputLine(string line, int required_length){
    int line_length = line.length();
    if (line_length > required_length){
        return line.substr(0, required_length);
    }
    if (line_length < required_length){
        return line.append(required_length - line_length, ' ');
    }
    return line;
}

void Maze::readMaze(ifstream& input_file){
    string line;
    int current_line = 0;
    while (getline(input_file, line) && current_line++ < rows){
        line = fixInputLine(line, cols);
        mazeData.push_back(line);
    }
    while (current_line++ < rows){
        line = fixInputLine("", cols);
        mazeData.push_back(line);
    }
}


bool Maze::findCharInMaze(char charToFind){
    bool found_char = false;
    size_t index_of_char;
    for (auto it = mazeData.begin(); it != mazeData.end(); it++){
        index_of_char = (*it).find(charToFind);
        if (index_of_char != string::npos){
            if(found_char){// We found it twice - not good
                printErrorHeader();
                cout << "More than one " << charToFind << " in maze" << endl;
                return false;
            }
            found_char = true;
            switch (charToFind){
            case '@':
                startPos.first = index_of_char;
                startPos.second = distance(mazeData.begin(), it);
                break;
            case '$':
                treasurePos.first = index_of_char;
                treasurePos.second = distance(mazeData.begin(), it);
                break;
            }
            index_of_char = (*it).find(charToFind, index_of_char + 1);
            if (index_of_char != string::npos){// Found the char again in the rest of the line
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

void Maze::printErrorHeader(){
    if (mazeValid){
        cout << "Bad maze in maze file:" << endl;
        mazeValid = false;
    }
}

bool Maze::checkWrongChars(string allowedChars){
    std::size_t index_of_char;
    bool is_valid = true;
    for (vector<string>::iterator it = mazeData.begin(); it != mazeData.end(); it++){
        index_of_char = (*it).find_first_not_of(allowedChars);
        if (index_of_char != string::npos){
            printErrorHeader();
            if ((*it)[index_of_char] != '\t'){
                cout << "Wrong character in maze: " << (*it)[index_of_char] << " in row " << distance(mazeData.begin(), it)+1 << ", col " << index_of_char+1 << endl;
            }
            else{
                cout << "Wrong character in maze: TAB in row " << distance(mazeData.begin(), it)+1 << ", col " << index_of_char+1 << endl;
            }
            is_valid = false;
        }
    }
    return is_valid;
}
