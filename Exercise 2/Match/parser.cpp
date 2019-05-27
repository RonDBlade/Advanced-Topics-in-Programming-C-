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

Maze addMaze(string mazePath){
    bool input_correct;
    Maze dummyMaze; // Initialized as "Dummy" with empty constructor
    ifstream input_file(mazePath);
    if (!input_file.is_open()){
        cout << "File: " << mazePath << "doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
        return dummyMaze;
    }
    int maze_data[3] = {0};
    if (!is_header_valid(input_file, maze_data)){
        input_file.close();
        return dummyMaze;
    }
    string fileName = std::filesystem::path(mazePath).stem();
    Maze gameMaze = Maze(fileName, maze_data[0], maze_data[1], maze_data[2]);
    input_correct = gameMaze.parse_maze(input_file);
    input_file.close();
    if (input_correct){
        return gameMaze;
    }
    return dummyMaze;
}

string parseStringFromVector(vector<string> arguments, string search_string){
    std::error_code err;
    auto place_in_vector = std::find(std::begin(arguments), std::end(arguments), search_string);
    string path = std::filesystem::current_path();
    if (place_in_vector != std::end(arguments)){
        if (std::next(place_in_vector) != std::end(arguments)){
            path = *(std::next(place_in_vector));
        }
    }
    if ((search_string == "-output") && (place_in_vector == std::end(arguments))){
        return "";
    }
    if (search_string == "-num_threads"){
        if (place_in_vector == std::end(arguments)){
            return "0";
        }
        return path;
    }
    // Return the path found in the arguments or the default path of current working directory
    return (std::filesystem::is_directory(path, err)) ? path : std::filesystem::current_path().string();
}


ParsedInput::ParsedInput(int num_of_arguments, char* arguments[]): maze_path(std::filesystem::current_path().string()), algorithm_path(std::filesystem::current_path().string()){
    string argument;
    vector<string> argumentsStrings;
    string threadsAsStrings;
    for (int i = 1; i < num_of_arguments; i++){
        argument = string(arguments[i]);
        argumentsStrings.push_back(argument);
    }
    maze_path = parseStringFromVector(argumentsStrings, "-maze_path");
    algorithm_path = parseStringFromVector(argumentsStrings, "-algorithm_path");
    output_path = parseStringFromVector(argumentsStrings, "-output");
    threadsAsStrings = parseStringFromVector(argumentsStrings, "-num_threads");
    cout << "maze: " << maze_path << " algorithm: " << algorithm_path << " output: " << output_path << " threads: " << threadsAsStrings << endl;
    try{
        // Reducing 1 since main thread runs also
        num_of_threads = stoi(threadsAsStrings) - 1;
    }
    catch(const std::invalid_argument& e){
        cout << "Error parsing number of threads, not running any additional threads." << endl;
        num_of_threads = 0;
    }
}


vector<string> findAllFilesByExtension(string path, string extension){
    vector<string> filesPaths;
    for (auto& p: std::filesystem::directory_iterator(path)){
        if (p.path().extension() == extension){
            filesPaths.push_back(p.path());
        }
    }
    return filesPaths;
}
