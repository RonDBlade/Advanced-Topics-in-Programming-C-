#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include "../Utilities/AbstractAlgorithm.h"


using std::vector;
using std::string;
using std::ifstream;
using std::pair;
using std::endl;
using std::cout;

class Maze{
    int maxSteps;
    int rows;
    int cols;
    bool mazeValid;
    pair<int, int> startPos;
    pair<int, int> treasurePos;
    vector<string> mazeData;



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

    void readMaze(ifstream& input_file){
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


    bool findCharInMaze(char charToFind){
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

    void printErrorHeader(){
        if (mazeValid){
            cout << "Bad maze in maze file:" << endl;
            mazeValid = false;
        }
    }

    bool checkWrongChars(string allowedChars){
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

public:
    Maze(int maxSteps_, int rows_, int cols_);
    bool parse_maze(ifstream &input_file);
    pair<int, int> getStart()const;
    pair<int, int> getTreasure()const;
    int getMaxSteps()const;
    int getRows()const;
    int getCols()const;
    char getChar(pair<int, int>)const;
};

#endif // MAZE_H_INCLUDED
