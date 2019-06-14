#include "GameData.h"

GameData::instanceData::instanceData(int _chosenNumber): chosenNumber(_chosenNumber), moveCount(0), gameDone(false){}

GameData::GameData(Id _gameID, int _maxRange = MAX_NUM): gameID(_gameID), maxRange(_maxRange) {}

GameData::GameInstanceData GameData::newGameInstance(){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, maxRange);
    int chosenNumber = uni(rng);
    return instanceData(chosenNumber);
}

GameData::MoveFeedback GameData::processMove(GameData::GameInstanceData& gameInstance, GameData::Move move){
    moveCount++;
    if(gameInstance == move){
        gameDone = true;
        return 0;
    }
    if(gameInstance > move){
        return 1;
    }
    return -1;
    }

GameData::InitData GameData::GetInitData(){
    return maxRange;
}

bool GameData::IsGameDone(){
    return gameDone;
}
