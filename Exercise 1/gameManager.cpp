#include "gameManager.h"

using std::pair;

void gameFlow(Maze& gameMaze){
    Player player = Player(); // Do we need it or we should just use empty constructor
    pair<unsigned int, unsigned int> startPos = gameMaze.getStart();
    int maxSteps = gameMaze.getMaxSteps(), currMoveNumber = 0;
    Move currPlayerMove;
    while(currMoveNumber < maxSteps){
        currPlayerMove = player.move();

    }
}
