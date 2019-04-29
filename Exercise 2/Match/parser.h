#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/stat.h>
#include <filesystem>
#include "matchManager.h"

using std::cout;
using std::string;
using std::endl;
using std::stoi;
using std::strtok;
using std::ifstream;
using std::filesystem;

Maze* parse_input(int num_of_arguments, char *arguments[]);

#endif // PARSER_H_INCLUDED
