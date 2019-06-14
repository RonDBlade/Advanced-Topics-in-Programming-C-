#ifndef GAMEDATA_H_INCLUDED
#define GAMEDATA_H_INCLUDED

#include <random>

#define MAX_NUM 100

class GameData{
    struct instanceData{
        int chosenNumber;
        int moveCount;
        bool gameDone;

        instanceData(int _chosenNumber);
    };

public:
    using Id = std::string;
    using InitData = int;
    using GameInstanceData = GameData::instanceData;
    using Move = int;
    using MoveFeedback = int;

    GameData(Id _gameID, int _maxRange);
    Id id() const { return gameID; }
    GameInstanceData newGameInstance();
    MoveFeedback processMove(GameData::GameInstanceData& gameInstance, GameData::Move move);
    InitData GetInitData();
    bool IsGameDone();

private:
    Id gameID;
    InitData maxRange;
    GameInstanceData gameInstanceData;
};

#endif // GAMEDATA_H_INCLUDED
