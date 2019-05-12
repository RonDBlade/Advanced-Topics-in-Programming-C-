#include "gameManager.h"

gameInstance::gameInstance(std::shared_ptr<Maze> gameMaze_, pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> algorithm_): algorithm(algorithm_), playerPos(gameMaze_->getStart()), foundTreasure(false), stepsTaken(0), bookmarkCount(0){}

pair<int, int> gameInstance::getPlayerPos(){
    return playerPos;
}

int gameInstance::getPlayerRow(){
    return playerPos.second;
}

int gameInstance::getPlayerCol(){
    return playerPos.first;
}

vector<pair<int, pair<int, int>>> gameInstance::getBookmarkPositions(){
    return bookmarkPositions;
}

bool gameInstance::getFoundTreasure(){
    return foundTreasure;
}

vector<string> gameInstance::getGameOutput(){
    return gameOutput;
}

int gameInstance::getStepsTaken(){
    return stepsTaken;
}

AbstractAlgorithm::Move gameInstance::moveAlgorithm(){
    return algorithm.second()->move();
}

void gameInstance::hitAlgorithmWall(){
    algorithm.second()->hitWall();
}

void gameInstance::hitAlgorithmBookmark(int seq, int index){
    algorithm.second()->hitBookmark(seq);
    bookmarkPositions.erase(bookmarkPositions.begin() + index);
}

void gameInstance::setPlayerPos(pair<int, int> position){
    playerPos = position;
}

void gameInstance::setPlayerRow(int row){
    playerPos.second = row;
}

void gameInstance::setPlayerCol(int col){
    playerPos.first = col;
}

void gameInstance::addBookmarkPosition(){
    bookmarkPositions.push_back(std::make_pair(++bookmarkCount, playerPos));
}

void gameInstance::setFoundTreasure(bool treasureStatus){
    foundTreasure = treasureStatus;
}

void gameInstance::addToGameOutput(string newLine){
    gameOutput.push_back(newLine);
}

void gameInstance::setStepsTaken(int steps){
    stepsTaken = steps;
}

vector<gameInstance> runAlgorithmsOnMaze(std::shared_ptr<Maze> gameMaze, vector<pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> loadedAlgorithms){
    vector<gameInstance> allGamesForMaze;
    int maxSteps = gameMaze->getMaxSteps(), currMoveNumber = 0;
    int numOfAlgorithms = 0;
    int numFinished = 0;
    AbstractAlgorithm::Move currPlayerMove;
    char requestedTile;
    for(auto it = loadedAlgorithms.begin(); it != loadedAlgorithms.end(); it++){
        gameInstance instance = gameInstance(gameMaze, *it);
        allGamesForMaze.push_back(instance);
        numOfAlgorithms++;
    }
    while((currMoveNumber < maxSteps) && (numFinished < numOfAlgorithms)){
        currMoveNumber++;
        for(auto player = allGamesForMaze.begin(); player != allGamesForMaze.end(); player++){
            if(!player->getFoundTreasure()){
                currPlayerMove = player->moveAlgorithm();
                switch(currPlayerMove){
                case AbstractAlgorithm::Move::UP:
                    player->setPlayerRow(positiveModulo(player->getPlayerRow() - 1, gameMaze->getRows()));
                    player->addToGameOutput("U");
                    break;
                case AbstractAlgorithm::Move::DOWN:
                    player->setPlayerRow(positiveModulo(player->getPlayerRow() + 1, gameMaze->getRows()));
                    player->addToGameOutput("D");
                    break;
                case AbstractAlgorithm::Move::RIGHT:
                    player->setPlayerCol(positiveModulo(player->getPlayerCol() + 1, gameMaze->getCols()));
                    player->addToGameOutput("R");
                    break;
                case AbstractAlgorithm::Move::LEFT:
                    player->setPlayerCol(positiveModulo(player->getPlayerCol() - 1, gameMaze->getCols()));
                    player->addToGameOutput("L");
                    break;
                case AbstractAlgorithm::Move::BOOKMARK:
                    player->addBookmarkPosition();
                    player->addToGameOutput("B");
                    continue; // Next loop iteration, don't check current character
                }
                requestedTile = gameMaze->getChar(player->getPlayerPos());
                switch(requestedTile){
                case ' ':
                    for(auto bookmark = player->getBookmarkPositions().begin(); bookmark != player->getBookmarkPositions().end(); bookmark++){
                        if (bookmark->second == player->getPlayerPos()){
                            std::ptrdiff_t index = std::distance(player->getBookmarkPositions().begin(), bookmark);
                            player->hitAlgorithmBookmark(bookmark->first, index);
                            break;
                        }
                    }
                    break;
                case '#':
                    player->hitAlgorithmWall();
                    switch(currPlayerMove){// Reverse player move
                    case AbstractAlgorithm::Move::UP:
                        player->setPlayerRow(positiveModulo(player->getPlayerRow() + 1, gameMaze->getRows()));
                        break;
                    case AbstractAlgorithm::Move::DOWN:
                        player->setPlayerRow(positiveModulo(player->getPlayerRow() - 1, gameMaze->getRows()));
                        break;
                    case AbstractAlgorithm::Move::RIGHT:
                        player->setPlayerCol(positiveModulo(player->getPlayerCol() - 1, gameMaze->getCols()));
                        break;
                    case AbstractAlgorithm::Move::LEFT:
                        player->setPlayerCol(positiveModulo(player->getPlayerCol() + 1, gameMaze->getCols()));
                        break;
                    case AbstractAlgorithm::Move::BOOKMARK:
                        break; // Won't get here, only to avoid compilation errors
                    }
                    break;
                case '$':
                    player->setStepsTaken(currMoveNumber);
                    player->setFoundTreasure(true);
                    player->addToGameOutput("!");
                    break;
                }
            }
        }
    }
    for (auto player = allGamesForMaze.begin(); player != allGamesForMaze.end(); player++){
        if (player->getFoundTreasure()){
            player->addToGameOutput("X");
            player->setStepsTaken(-1);
        }
    }
    return allGamesForMaze;
}
