#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "maze.h"

#define delimiter " \t\r"
#define HEADER_LENGTH 3
#define TOKEN_LENGTH 2

using std::cout;
using std::string;
using std::endl;
using std::stoi;
using std::strtok;
using std::ifstream;


bool check_if_int(char* token){
    int string_length = strlen(token);
    for (int i = 0; i < string_length; i++){
        if (isdigit(token[i]) == false){
            return false;
        }
    }
    return true;
}

bool does_header_contains_word(int line_number, string line, string word, bool* header_valid){
    const std::regex header_pattern("\\s*\\b" + word + "\\b\\s*=\\s*[0-9]+\\s*");
    if (!std::regex_match(line, header_pattern)){
        if (*header_valid){
            *header_valid = false;
            cout << "Bad maze file header:" << endl;
        }
        cout << "expected in line " << line_number << " - " << word << " = <num>" << endl;
        cout << "got: " << line;
        return false;
    }
    return true;
}

bool is_header_valid(ifstream& input_file, int* maze_data){
    string line, number, temp;
    bool header_valid = true;
    std::istringstream iss(line);
    getline(input_file, line); // First row is not relevant for parsing
    getline(input_file, line);
    if (does_header_contains_word(2, line, "MaxSteps", &header_valid)){
        iss >> temp >> temp >> number;
        maze_data[0] = stoi(number);
    }
    getline(input_file, line);
    if (does_header_contains_word(3, line, "Rows", &header_valid)){
        iss >> temp >> temp >> number;
        maze_data[1] = stoi(number);
    }
    getline(input_file, line);
    if (does_header_contains_word(4, line, "Cols", &header_valid)){
        iss >> temp >> temp >> number;
        maze_data[2] = stoi(number);
    }
    return header_valid;
}

bool file_exists(const string& file_path){
    ifstream file(file_path.c_str());
    return file.good();
}

int main(int argc, char* argv[]){
    bool is_valid_game;
    if(argc < 3){
        if (argc < 2){
            cout << "Missing maze file argument in command line" << endl;
            cout << "Missing output file argument in command line" << endl;
            return 1;
        }
        cout << "Missing output file argument in command line" << endl;
        is_valid_game = false;
    }
    ifstream input_file(argv[1]);
    if (!input_file.is_open()){
        cout << "Command line argument for maze: " << argv[1] << "doesn't lead to a maze file or leads to a file that cannot be opened";
        return 1;
    }
    int maze_data[3] = {0};
    if (!is_header_valid(input_file, maze_data)){
        // Errors
        is_valid_game = false;
    }
    Maze* gameMaze = new Maze(maze_data[0], maze_data[1], maze_data[2]);
    is_valid_game = is_valid_game && gameMaze.parse_maze(input_file);
    if (file_exists(argv[2])){/*bad path==directories that describe this path don't exist i think(ron),need to add a check for that*/
        cout << "Command line argument for output file: " << argv[2] << "points to a bad path or to a file that already exists" << endl;

    }

}
