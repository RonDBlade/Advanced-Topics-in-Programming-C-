#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


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

bool is_header_valid(ifstream input_file, int* maze_data){
    string line, word;
    int i;
    bool valid = true;
    getline(input_file, line); // First row is not relevant for parsing
    while (i < HEADER_LENGTH){
        getline(input_file, line);
        getline(line, word, delimiter);
        switch(i){
        case 0:
            if (word != "MaxSteps"){
                // Print error
                valid = false;
            }
            break;
        case 1:
            if (word != "Rows"){
                // Print error
                valid = false;
            }
            break;
        case 2:
            if (word != "Cols"){
                // Print error
                valid = false;
            }
            break;
        }
        getline(line, word, delimiter);
        if (word != "="){
            // Print error
            valid = false;
        }
        getline(line, word, delimiter);
        if (check_if_int(word)){
                maze_data[i] = stoi(word);
        }
        else{
            // Print error
            valid = false;
        }
        getline(line, word, delimiter);
        if (word != nullptr){
            // Print error - more tokens than needed
            valid = false;
        }
    }
    return valid;
}

bool file_exists(const string& file_path){
    ifstream file(file_path.c_str());
    return file.good();
}

int main(int argc, char* argv[]){
    if(argc==1){
        cout<<"Missing maze file argument in command line"<<endl;
        return 0;
    }
    ifstream input_file (argv[1]);
    if !(input_file.is_open()){
        // Add to errors
    }
    if !(is_header_valid(input_file)){
        // Errors
    }
    if (file_exists(argv[2])){/*bad path==directories that describe this path don't exist i think(ron),need to add a check for that*/
        cout<<"Command line argument for output file: " << argv[2] << "points to a bad path or to a file that already exists" << endl;

    }
    parse_maze();
}
