#include "gameManager.h"

using std::pair;


int gameFlow(int num_of_arguments, char *arguments[]){
    Maze *gameMaze = parse_input(num_of_arguments, arguments);
    if (gameMaze == nullptr)
        return 1;
    Player player = Player(); // Do we need it or we should just use empty constructor
    pair<unsigned int, unsigned int> playerPos = gameMaze->getStart(), bookmarkPos;
    int maxSteps = gameMaze->getMaxSteps(), currMoveNumber = 0;
    Move currPlayerMove;
    char requestedTile;
    bool foundTreasure = false;
    while((currMoveNumber < maxSteps) && (!foundTreasure)){
        currPlayerMove = player.move();
        if (currPlayerMove == Move::BOOKMARK){
            bookmarkPos = playerPos;
        }
        else{
            switch(currPlayerMove){
            case Move::UP:
                playerPos.second = (playerPos.second + 1) % gameMaze->getRows();
                break;
            case Move::DOWN:
                playerPos.second = (playerPos.second - 1) % gameMaze->getRows();
                break;
            case Move::RIGHT:
                playerPos.first = (playerPos.first + 1) % gameMaze->getCols();
                break;
            case Move::LEFT:
                playerPos.first = (playerPos.first - 1) % gameMaze->getCols();
                break;
            case Move::BOOKMARK:
                bookmarkPos = playerPos;
                //continue;  ??? want to start loop over
                break;
            }
            requestedTile = gameMaze->getChar(playerPos);
            switch(requestedTile){
            case ' ':
                if (playerPos == bookmarkPos){
                    player.hitBookmark();
                }
                break;
            case '#':
                player.hitWall();
                break;
            case '$':
                //FIX
                break;
            }

        }
    }
    return 1;
}
