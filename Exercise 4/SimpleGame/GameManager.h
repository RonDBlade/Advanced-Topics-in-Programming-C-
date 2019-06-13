#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "GameData.h"

class GameManager {
public:
    GameData::InitData getInitData(GameData& game, GameData::GameInstanceData& gameInstance) {
        return GameData::get_init_Data();
    }
    GameData::MoveFeedback processMove(GameData& game, GameData::GameInstanceData& gameInstance, GameData::Move move) {
        return game.processMove(gameInstance, move);
    }
    bool endGame(GameData& game, GameData::GameInstanceData& gameInstance) {
        return gameInstance.IsGameDone();
    }
    int score(GameData& game, GameData::GameInstanceData& gameInstance) {
        return 0;
    }
};

#endif // GAMEMANAGER_H_INCLUDED
