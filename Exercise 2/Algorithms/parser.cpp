#include "parser.h"


bool does_header_contains_word(int line_number, string line, string word, bool* header_valid){
    const std::regex header_pattern("\\s*\\b" + word + "\\b\\s*=\\s*[0-9]+\\s*");
    if (!std::regex_match(line, header_pattern)){
        if (*header_valid){
            *header_valid = false;
            cout << "Bad maze file header:" << endl;
        }
        cout << "expected in line " << line_number << " - " << word << " = <num>" << endl;
        cout << "got: " << line << endl;
        return false;
    }
    return true;
}

int extract_number_from_header(string line){
    string number, temp;
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
    number = line.substr(line.find("=") + 1, string::npos);
    return stoi(number);
}

bool is_header_valid(ifstream& input_file, int* maze_data){
    string line;
    bool header_valid = true;
    getline(input_file, line); // First row is not relevant for parsing
    getline(input_file, line);
    if (does_header_contains_word(2, line, "MaxSteps", &header_valid)){
        maze_data[0] = extract_number_from_header(line);
    }
    getline(input_file, line);
    if (does_header_contains_word(3, line, "Rows", &header_valid)){
        maze_data[1] = extract_number_from_header(line);
    }
    getline(input_file, line);
    if (does_header_contains_word(4, line, "Cols", &header_valid)){
        maze_data[2] = extract_number_from_header(line);
    }
    return header_valid;
}

bool file_exists(const string& file_path){
    struct stat buffer;
    return ((stat(file_path.c_str(), &buffer) == 0) && (buffer.st_mode & S_IFREG )); // Check the given output path doesn't exist as a file (and not folder)
}

Maze* parse_input(int num_of_arguments, char *arguments[]){
    bool input_correct = true, output_correct = true;
    if (num_of_arguments < 2){
        cout << "Missing maze file argument in command line" << endl;
        cout << "Missing output file argument in command line" << endl;
        return nullptr;
    }
    ifstream input_file(arguments[1]);
    if (!input_file.is_open()){
        cout << "Command line argument for maze: " << arguments[1] << "doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
        input_correct = false;
    }
    if (num_of_arguments < 3){
        cout << "Missing output file argument in command line" << endl;
        if (!input_correct){
            return nullptr;
        }
        output_correct = false;
    }
    if ((output_correct) && (file_exists(arguments[2]))){
        cout << "Command line argument for output file: " << arguments[2] << " points to a bad path or to a file that already exists" << endl;
        output_correct = false;
    }
    if (!input_correct){
        return nullptr;
    }
    int maze_data[3] = {0};
    if (!is_header_valid(input_file, maze_data)){
        input_file.close();
        return nullptr;
    }
    Maze *gameMaze = new Maze(maze_data[0], maze_data[1], maze_data[2]);
    input_correct = input_correct && gameMaze->parse_maze(input_file);
    input_file.close();
    if (input_correct && output_correct){
        return gameMaze;
    }
    return nullptr;
}
