#include "parser.h"

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

Maze* parse_input(int num_of_arguments, char *arguments[]){
    bool is_valid_game;
    if(num_of_arguments < 3){
        if (num_of_arguments < 2){
            cout << "Missing maze file argument in command line" << endl;
            cout << "Missing output file argument in command line" << endl;
            return nullptr;
        }
        cout << "Missing output file argument in command line" << endl;
        is_valid_game = false;
    }
    ifstream input_file(arguments[1]);
    if (!input_file.is_open()){
        cout << "Command line argument for maze: " << arguments[1] << "doesn't lead to a maze file or leads to a file that cannot be opened";
        return nullptr;
    }
    if (file_exists(arguments[2])){/*bad path==directories that describe this path don't exist i think(ron),need to add a check for that*/
    cout << "Command line argument for output file: " << arguments[2] << "points to a bad path or to a file that already exists" << endl;
    is_valid_game = false;
    }
    int maze_data[3] = {0};
    if (!is_header_valid(input_file, maze_data)){
        // Errors
        is_valid_game = false;
    }
    Maze *gameMaze = new Maze(maze_data[0], maze_data[1], maze_data[2]);
    is_valid_game = is_valid_game && gameMaze->parse_maze(input_file);
    input_file.close();
    return gameMaze;
}
