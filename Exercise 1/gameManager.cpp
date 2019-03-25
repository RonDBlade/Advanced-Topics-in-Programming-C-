//#include "maze.h"
//#include "player.h"
#include <utility>

using std::pair;


void gameFlow(const maze& gameMaze)const{
    Player player = Player();
    pair startPos = maze.getStart();
    int maxSteps, currMoveNumber = maze.getMaxSteps(), 0;

    while(currMoveNumber < maxSteps){
        player.move();
        player.direction
    }
}
