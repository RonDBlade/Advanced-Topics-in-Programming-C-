#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "parser.h"
#include "maze.h"
#include "player.h"
#include <utility>

class GameManager{
    Maze gameMaze();
    Player gamePlayer();

public:
    GameManager();
};
int gameFlow(int num_of_arguments, char *arguments[]);

#endif // GAMEMANAGER_H_INCLUDED
