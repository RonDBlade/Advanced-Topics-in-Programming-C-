#include "player.h"


#define STARTING_MAP_SIZE 5 /*why?*/

using std::vector;
using std::pair;

Player::Player(): current_position(0, 0), bookmark_position(0, 0){
    player_map.resize(STARTING_MAP_SIZE);
    for(int i = 0; i < STARTING_MAP_SIZE; i++){
        player_map[i].resize(STARTING_MAP_SIZE);
    }
}
pair<int, int> Player::player_pos()const{
    return current_position;
}

Move Player::move(){
    return Move::UP; // TODO: Implement
}
