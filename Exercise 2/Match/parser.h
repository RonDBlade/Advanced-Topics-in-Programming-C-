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


struct FilePaths{
    string maze_path;
    string algorithm_path;
    string output_path;

public:
    FilePaths(int num_of_arguments, char* arguments[]);
};

vector<string> findAllFilesByExtension(string path, string extension);
std::shared_ptr<Maze> addMaze(string mazePath);

#endif // PARSER_H_INCLUDED
