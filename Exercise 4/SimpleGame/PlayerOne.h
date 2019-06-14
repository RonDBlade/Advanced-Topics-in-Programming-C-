#ifndef PLAYERONE_H_INCLUDED
#define PLAYERONE_H_INCLUDED

#include <iostream>

class Player {
public:

    using Id = std::string;

    Player(GameData::InitData){}
    Id id() const { return Id{}; }
    GameData::Move move() { return GameData::Move{}; }
    void moveFeedback(GameData::MoveFeedback feedback) {std::cout << feedback;}
};


#endif // PLAYERONE_H_INCLUDED
