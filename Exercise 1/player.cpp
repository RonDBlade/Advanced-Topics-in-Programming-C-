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

Move Player::chooseMove(){//for now,SIMPLE IMPLEMENTATION
    bool checkLoc=Player::isKnown(current_position.first,current_position.second+1);//checks if the player discovered whats above him already
    if(checkLoc)
        return Move::UP;
    checkLoc=Player::isKnown(current_position.first,current_position.second-1); //same for down
    if(checkLoc)
        return Move::DOWN;
    checkLoc=Player::isKnown(current_position.first-1,current_position.second); //same for left
    if(checkLoc)
        return Move::LEFT;
    checkLoc=Player::isKnown(current_position.first+1,current_position.second); //same for right
    if(checkLoc)
        return Move::RIGHT;
    //if we got here,we already know ALL the locations which surround the player.Time to find which are a wall and which arent.
    checkLoc=Player::isWall(current_position.first,current_position.second+1);//checks if the position above the player is a wall
    if(!checkLoc)
        return Move::UP;
    checkLoc=Player::isWall(current_position.first,current_position.second-1);//same for down
    if(!checkLoc)
        return Move::DOWN;
    checkLoc=Player::isWall(current_position.first-1,current_position.second);//same for left
    if(!checkLoc)
        return Move::LEFT;
    checkLoc=Player::isWall(current_position.first+1,current_position.second);//same for right
    if(!checkLoc)
        return Move::RIGHT;
    return Move::BOOKMARK;//if everything is a wall he is fucked lmaoooooooooooooooooooooo
}
void Player::updateMap(char to_put,Move where){
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
