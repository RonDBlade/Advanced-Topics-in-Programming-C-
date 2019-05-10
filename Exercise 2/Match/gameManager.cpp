#include "gameManager.h"

gameInstance::gameInstance(shared_ptr<Maze> gameMaze_, pair<string, AbstractAlgorithm> algorithm_, string outputFolder_): algorithm(algorithm_), playerPos(gameMaze_->getStart()), foundTreasure(false), stepsTaken(0){
    if (outputFolder_ != nullptr){
        string outputFileName = outputFolder_ + gameMaze_->mazeName + "_" + algorithm_.first() + ".output";
        outputFile = (outputFileName);
        if (!outputFile.is_open()){
            cout << "Error opening output file " << outputFileName << endl;
            outputFile = nullptr;
        }
    }
    else{
        outputFile = nullptr;
    }
}

int runAlgorithmsOnMaze(shared_ptr<Maze> gameMaze, vector<pair<string, AbstractAlgorithm>> loadedAlgorithms, string outputFolder){
    vector<gameInstance> allGamesForMaze;
    int maxSteps = gameMaze->getMaxSteps(), currMoveNumber = 0;
    int numOfAlgorithms = 0;
    int numFinished = 0;
    AbstractAlgorithm::Move currPlayerMove;
    char requestedTile;
    for(auto it = loadedAlgorithms.begin(); it != loadedAlgorithms.end(); it++){
        allGamesForMaze.push(gameInstance(gameMaze, *it, outputFolder));
        numOfAlgorithms++;
    }
    while((currMoveNumber < maxSteps) && (numFinished < numOfAlgorithms)){
        currMoveNumber++;
        for(auto player = allGamesForMaze.begin(); player != allGamesForMaze.end(); player++){
            if(!*player.foundTreasure){
                currPlayerMove = *player.algorithm.move();
                switch(currPlayerMove){
                case AbstractAlgorithm::Move::UP:
                    *player.playerPos.second = positiveModulo(playerPos.second - 1, gameMaze->getRows());
                    *player.outputFile << "U" << endl;
                    break;
                case AbstractAlgorithm::Move::DOWN:
                    *player.playerPos.second = positiveModulo(playerPos.second + 1, gameMaze->getRows());
                    *player.outputFile << "D" << endl;
                    break;
                case AbstractAlgorithm::Move::RIGHT:
                    *player.playerPos.first = positiveModulo(playerPos.first + 1, gameMaze->getCols());
                    *player.outputFile << "R" << endl;
                    break;
                case AbstractAlgorithm::Move::LEFT:
                    *player.playerPos.first = positiveModulo(playerPos.first - 1, gameMaze->getCols());
                    *player.outputFile << "L" << endl;
                    break;
                case AbstractAlgorithm::Move::BOOKMARK:
                    *player.bookmarkPositions.push_back(playerPos);
                    *player.outputFile << "B" << endl;
                    continue; // Next loop iteration, don't check current character
                }
                requestedTile = gameMaze->getChar(*player.playerPos);
                switch(requestedTile){
                case ' ':
                    auto it = std::find(*player.bookmarkPositions.begin(), *player.bookmarkPositions.end(), *player.playerPos);
                    if (it != *player.bookmarkPositions.end()){
                        std::ptrdiff_t index = std::distance(*player.bookmarkPositions.begin(), it);
                        *player.algorithm.hitBookmark(index);
                        *player.bookmarkPositions.erase(*player.bookmarkPositions.begin() + index);
                    }
                    break;
                case '#':
                    *player.algorithm.hitWall();
                    switch(currPlayerMove){// Reverse player move
                    case AbstractAlgorithm::Move::UP:
                        *player.playerPos.second = positiveModulo(*player.playerPos.second + 1, gameMaze->getRows());
                        break;
                    case AbstractAlgorithm::Move::DOWN:
                        *player.playerPos.second = positiveModulo(*player.playerPos.second - 1, gameMaze->getRows());
                        break;
                    case AbstractAlgorithm::Move::RIGHT:
                        *player.playerPos.first = positiveModulo(*player.playerPos.first - 1, gameMaze->getCols());
                        break;
                    case AbstractAlgorithm::Move::LEFT:
                        *player.playerPos.first = positiveModulo(*player.playerPos.first + 1, gameMaze->getCols());
                        break;
                    case AbstractAlgorithm::Move::BOOKMARK:
                        break; // Won't get here, only to avoid compilation errors
                    }
                    break;
                case '$':
                    *player.stepsTaken = currMoveNumber;
                    *player.foundTreasure = true;
                    *player.outputFile << "!";
                    break;
                }
            }
        }
    }
    for (auto player = allGamesForMaze.begin(); player != allGamesForMaze.end(); player++){
        if (!*player.foundTreasure){
            *player.outputFile << "X";
        }
    }
    return 0;
}
