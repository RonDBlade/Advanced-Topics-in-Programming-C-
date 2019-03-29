#include "player.h"


#define STARTING_MAP_SIZE 5 /*why?*/

using std::map;
using std::pair;

Player::Player(): current_position(0, 0), bookmark_position(0, 0){
    player_map[0][0]=' ';
}
pair<int, int> Player::player_pos()const{
    return current_position;
}

Move Player::chooseMove(){
    return Move::UP; // TODO: Implement
}
void Player::update_map(char to_put,Move where){
        if(where==Move::UP)
            player_map[current_position.first][current_position.second+1]=to_put;
        else if(where==Move::DOWN)
            player_map[current_position.first][current_position.second-1]=to_put;
        else if(where==Move::LEFT)
            player_map[current_position.first-1][current_position.second]=to_put;
        else if(where==Move::RIGHT)
            player_map[current_position.first+1][current_position.second]=to_put;
        //dont need to put anything if move was BOOKMARK
    }
