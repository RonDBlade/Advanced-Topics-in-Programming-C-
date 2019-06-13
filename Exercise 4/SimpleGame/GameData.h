#ifndef GAMEDATA_H_INCLUDED
#define GAMEDATA_H_INCLUDED

#include <random>

#define MIN_NUM 0
#define MAX_NUM 100

class GameData{
    bool gameDone;
    int moveCount;
    Id gameID;
    InitData numberRange;
    GameInstanceData chosenNumber;

public:
    using Id = std::string;
    using InitData = int;
    using GameInstanceData = int;
    using Move = int;
    using MoveFeedback = int;

    GameData();
    Id id() const {
        return gameID;
    }
    GameInstanceData newGameInstance();
    MoveFeedback processMove(GameData::GameInstanceData& gameInstance, GameData::Move move);
    InitData GetInitData();
    bool IsGameDone();
};

#endif // GAMEDATA_H_INCLUDED
