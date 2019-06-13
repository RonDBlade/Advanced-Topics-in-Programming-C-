#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <filesystem>
#include <sys/stat.h>
#include "maze.h"

using std::cout;
using std::string;
using std::endl;
using std::stoi;
using std::strtok;
using std::ifstream;


struct ParsedInput{
    string maze_path;
    string algorithm_path;
    string output_path;
    int num_of_threads;

public:
    ParsedInput(int num_of_arguments, char* arguments[]);
};

vector<string> findAllFilesByExtension(string path, string extension);
Maze addMaze(string mazePath);

#endif // PARSER_H_INCLUDED
