#include <vector>
#include "player.h"

using std::map;
using std::pair;
using std::vector;

Player::Player(): current_position(0, 0), bookmark_position(0, 0){
    player_map[0][0]=' ';
}
pair<int, int> Player::player_pos()const{
    return current_position;
}
void Player::increaseMovenum(){
        moveNumber++;
    }
void Player::setLocMove(int x,int y){
        when_wasOn[x][y]=moveNumber;
    }

Move whatMove(int movnum){
    if(movnum==0)
        return Move::UP;
    if(movnum==1)
        return Move::DOWN;
    if(movnum==2)
        return Move::LEFT;
    return Move::RIGHT;
}
int Player::getLocMove(int x, int y){
    return when_wasOn[x][y];
}
int findMoveNum(Move mov){
    if(mov==Move::UP)
        return Player::getLocMove(current_position.first,current_position.second+1);
    if(mov==Move::DOWN)
        return Player::getLocMove(current_position.first,current_position.second-1);
    if(mov==Move::LEFT)
        return Player::getLocMove(current_position.first-1,current_position.second);
    return Player::getLocMove(current_position.first+1,current_position.second);
}
void setbyMove(Move mov){
    if(mov==Move::UP)
        return when_wasOn[current_position.first][current_position.second+1];
    if(mov==Move::DOWN)
        return when_wasOn[current_position.first][current_position.second-1];
    if(mov==Move::LEFT)
        return when_wasOn[current_position.first-1][current_position.second];
    return when_wasOn[current_position.first+1][current_position.second];
}

Move Player::move(){//for now,SIMPLE IMPLEMENTATION
    //first check places we haven't been to yet.
    int tmp1,tmp2=2,147,483,647;//to keep the least visited loc for later in the func.tmp2 is max integer value for flow in loop
    Move tmp3,returnMove;
    moveNumber++;
    bool checkLoc=Player::isKnown(current_position.first,current_position.second+1);//checks if the player discovered whats above him already
    if(!checkLoc){
        setLocMove(current_position.first,current_position.second+1);
        return Move::UP;
    }
    checkLoc=Player::isKnown(current_position.first,current_position.second-1); //same for down
    if(!checkLoc){
        setLocMove(current_position.first,current_position.second-1);
        return Move::DOWN;
    }
    checkLoc=Player::isKnown(current_position.first-1,current_position.second); //same for left
    if(!checkLoc){
        setLocMove(current_position.first-1,current_position.second);
        return Move::LEFT;
    }
    checkLoc=Player::isKnown(current_position.first+1,current_position.second); //same for right
    if(!checkLoc){
        setLocMove(current_position.first+1,current_position.second);
        return Move::RIGHT;
    }
    //if we got here,we already know ALL the locations which surround the player.Time to find which are a wall and which arent.
    vector<int> movevec;
    checkLoc=Player::isWall(current_position.first,current_position.second+1);//checks if the position above the player is a wall
    if(!checkLoc)
        movevec.push_back(0);
    checkLoc=Player::isWall(current_position.first,current_position.second-1);//same for down
    if(!checkLoc)
        movevec.push_back(1);
    checkLoc=Player::isWall(current_position.first-1,current_position.second);//same for left
    if(!checkLoc)
        movevec.push_back(2);
    checkLoc=Player::isWall(current_position.first+1,current_position.second);//same for right
    if(!checkLoc)
        movevec.push_back(3);
    if movevec.empty()
        return Move::BOOKMARK;//if everything is a wall he is fucked lmaoooooooooooooooooooooo
    if movevec.size()==1
        return whatMove(movevec.front());
    //now we have all the tiles around him which are not walls.lets visit the one we visited the earliest between them!
    for(int i=0;i<movevec.size();i++){//finally, find the place we visited the most in the past from our current options
        tmp1=movevec.back();
        tmp3=whatMove(tmp1);
        tmp1=findMoveNum(tmp3);
        if(tmp1<tmp2){
            tmp2=tmp1;
            returnMove=tmp3;
        }
    }
    setbyMove(returnMove);
    return returnMove;
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
