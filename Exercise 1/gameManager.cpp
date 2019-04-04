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
    std::ofstream output_file(arguments[2]);
    if (!output_file.is_open()){
        //Need to add Adam error for not opening file for writing
        return 1;
    }
    while((currMoveNumber < maxSteps) && (!foundTreasure)){
        currPlayerMove = player.move();
        if (currPlayerMove == Move::BOOKMARK){
            bookmarkPos = playerPos;
        }
        else{
            switch(currPlayerMove){
            case Move::UP:
                playerPos.second = (playerPos.second - 1) % gameMaze->getRows();
                output_file << "U" << endl;
                break;
            case Move::DOWN:
                playerPos.second = (playerPos.second + 1) % gameMaze->getRows();
                output_file << "D" << endl;
                break;
            case Move::RIGHT:
                playerPos.first = (playerPos.first + 1) % gameMaze->getCols();
                output_file << "R" << endl;
                break;
            case Move::LEFT:
                playerPos.first = (playerPos.first - 1) % gameMaze->getCols();
                output_file << "L" << endl;
                break;
            case Move::BOOKMARK:
                bookmarkPos = playerPos;
                output_file << "B" << endl;
                continue; // Next loop iteration, don't check current character
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
                cout << "Succeeded in " << currMoveNumber << " steps" << endl;
                foundTreasure = true;
                output_file << "!";
                break;
            }
        }
    }
    if (!foundTreasure){
        cout << "Failed to solve maze in " << maxSteps << " steps" << endl;
        output_file << "X";
    }
    return 0;
}
