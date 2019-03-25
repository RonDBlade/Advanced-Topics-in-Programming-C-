#include <maze.h>
#include <vector>
#include <fstream>
#include <string>

using std::vector;
using std::string;

MazeInfo::MazeInfo(int maxSteps_, int rows_, int cols_): maxSteps(maxSteps_), rows(rows_), cols(cols_){
    mazeData.resize(rows);
    for(int i = 0; i < rows; i++){
        mazeData[i].resize(cols);
    }
}
MazeInfo::parse_maze(ifstream input_file){
    int curr_col, curr_row = 0;
    string line;
    while (curr_row < rows){
        line = getline(input_file)
        curr_col = 0;
        while (curr_col < cols) && (cur_col < line.length()){
        }
    }
}
