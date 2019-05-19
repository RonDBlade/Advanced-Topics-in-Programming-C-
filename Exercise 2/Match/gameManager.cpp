#include "gameManager.h"

gameInstance::gameInstance(std::shared_ptr<Maze> gameMaze_, pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>> &algorithm_): algorithmGenerator(algorithm_.second), algoName(algorithm_.first), playerPos(gameMaze_->getStart()), foundTreasure(false), stepsTaken(0), bookmarkCount(0){}

std::unique_ptr<AbstractAlgorithm> gameInstance::generateAlgorithm(){
    return algorithmGenerator();
}

string gameInstance::getAlgorithmName(){
    return algoName;
}

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

void gameInstance::setPlayerPos(pair<int, int> position){
    playerPos = position;
}

void gameInstance::setPlayerRow(int row){
    cout << "Trying to set row to " << row << endl;
    playerPos.second = row;
}

void gameInstance::setPlayerCol(int col){
    playerPos.first = col;
}

void gameInstance::addBookmarkPosition(){
    cout << "Adding bookmark" << endl;
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

void runSingleAlgorithm(std::shared_ptr<Maze> gameMaze, gameInstance &player){
    int maxSteps = gameMaze->getMaxSteps(), currMoveNumber = 0;
    AbstractAlgorithm::Move currPlayerMove;
    char requestedTile;
    std::unique_ptr<AbstractAlgorithm> algorithmPtr = player.generateAlgorithm();
    while(currMoveNumber < maxSteps){
        currMoveNumber++;
        currPlayerMove = player.moveAlgorithm(algorithmPtr);
        cout << "Player details: " << " move: " << currPlayerMove << " position: " << player.getPlayerPos().first << " , " <<  player.getPlayerPos().second << endl;
        switch(currPlayerMove){
        case AbstractAlgorithm::Move::UP:
            player.setPlayerRow(positiveModulo(player.getPlayerRow() - 1, gameMaze->getRows()));
            player.addToGameOutput("U");
            break;
        case AbstractAlgorithm::Move::DOWN:
            player.setPlayerRow(positiveModulo(player.getPlayerRow() + 1, gameMaze->getRows()));
            player.addToGameOutput("D");
            break;
        case AbstractAlgorithm::Move::RIGHT:
            player.setPlayerCol(positiveModulo(player.getPlayerCol() + 1, gameMaze->getCols()));
            player.addToGameOutput("R");
            break;
        case AbstractAlgorithm::Move::LEFT:
            player.setPlayerCol(positiveModulo(player.getPlayerCol() - 1, gameMaze->getCols()));
            player.addToGameOutput("L");
            break;
        case AbstractAlgorithm::Move::BOOKMARK:
            player.addBookmarkPosition();
            player.addToGameOutput("B");
            continue; // Next loop iteration, don't check current character
        }
        requestedTile = gameMaze->getChar(player.getPlayerPos());
        switch(requestedTile){
        case '@':
        case ' ':
            for(auto bookmark = player.getBookmarkPositions().begin(); bookmark != player.getBookmarkPositions().end(); bookmark++){
                if (bookmark->second == player.getPlayerPos()){
                    std::ptrdiff_t index = std::distance(player.getBookmarkPositions().begin(), bookmark);
                    player.hitAlgorithmBookmark(algorithmPtr, bookmark->first, index);
                    break;
                }
            }
            break;
        case '#':
            player.hitAlgorithmWall(algorithmPtr);
            switch(currPlayerMove){// Reverse player move
            case AbstractAlgorithm::Move::UP:
                player.setPlayerRow(positiveModulo(player.getPlayerRow() + 1, gameMaze->getRows()));
                break;
            case AbstractAlgorithm::Move::DOWN:
                player.setPlayerRow(positiveModulo(player.getPlayerRow() - 1, gameMaze->getRows()));
                break;
            case AbstractAlgorithm::Move::RIGHT:
                player.setPlayerCol(positiveModulo(player.getPlayerCol() - 1, gameMaze->getCols()));
                break;
            case AbstractAlgorithm::Move::LEFT:
                player.setPlayerCol(positiveModulo(player.getPlayerCol() + 1, gameMaze->getCols()));
                break;
            case AbstractAlgorithm::Move::BOOKMARK:
                break; // Won't get here, only to avoid compilation errors
            }
            break;
        case '$':
            player.setStepsTaken(currMoveNumber);
            player.addToGameOutput("!");
            return;
        }
    }
    player.addToGameOutput("X");
    player.setStepsTaken(-1);
}

vector<gameInstance> runAlgorithmsOnMaze(std::shared_ptr<Maze> gameMaze, vector<pair<string, std::function<std::unique_ptr<AbstractAlgorithm>()>>> &loadedAlgorithms){
    vector<gameInstance> allGamesForMaze;
    for(auto it = loadedAlgorithms.begin(); it != loadedAlgorithms.end(); it++){
        allGamesForMaze.emplace_back(gameInstance(gameMaze, *it));
    }
    for (auto player = allGamesForMaze.begin(); player != allGamesForMaze.end(); player++){
        cout << "Running game " << player->getAlgorithmName() << endl;
        runSingleAlgorithm(gameMaze, *player);
    }
    return allGamesForMaze;
}
