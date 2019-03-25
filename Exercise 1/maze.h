#include <vector>
#include <fstream>
#include <string>

using std::vector;
using std::string;

class MazeInfo{
    int maxSteps;
    int rows;
    int cols;
    vector<vector<char>> mazeData;

public:
    MazeInfo(int maxSteps_, int rows_, int cols_);
    /*need to select return type*/ parse_maze(ifstream input_file); /*why do we need this?or atleast why here?*/
};
