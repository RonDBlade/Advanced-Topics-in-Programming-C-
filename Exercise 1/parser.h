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

#define delimiter " \t\r"
#define HEADER_LENGTH 3
#define TOKEN_LENGTH 2

using std::cout;
using std::string;
using std::endl;
using std::stoi;
using std::strtok;
using std::ifstream;


Maze* parse_input(int num_of_arguments, char *arguments[]);

#endif // PARSER_H_INCLUDED
