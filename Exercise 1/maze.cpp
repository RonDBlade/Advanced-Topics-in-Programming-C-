#include "maze.h"

using std::vector;
using std::string;

Maze::Maze(unsigned int maxSteps_, unsigned int rows_, unsigned int cols_): maxSteps(maxSteps_), rows(rows_), cols(cols_){
    mazeData.resize(rows);
    for(unsigned int i = 0; i < rows; i++){
        mazeData[i].resize(cols);
    }
}

//TODO: Fix implementation to trim/pad a line according to it's length
//and check if it's valid using     return str.find_first_not_of("0123456789") == std::string::npos;
//Then, search for treasure and player in any way - char checking or finding indexes
//Lastly, add line to vector by pushing it in any suitable way
bool Maze::parse_maze(ifstream input_file){
    unsigned int curr_col, curr_row = 0;
    bool saw_treasue = false;
    bool saw_player = false;
    string line;
    istringstream iss;
    char current_cell;
    while ((curr_row < rows) && maze_valid){
        getline(input_file, line);
        iss(line);
        curr_col = 0;
        while (((curr_col < cols) && (curr_col < line.length())) && maze_valid){
                iss >> current_cell;
                mazeData[curr_row][curr_col] = current_cell;
                switch(current_cell){
                    case ' ':
                        break;
                    case '@':
                        if (saw_player){
                                std::cout << "More than one @ in maze";
                                return false;
                                }
                        saw_player = true;
                        break;
                    case '$':
                        if (saw_treasue){
                            std::cout << "More than one $ in maze";
                                return false;
                        }
                        saw_treasue = true;
                        break;
                    default:

                        }
                mazeData[curr_row][curr_col] << line[curr_col];
                curr_col++;
        }
        while (curr_col < cols){
            mazeData[curr_row][curr_col] << ' ';
            curr_col++;
        }
        curr_row++;
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
