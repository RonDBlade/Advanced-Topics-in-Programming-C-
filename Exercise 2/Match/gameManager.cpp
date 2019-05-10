#include "gameManager.h"

int gameFlow(int num_of_arguments, char *arguments[]){
    Maze *gameMaze = parse_input(num_of_arguments, arguments);
    if (gameMaze == nullptr)// Input file isn't valid
        return 1;
    AbstractAlgorithm algorithm = AbstractAlgorithm();
    pair<int, int> playerPos = gameMaze->getStart(), bookmarkPos;
    int maxSteps = gameMaze->getMaxSteps(), currMoveNumber = 0;
    AbstractAlgorithm::Move currPlayerMove;
    char requestedTile;
    bool foundTreasure = false;
    std::ofstream output_file(arguments[2]);
    if (!output_file.is_open()){
        cout << "Error opening output file" << endl;
        return 1;
    }
    while((currMoveNumber < maxSteps) && (!foundTreasure)){
        currPlayerMove = algorithm.move();
        currMoveNumber++;
        if (currPlayerMove == AbstractAlgorithm::Move::BOOKMARK){
            bookmarkPos = playerPos;
        }
        else{
            switch(currPlayerMove){
            case AbstractAlgorithm::Move::UP:
                playerPos.second = positiveModulo(playerPos.second - 1, gameMaze->getRows());
                output_file << "U" << endl;
                break;
            case AbstractAlgorithm::Move::DOWN:
                playerPos.second = positiveModulo(playerPos.second + 1, gameMaze->getRows());
                output_file << "D" << endl;
                break;
            case AbstractAlgorithm::Move::RIGHT:
                playerPos.first = positiveModulo(playerPos.first + 1, gameMaze->getCols());
                output_file << "R" << endl;
                break;
            case AbstractAlgorithm::Move::LEFT:
                playerPos.first = positiveModulo(playerPos.first - 1, gameMaze->getCols());
                output_file << "L" << endl;
                break;
            case AbstractAlgorithm::Move::BOOKMARK:
                bookmarkPos = playerPos;
                output_file << "B" << endl;
                continue; // Next loop iteration, don't check current character
            }
            requestedTile = gameMaze->getChar(playerPos);
            switch(requestedTile){
            case ' ':
                if (playerPos == bookmarkPos){
                    player.hitBookmark();
                    bookmarkPos = {-1,-1}; // Reset bookmark position
                }
                break;
            case '#':
                player.hitWall();
                switch(currPlayerMove){// Reverse player move
                case AbstractAlgorithm::Move::UP:
                    playerPos.second = positiveModulo(playerPos.second + 1, gameMaze->getRows());
                    break;
                case AbstractAlgorithm::Move::DOWN:
                    playerPos.second = positiveModulo(playerPos.second - 1, gameMaze->getRows());
                    break;
                case AbstractAlgorithm::Move::RIGHT:
                    playerPos.first = positiveModulo(playerPos.first - 1, gameMaze->getCols());
                    break;
                case AbstractAlgorithm::Move::LEFT:
                    playerPos.first = positiveModulo(playerPos.first + 1, gameMaze->getCols());
                    break;
                case AbstractAlgorithm::Move::BOOKMARK:
                    break; // Won't get here, only to avoid compilation errors
                }
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
