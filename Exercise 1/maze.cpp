#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


#define delimiter " \t\r\n"
#define HEADER_LENGTH 3
#define TOKEN_LENGTH 2

using std::cout
using std::string

bool check_if_int(char* token){
    for (int i = 0; i < token.length(); i++){
        if (isdigit(token[i]) == false){
            return false;
        }
    }
    return true;
}

bool is_header_valid(ifstream input_file, int* maze_data){
    string line;
    char* token;
    getline(input_file, line);
    while (i < HEADER_LENGTH){
        getline(input_file, line);
        token = strtok(line, delimiter);
        switch(i){
        case 0:
            if (token != "MaxSteps"){
                // Print error
            }
            break;
        case 1:
            if (token != "Rows"){
                // Print error
            }
            break;
        case 2:
            if (token != "Cols"){
                // Print error
            }
            break;
        }
        token = strtok(nullptr, delimiter);
        if (token != "="){
            // Print error
        }
        token = strtok(nullptr, delimiter);
        if (check_if_int(token)){
                maze_data[i] = stoi(token)
        }
        else{
            // Print error
        }
        if (token != nullptr){
            // Print error - more tokens than needed
        }
    }
}

bool file_exists(const string& file_path){
    ifstream file(file_path.c_str());
    return file.good();
}

int main(int argc, char* argv[]){
    ifstream input_file (argv[1])
    if !(input_file.is_open()){
        // Add to errors
    }
    if !(is_header_valid(input_file)){
        // Errors
    }
    if (file_exists(argv[2])){
        // Print errors
    }
    parse_maze();
}
