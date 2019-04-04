#include <vector>
#include "player.h"
#include <iostream>

using std::map;
using std::pair;
using std::vector;


void Player::hitWall(){
    std::cout << "ouch!" << std::endl;
    player_map[current_position.first][current_position.second]='#';
    pair<Move,char> moved= movekeep.back();
    std::cout << "ouch2!" << std::endl;
    if(moved.first==Move::UP)
        current_position.second--;
    else if(moved.first==Move::DOWN)
        current_position.second++;
    else if(moved.first==Move::LEFT)
        current_position.first++;
    else if(moved.first==Move::RIGHT)
        current_position.first--;
    movekeep.back().second='#';
}


int Player::firstBook(){
    return bookmark_position.first;
}
int Player::secondBook(){
    return bookmark_position.second;
}

pair<int, int> Player::bookmark_pos()const{
    return bookmark_position;
}

void Player::hitBookmark(){//we want to update the map of locations
    int cnt=moveNumber;
    current_position=bookmark_pos();
    pair<int, int> pos=bookmark_pos();
    pair<Move,char> tmp;
    unsigned int tmpsize=movekeep.size();//so wont need to keep calculating this
    for(unsigned int i=0;i<tmpsize;i++){
        cnt--;
        if(i==tmpsize-1){//last iteration.this is where we started.which means it has to be a space.
            player_map[pos.first][pos.second]=' ';
            when_wasOn[pos.first][pos.second]=cnt;
            continue;
        }
        tmp=movekeep[tmpsize-1-i];
        if(tmp.first==Move::BOOKMARK)
            continue;
        if(tmp.second==' '){
            if(tmp.first==Move::UP){
                pos.second--;
                player_map[pos.first][pos.second]=tmp.second;
                when_wasOn[pos.first][pos.second]=cnt;//put it in each if SPECIFICALLY AND ON PURPOSE.DONT PUT THIS IN THE END TO SAVE LINES

            }
            else if(tmp.first==Move::DOWN){
                pos.second++;
                player_map[pos.first][pos.second]=tmp.second;
                when_wasOn[pos.first][pos.second]=cnt;

            }
            else if(tmp.first==Move::LEFT){
                pos.first++;
                player_map[pos.first][pos.second]=tmp.second;
                when_wasOn[pos.first][pos.second]=cnt;

            }
            else{
                pos.first--;
                player_map[pos.first][pos.second]=tmp.second;
                when_wasOn[pos.first][pos.second]=cnt;
            }

        }
        else{//if we walked into a wall in that one,then only need to set it as a wall for later.
            if(tmp.first==Move::UP){
                player_map[pos.first][pos.second+1]=tmp.second;

            }
            else if(tmp.first==Move::DOWN){
                player_map[pos.first][pos.second-1]=tmp.second;

            }
            else if(tmp.first==Move::LEFT){
                player_map[pos.first-1][pos.second]=tmp.second;

            }
            else if(tmp.first==Move::RIGHT){
                player_map[pos.first+1][pos.second]=tmp.second;

            }
        }
    }




    movekeep.clear();
}

Player::Player(): current_position(0, 0), bookmark_position(0, 0){
    player_map[0][0]=' ';
    when_wasOn[0][0]=0;
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
    else if(movnum==1)
        return Move::DOWN;
    else if(movnum==2)
        return Move::LEFT;
    return Move::RIGHT;
}
int Player::getLocMove(int x, int y){
    return when_wasOn[x][y];
}


Move Player::move(){//for now,SIMPLE IMPLEMENTATION
    //first check places we haven't been to yet.
    std::cout<< current_position.first << " " << current_position.second << std::endl;
    int tmp1;
    int tmp2;
    tmp2=2147483647;//to keep the least visited loc for later in the func.tmp2 is max integer value for flow in loop
    Move tmp3,returnMove=Move::UP;
    moveNumber++;
 //   if(putBookmark()){
    //    bookmark_pos()=player_pos();
    //    pushtoMoveKeep(Move::BOOKMARK,' ');
    //    std::cout<< "BOOKMARK" << std::endl;
     //   return Move::BOOKMARK;
    //}
    bool checkLoc=Player::isKnown(current_position.first,current_position.second+1);//checks if the player discovered whats above him already
    if(!checkLoc){
        current_position.second++;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        pushtoMoveKeep(returnMove,' ');
        std::cout<< "UP" << std::endl;
        return Move::UP;
    }
    checkLoc=Player::isKnown(current_position.first,current_position.second-1); //same for down
    if(!checkLoc){
        current_position.second--;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        pushtoMoveKeep(returnMove,' ');
        std::cout<< "DOWN" << std::endl;
        return Move::DOWN;
    }
    checkLoc=Player::isKnown(current_position.first-1,current_position.second); //same for left
    if(!checkLoc){
        current_position.first--;
        setLocMove(current_position.first-1,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        pushtoMoveKeep(returnMove,' ');
        std::cout<< "LEFT" << std::endl;
        return Move::LEFT;
    }
    checkLoc=Player::isKnown(current_position.first+1,current_position.second); //same for right
    if(!checkLoc){
        current_position.first++;
        setLocMove(current_position.first+1,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        pushtoMoveKeep(returnMove,' ');
        std::cout<< "RIGHT" << std::endl;
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
    if (movevec.empty())
        return Move::BOOKMARK;//if everything is a wall he is fucked lmaoooooooooooooooooooooo
    else if (movevec.size()==1)
        return whatMove(movevec.front());
    //now we have all the tiles around him which are not walls.lets visit the one we visited the earliest between them!
    for(unsigned int i=0;i<movevec.size();i++){//finally, find the place we visited the most in the past from our current options
        tmp1=movevec.back();
        tmp3=whatMove(tmp1);
        tmp1=findMoveNum(tmp3);
        if(tmp1<tmp2){
            tmp2=tmp1;
            returnMove=tmp3;
        }
    }
    setbyMove(returnMove);
    pushtoMoveKeep(returnMove,' ');

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
