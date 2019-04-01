#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>

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
    vector<vector<char> > mazeData;



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

    void readMaze(ifstream input_file){
        string line;
        unsigned int current_line;
        while (getline(input_file, line) && current_line < rows){
            line = fixInputLine(line, cols);
            mazeData[current_line++] = vector<char>(line.begin(), line.end());
        }
        while (current_line < rows){
            line = fixInputLine("", cols);
            mazeData[current_line++] = vector<char>(line.begin(), line.end());
        }
    }


    bool findCharInMaze(char charToFind)const{
        bool found_char = false;
        vector<char>::iterator place_found_iter;
        vector<vector<char> >::iterator it;
        for (it = mazeData.begin(); it != mazeData.end(); it++){
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

    bool checkWrongChars(string allowedChars)const{
        for (vector::iterator it = mazeData.begin(); it != mazeData.end(); it++){
            if (it.has_not_of(allowedChars)){
                printErrorHeader();
                return false;
            }
        }
        return true;
    }

public:
    Maze(unsigned int maxSteps_, unsigned int rows_, unsigned int cols_);
    void parse_maze(ifstream input_file);
    pair<unsigned int, unsigned int> getStart()const;
    pair<unsigned int, unsigned int> getTreasure()const;
    unsigned int getMaxSteps()const;
    char getChar(pair<unsigned int, unsigned int>)const;
};

#endif // MAZE_H_INCLUDED
