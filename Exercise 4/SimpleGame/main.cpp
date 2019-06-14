#include "Match.h"
#include "GameManager.h"


int main() {
    using MyMatch = Match<GameManager, GameData, Player>;
    GameManager g;
    MyMatch match{g};
    match.addPlayer([](int init){return Player{init};});
    GameData gd;
    match.addGame(gd);
    MyMatch::Report report = match.runMatch();
    // TODO: print report to screen
}
