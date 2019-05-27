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

pair<int, int> gameInstance::getPlayerPos() const{
    return playerPos;
}

int gameInstance::getPlayerRow() const{
    return playerPos.second;
}

int gameInstance::getPlayerCol() const{
    return playerPos.first;
}

vector<pair<int, pair<int, int>>> gameInstance::getBookmarkPositions() const{
    return bookmarkPositions;
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

void gameInstance::hitAlgorithmBookmark(std::unique_ptr<AbstractAlgorithm> &algorithmPtr, int seq, int index){
    algorithmPtr->hitBookmark(seq);
    bookmarkPositions.erase(bookmarkPositions.begin() + index);
}

void gameInstance::setPlayerPos(pair<int, int> &position){
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


void gameInstance::addToGameOutput(string newLine){
    gameOutput.push_back(newLine);
}

void gameInstance::setStepsTaken(int steps){
    stepsTaken = steps;
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
        requestedTile = gameMaze.getChar(getPlayerPos());
        switch(requestedTile){
        case '@':
        case ' ':
            for(auto bookmark = getBookmarkPositions().begin(); bookmark != getBookmarkPositions().end(); bookmark++){
                if (bookmark->second == getPlayerPos()){
                    int index = std::distance(getBookmarkPositions().begin(), bookmark);
                    hitAlgorithmBookmark(algorithmPtr, bookmark->first, index);
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
            setStepsTaken(currMoveNumber);
            addToGameOutput("!");
            return;
        }
    }
    addToGameOutput("X");
    setStepsTaken(-1);
}

