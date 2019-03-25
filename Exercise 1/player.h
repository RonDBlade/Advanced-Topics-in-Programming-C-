#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <vector>
#include <utility>

#define STARTING_MAP_SIZE 5 /*why?*/

using std::vector;
using std::pair;

enum class Move{LEFT, RIGHT, UP, DOWN, BOOKMARK};

class Player{
    vector<vector<int> > player_map; /*should change to map of maps.From my understanding of the implementation we start the player from position
    (0,0) in his perspective,and if we treat some positions as "-" positions(down from (0,0) is (0,-1)),we cant do that with vectors*/
    pair<int, int> current_position;
    pair<int, int> bookmark_position; /*should keep this as game manager data,since he doesnt remember where he put it*/

public:
    Player();
    pair<int, int> player_pos()const;
    Move move();
};

#endif // PLAYER_H_INCLUDED
