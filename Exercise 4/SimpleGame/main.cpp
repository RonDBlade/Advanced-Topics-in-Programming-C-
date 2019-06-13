#include "Match.h"


int main(int argc, char *argv[]) {
    using MyMatch = Match<GameManager, GameData, Player>;
    GameManager g;
    MyMatch match{g};
    match.addPlayer([](int init){return Player{init};});
    GameData gd;
    match.addGame(gd);
    MyMatch::Report report = match.runMatch();
    // TODO: print report to screen
}
