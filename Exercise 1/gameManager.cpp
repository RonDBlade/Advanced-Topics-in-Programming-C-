#include "gameManager.h"

using std::pair;

void gameFlow(Maze& gameMaze){
    Player player = Player(); // Do we need it or we should just use empty constructor
    pair<unsigned int, unsigned int> playerPos = gameMaze.getStart(), bookmarkPos;
    int maxSteps = gameMaze.getMaxSteps(), currMoveNumber = 0;
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
                playerPos.second = (playerPos.second + 1) % gameMaze.rows;
                break;
            case Move::DOWN:
                playerPos.second = (playerPos.second - 1) % gameMaze.rows;
                break;
            case Move::RIGHT:
                playerPos.first = (playerPos.first + 1) % gameMaze.cols;
                break;
            case Move::LEFT:
                playerPos.first = (playerPos.first - 1) % gameMaze.cols;
                break;
            }
            requestedTile = gameMaze.getChar(playerPos);
            switch(requestedTile){
            case ' ':

            }
        }
    }
}
