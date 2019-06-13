#include "GameData.h"

GameData::GameData(): gamedone(false), moveCount(0){};

GameInstanceData GameData::newGameInstance(){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(MIN_NUM, MAX_NUM);
    return chosenNumber = uni(rng);
    }

MoveFeedback GameData::processMove(GameData::GameInstanceData& gameInstance, GameData::Move move){
    moveCount++;
    if(gameInstance == move){
        GameDone = true;
        return 0;
    }
    if(gameInstance > move){
        return 1;
    }
    return -1;
    }

InitData GameData::GetInitData(){
    return MAX_NUM;
}

bool GameData::IsGameDone(){
    return GameDone;
}
