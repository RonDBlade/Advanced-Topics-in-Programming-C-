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

bool is_header_valid(ifstream& input_file, int* maze_data){
    string line;
    char *token, *cstr_line;
    int i;
    bool valid = true;
    getline(input_file, line); // First row is not relevant for parsing
    while (i < HEADER_LENGTH){
        getline(input_file, line);
        strcpy(cstr_line, line.c_str());
        token = strtok(cstr_line, delimiter);
        switch(i){
        case 0:
            if (strcmp(token, "MaxSteps")){
                // Print error
                valid = false;
            }
            break;
        case 1:
            if (strcmp(token, "Rows")){
                // Print error
                valid = false;
            }
            break;
        case 2:
            if (strcmp(token, "Cols")){
                // Print error
                valid = false;
            }
            break;
        }
        token = strtok(nullptr, delimiter);
        if (strcmp(token, "=")){//maybe change to strcmp if it yells that its a char since it is only 1 char long
            // Print error
            valid = false;
        }
        token = strtok(nullptr, delimiter);
        if (check_if_int(token)){
                maze_data[i] = stoi(token);
        }
        else{
            // Print error
            valid = false;
        }
        token = strtok(nullptr, delimiter);
        if (token != nullptr){
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
    if (!input_file.is_open()){
        // Add to errors
    }
    int maze_data[3] = {0};
    if (!is_header_valid(input_file, maze_data)){
        // Errors
    }
    if (file_exists(argv[2])){/*bad path==directories that describe this path don't exist i think(ron),need to add a check for that*/
        cout<<"Command line argument for output file: " << argv[2] << "points to a bad path or to a file that already exists" << endl;

    }
    parse_maze();
}
