#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/stat.h>
#include "maze.h"

using std::cout;
using std::string;
using std::endl;
using std::stoi;
using std::strtok;
using std::ifstream;
using std::filesystem;


struct FilePaths{
    string maze_path;
    string algorithm_path;
    string output_path;
};

FilePaths::FilePaths(int num_of_arguments, char* arguments[]): maze_path(std::filesystem::current_path()), algorithm_path(std::filesystem::current_path());
vector<string> findAllFilesByExtension(string path, string extension);
Maze* parse_input(int num_of_arguments, char *arguments[]);

#endif // PARSER_H_INCLUDED
