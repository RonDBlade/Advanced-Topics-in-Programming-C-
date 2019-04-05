#include <vector>
#include "player.h"
#include <iostream>

using std::map;
using std::pair;
using std::vector;


void Player::hitWall(){
    std::cout << "ouch!" << std::endl;
    player_map[current_position.first][current_position.second]='#';
    if(lastMove==Move::UP){
        std::cout << "UP TO WALL" << std::endl;
        current_position.second--;
    }
    else if(lastMove==Move::DOWN){
        std::cout << "DOWN TO WALL" << std::endl;
        current_position.second++;
    }
    else if(lastMove==Move::LEFT){
        std::cout << "LEFT TO WALL" << std::endl;
        current_position.first++;
    }
    else if(lastMove==Move::RIGHT){
        std::cout << "RIGHT TO WALL" << std::endl;
        current_position.first--;
    }
    else if(lastMove==Move::BOOKMARK){
        std::cout << "BOOKMARK TO WALL" << std::endl;
    }
    else{
        std::cout << "the fuck?" << std::endl;
    }
    if(bookmark_on)
        movekeep.back().second='#';
    when_wasOn[current_position.first][current_position.second]=moveNumber;
}



pair<int, int> Player::bookmark_pos()const{
    return bookmark_position;
}

void Player::hitBookmark(){//we want to update the map of locations
    int cnt=moveNumber;
    std::cout << "FOUND BOOKMARK IN POSITION"<<bookmark_position.first << " "<< bookmark_position.second << std::endl;
    bookmark_on=false;
    std::cout << "put_bookmark is of size before"<< put_bookmark << std::endl;
    put_bookmark/=2;
    if(put_bookmark<10)
        put_bookmark=10;
    bookmark_count=0;
    std::cout << "put_bookmark is of size after"<< put_bookmark << std::endl;
    current_position=bookmark_pos();
    pair<int, int> pos=bookmark_pos();
    pair<Move,char> tmp;
    unsigned int tmpsize=movekeep.size();//so wont need to keep calculating this
    for(int i=0;(unsigned int)i<tmpsize;i++){
        cnt--;
        if((unsigned int)i==tmpsize-1){//last iteration.this is where we started.which means it has to be a space.
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
            else if(tmp.first==Move::RIGHT){
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
    if(bookmark_on)
        bookmark_count++;
//    if(putBookmark()){
//        bookmark_count=0;
//        bookmark_position.first=player_pos().first;
//        bookmark_position.second=player_pos().second;
////        pushtoMoveKeep(Move::BOOKMARK,' ');
 //       when_wasOn[current_position.first][current_position.second]=moveNumber;
   //     std::cout<< "BOOKMARK IN POSITION"<<bookmark_position.first << " "<< bookmark_position.second << std::endl;
//        return Move::BOOKMARK;
 //   }
    bool checkLoc=Player::isKnown(current_position.first,current_position.second+1);//checks if the player discovered whats above him already
    if(!checkLoc){
        current_position.second++;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::UP,' ');
        moved_to_new=true;
        lastMove=Move::UP;
        std::cout<< "UP" << std::endl;
        return Move::UP;
    }
    checkLoc=Player::isKnown(current_position.first,current_position.second-1); //same for down
    if(!checkLoc){
        current_position.second--;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::DOWN,' ');
        moved_to_new=true;
        lastMove=Move::DOWN;
        std::cout<< "DOWN" << std::endl;
        return Move::DOWN;
    }
    checkLoc=Player::isKnown(current_position.first-1,current_position.second); //same for left
    if(!checkLoc){
        current_position.first--;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::LEFT,' ');
        moved_to_new=true;
        lastMove=Move::LEFT;
        std::cout<< "LEFT" << std::endl;
        return Move::LEFT;
    }
    checkLoc=Player::isKnown(current_position.first+1,current_position.second); //same for right
    if(!checkLoc){
        current_position.first++;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::RIGHT,' ');
        moved_to_new=true;
        lastMove=Move::RIGHT;
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
    if(!checkLoc){
        movevec.push_back(3);
        std::cout << "cant go right theres a wall m8!" << std::endl;
    }
    if (movevec.empty())
        return Move::BOOKMARK;//if everything is a wall he is fucked lmaoooooooooooooooooooooo
    else if (movevec.size()==1){
        if(bookmark_on)
            pushtoMoveKeep(whatMove(movevec.front()),' ');
        lastMove=whatMove(movevec.front());
        return whatMove(movevec.front());
    }
    //now we have all the tiles around him which are not walls.lets visit the one we visited the earliest between them!
    for(int i=0;(unsigned int)i<movevec.size();i++){//finally, find the place we visited the most in the past from our current options
        tmp1=movevec.back();
        movevec.pop_back();
        tmp3=whatMove(tmp1);
        tmp1=findMoveNum(tmp3);
        if(tmp1<tmp2){
            tmp2=tmp1;
            returnMove=tmp3;
        }
    }
    setbyMove(returnMove);
    if(bookmark_on)
        pushtoMoveKeep(returnMove,' ');
    lastMove=returnMove;
    moved_to_new=false;
    return returnMove;
}
