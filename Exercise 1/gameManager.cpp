#include "gameManager.h"

int gameFlow(int num_of_arguments, char *arguments[]){
    Maze *gameMaze = parse_input(num_of_arguments, arguments);
    if (gameMaze == nullptr)// Input file isn't valid
        return 1;
    Player player = Player(); // Do we need it or we should just use empty constructor
    pair<int, int> playerPos = gameMaze->getStart(), bookmarkPos;
    int maxSteps = gameMaze->getMaxSteps(), currMoveNumber = 0;
    Move currPlayerMove;
    char requestedTile;
    bool foundTreasure = false;
    std::ofstream output_file(arguments[2]);
    if (!output_file.is_open()){
        cout << "Error opening output file" << endl;
        return 1;
    }
    while((currMoveNumber < maxSteps) && (!foundTreasure)){
        currPlayerMove = player.move();
        currMoveNumber++;
        if (currPlayerMove == Move::BOOKMARK){
            bookmarkPos = playerPos;
        }
        else{
            switch(currPlayerMove){
            case Move::UP:
                playerPos.second = positiveModulo(playerPos.second - 1, gameMaze->getRows());
                output_file << "U" << endl;
                break;
            case Move::DOWN:
                playerPos.second = positiveModulo(playerPos.second + 1, gameMaze->getRows());
                output_file << "D" << endl;
                break;
            case Move::RIGHT:
                playerPos.first = positiveModulo(playerPos.first + 1, gameMaze->getCols());
                output_file << "R" << endl;
                break;
            case Move::LEFT:
                playerPos.first = positiveModulo(playerPos.first - 1, gameMaze->getCols());
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
                switch(currPlayerMove){// Reverse player move
                case Move::UP:
                    playerPos.second = positiveModulo(playerPos.second + 1, gameMaze->getRows());
                    break;
                case Move::DOWN:
                    playerPos.second = positiveModulo(playerPos.second - 1, gameMaze->getRows());
                    break;
                case Move::RIGHT:
                    playerPos.first = positiveModulo(playerPos.first - 1, gameMaze->getCols());
                    break;
                case Move::LEFT:
                    playerPos.first = positiveModulo(playerPos.first + 1, gameMaze->getCols());
                    break;
                case Move::BOOKMARK:
                    break; // Won't get here, only to avoid compilation errors
                }
                break;
            case '$':
                cout << "Succeeded in " << currMoveNumber << " steps" << endl;
                foundTreasure = true;
                output_file << "!";
                break;
            }
            cout << playerPos.first << " !!! " << playerPos.second << endl;
            for (int i = 0; i < gameMaze->getRows(); i++){
                for (int j = 0; j < gameMaze->getCols(); j++){
                    if ((playerPos.first == j) && (playerPos.second == i)){
                        cout << "@";
                    }
                    else{
                        char temp = gameMaze->getChar(std::make_pair(j,i));
                        if (temp == '@'){
                            cout << " ";
                        }
                        else{
                            cout << temp;
                        }
                    }
                }
                cout << endl;
            }
        }
    }
    if (!foundTreasure){
        cout << "Failed to solve maze in " << maxSteps << " steps" << endl;
        output_file << "X";
    }
    return 0;
}
