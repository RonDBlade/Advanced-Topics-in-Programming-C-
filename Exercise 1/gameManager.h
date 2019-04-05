#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "parser.h"
#include "maze.h"
#include "player.h"
#include <utility>
#include <fstream>
#include <iostream>

using std::pair;

int gameFlow(int num_of_arguments, char *arguments[]);

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

#endif // GAMEMANAGER_H_INCLUDED
