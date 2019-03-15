#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define delimiter " \t\r\n"
#define HEADER_LENGTH 3
#define TOKEN_LENGTH 2

using std::cout

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
    for (int i = 0; i < HEADER_LENGTH; i++){
        getline(input_file, line);
        token = strtok(line, delimiter);
        if (i == 0){
            if (token != "MaxSteps")
        }
        for (int j = 0; j < TOKEN_LENGTH; j++){

            token = strtok(NULL, delimiter);
        }
        if (check_if_int(token)){

        }
    }
}

int main(int argc, char* argv[]){
    ifstream input_file (argv[1])
    if !(input_file.is_open()){
        // Add to errors
    }
    if !(is_header_valid(input_file)){
        // Errors
    }
}
