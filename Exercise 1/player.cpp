#include "player.h"
#include <vector>
#include <pair>

#define STARTING_MAP_SIZE 5 /*why?*/

using std::vector
using std::pair

Player::Player():{
    player_map.resize(STARTING_MAP_SIZE);
    for(int i = 0; i < STARTING_MAP_SIZE; i++){
        player_map[i].resize(STARTING_MAP_SIZE);
    }
    current_position.first = current_position.second = 0;
    bookmark_position.first = bookmark_position.second = 0;
    }
pair<int, int> Player::player_pos()const{
    return current_position;
}
