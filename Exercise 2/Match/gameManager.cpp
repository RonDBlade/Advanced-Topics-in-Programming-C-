#include "gameManager.h"

gameInstance::gameInstance(std::shared_ptr<Maze> gameMaze_, pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> algorithm_, string outputFolder_): algorithm(algorithm_), playerPos(gameMaze_->getStart()), foundTreasure(false), outputFile(nullptr), stepsTaken(0){
    if (outputFolder_ != ""){
        string outputFileName = outputFolder_ + gameMaze_->getMazeName() + "_" + algorithm_.first() + ".output";
        std::filebuf fileBuffer;
        fileBuffer.open(outputFileName.c_str, std::ios_base::out);
        if (!fileBuffer.is_open()){
            cout << "Error opening output file " << outputFileName << endl;
            // In case of error opening the file (or we didn't received output folder) constructing it with null will cause a no-op each time we use it
        }
        else{
            ouputFile.rdbuf(&fileBuffer);
        }
    }
}

vector<gameInstance> runAlgorithmsOnMaze(std::shared_ptr<Maze> gameMaze, vector<pair<string, vector<std::function<std::unique_ptr<AbstractAlgorithm>()>>>> loadedAlgorithms, string outputFolder){
    vector<gameInstance> allGamesForMaze;
    int maxSteps = gameMaze->getMaxSteps(), currMoveNumber = 0;
    int numOfAlgorithms = 0;
    int numFinished = 0;
    AbstractAlgorithm::Move currPlayerMove;
    char requestedTile;
    for(auto it = loadedAlgorithms.begin(); it != loadedAlgorithms.end(); it++){
        gameInstance instance = gameInstance(gameMaze, *it, outputFolder);
        allGamesForMaze.push_back(instance);
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
            *player.stepsTaken = -1;
        }
    }
    return allGamesForMaze;
}
