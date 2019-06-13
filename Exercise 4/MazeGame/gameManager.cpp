#include "gameManager.h"

gameInstance::gameInstance(){
}

gameInstance::gameInstance(Maze &gameMaze_, pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> &algorithm_): algorithmGenerator(algorithm_.second), gameMaze(gameMaze_), algoName(algorithm_.first), playerPos(gameMaze_.getStart()), stepsTaken(0), bookmarkCount(0){
    bookmarkPositions.clear();
    gameOutput.clear();
}

std::unique_ptr<AbstractAlgorithm> gameInstance::generateAlgorithm(){
    return algorithmGenerator();
}

string gameInstance::getAlgorithmName() const{
    return algoName;
}

string gameInstance::getMazeName()const{
    return gameMaze.getMazeName();
}

int gameInstance::getPlayerRow() const{
    return playerPos.second;
}

int gameInstance::getPlayerCol() const{
    return playerPos.first;
}

vector<string> gameInstance::getGameOutput() const{
    return gameOutput;
}

int gameInstance::getStepsTaken() const{
    return stepsTaken;
}

AbstractAlgorithm::Move gameInstance::moveAlgorithm(std::unique_ptr<AbstractAlgorithm> &algorithmPtr){
    return algorithmPtr->move();
}

void gameInstance::hitAlgorithmWall(std::unique_ptr<AbstractAlgorithm> &algorithmPtr){
    algorithmPtr->hitWall();
}

void gameInstance::hitAlgorithmBookmark(std::unique_ptr<AbstractAlgorithm> &algorithmPtr, int seq){
    algorithmPtr->hitBookmark(seq);
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


void gameInstance::addToGameOutput(string newLine){
    gameOutput.push_back(newLine);
}

void gameInstance::runGame(){
    int maxSteps = gameMaze.getMaxSteps(), currMoveNumber = 0;
    int rows = gameMaze.getRows(), cols = gameMaze.getCols();
    AbstractAlgorithm::Move currPlayerMove;
    char requestedTile;
    std::unique_ptr<AbstractAlgorithm> algorithmPtr = generateAlgorithm();
    while(currMoveNumber < maxSteps){
        currMoveNumber++;
        currPlayerMove = moveAlgorithm(algorithmPtr);
        switch(currPlayerMove){
        case AbstractAlgorithm::Move::UP:
            setPlayerRow(positiveModulo(getPlayerRow() - 1, rows));
            addToGameOutput("U");
            break;
        case AbstractAlgorithm::Move::DOWN:
            setPlayerRow(positiveModulo(getPlayerRow() + 1, rows));
            addToGameOutput("D");
            break;
        case AbstractAlgorithm::Move::RIGHT:
            setPlayerCol(positiveModulo(getPlayerCol() + 1, cols));
            addToGameOutput("R");
            break;
        case AbstractAlgorithm::Move::LEFT:
            setPlayerCol(positiveModulo(getPlayerCol() - 1, cols));
            addToGameOutput("L");
            break;
        case AbstractAlgorithm::Move::BOOKMARK:
            addBookmarkPosition();
            addToGameOutput("B");
            continue; // Next loop iteration, don't check current character
        }
        requestedTile = gameMaze.getChar(playerPos);
        switch(requestedTile){
        case '@':
        case ' ':
            for(auto& bookmark : bookmarkPositions){
                if (bookmark.second == playerPos){
                    hitAlgorithmBookmark(algorithmPtr, bookmark.first);
                    bookmarkPositions.erase(std::remove(bookmarkPositions.begin(), bookmarkPositions.end(), bookmark), bookmarkPositions.end());
                    break;
                }
            }
            break;
        case '#':
            hitAlgorithmWall(algorithmPtr);
            switch(currPlayerMove){// Reverse player move
            case AbstractAlgorithm::Move::UP:
                setPlayerRow(positiveModulo(getPlayerRow() + 1, rows));
                break;
            case AbstractAlgorithm::Move::DOWN:
                setPlayerRow(positiveModulo(getPlayerRow() - 1, rows));
                break;
            case AbstractAlgorithm::Move::RIGHT:
                setPlayerCol(positiveModulo(getPlayerCol() - 1, cols));
                break;
            case AbstractAlgorithm::Move::LEFT:
                setPlayerCol(positiveModulo(getPlayerCol() + 1, cols));
                break;
            case AbstractAlgorithm::Move::BOOKMARK:
                break; // Won't get here, only to avoid compilation errors
            }
            break;
        case '$':
            stepsTaken = currMoveNumber;
            addToGameOutput("!");
            return;
        }
    }
    addToGameOutput("X");
    stepsTaken = -1;
}

