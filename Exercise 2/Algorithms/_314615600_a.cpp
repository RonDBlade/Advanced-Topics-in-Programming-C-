#include <iostream>
#include "_314615600_a.h"
REGISTER_ALGORITHM(_314615600_a)

bool _314615600_a::isKnown(int x,int y){//this method checks if player has been on this coordination yet.On HIS map,not the maze map.
        if(!player_map.count(x))//no point in this x coordination has been discovered,so this one hasn't either
            return false;
        if(!player_map[x].count(y))//this specific point hasn't been discovered yet
            return false;
        return true;//we have visited this cell in the past
    }

bool _314615600_a::isWall(int x,int y){
        return player_map[x][y]=='#';
    }

bool _314615600_a::putBookmark(){
    highest_bookmark++;
    if(moveNumber==1){
        //just started the game
        bookmark_on=true;
        return true;
    }
    else if(bookmark_on==false&&moved_to_new){
        //if we dont have a bookmark and this is a new place we just went to
        bookmark_on=true;
        return true;
    }
    else if(bookmark_count==put_bookmark){//if we waited too long for a bookmark
        put_bookmark*=2;
        bookmark_on=true;
        return true;
    }
    return false;
}

void _314615600_a::pushtoMoveKeep(Move moved,char tileWentTo){
        movekeep.push_back({moved,tileWentTo});
    }

int _314615600_a::findMoveNum(Move mov){
        if(mov==Move::UP)
            return _314615600_a::getLocMove(current_position.first,current_position.second+1);
        if(mov==Move::DOWN)
            return _314615600_a::getLocMove(current_position.first,current_position.second-1);
        if(mov==Move::LEFT)
            return _314615600_a::getLocMove(current_position.first-1,current_position.second);
        return _314615600_a::getLocMove(current_position.first+1,current_position.second);
    }


void _314615600_a::setbyMove(Move mov){
        if(mov==Move::UP){
            current_position.second++;
        }
        else if(mov==Move::DOWN){
            current_position.second--;
        }
        else if(mov==Move::LEFT){
            current_position.first--;
        }
        else if(mov==Move::RIGHT){
            current_position.first++;
        }
        when_wasOn[current_position.first][current_position.second]=moveNumber;
        player_map[current_position.first][current_position.second]=' ';
    }

void _314615600_a::hitWall(){
    player_map[current_position.first][current_position.second]='#';
    if(lastMove==Move::UP){
        current_position.second--;
    }
    else if(lastMove==Move::DOWN){
        current_position.second++;
    }
    else if(lastMove==Move::LEFT){
        current_position.first++;
    }
    else if(lastMove==Move::RIGHT){
        current_position.first--;
    }
    else if(lastMove==Move::BOOKMARK){
    }
    if(bookmark_on)
        movekeep.back().second='#';
    when_wasOn[current_position.first][current_position.second]=moveNumber;
}



pair<int, int> _314615600_a::bookmark_pos()const{
    return bookmark_position;
}

void _314615600_a::hitBookmark(int seq){//we want to update the map of locations
        if(seq==highest_bookmark){
            int cnt=moveNumber;
            bookmark_on=false;
            put_bookmark/=2;
            if(put_bookmark<10)
                put_bookmark=10;
            bookmark_count=0;
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
                        pos.second--; //put it in each if SPECIFICALLY AND ON PURPOSE.DONT PUT THIS IN THE END TO SAVE LINES
                    }
                    else if(tmp.first==Move::DOWN){
                        pos.second++;
                    }
                    else if(tmp.first==Move::LEFT){
                        pos.first++;
                    }
                    else if(tmp.first==Move::RIGHT){
                        pos.first--;
                    }
                    player_map[pos.first][pos.second]=tmp.second;
                    when_wasOn[pos.first][pos.second]=cnt;
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
}

_314615600_a::_314615600_a(): current_position(0, 0), bookmark_position(0, 0){
    player_map[0][0]=' ';
    when_wasOn[0][0]=0;
}
pair<int, int> _314615600_a::player_pos()const{
    return current_position;
}
void _314615600_a::increaseMovenum(){
        moveNumber++;
    }
void _314615600_a::setLocMove(int x,int y){
        when_wasOn[x][y]=moveNumber;
    }

int _314615600_a::getLocMove(int x, int y){
    return when_wasOn[x][y];
}


AbstractAlgorithm::Move _314615600_a::move(){//for now,SIMPLE IMPLEMENTATION
    //first check places we haven't been to yet.
    int tmp1;
    int tmp2;
    tmp2=2147483647;//to keep the least visited loc for later in the func.tmp2 is max integer value for flow in loop
    Move tmp3,returnMove=Move::LEFT;
    moveNumber++;
    if(bookmark_on)
        bookmark_count++;
    if(putBookmark()){
        bookmark_count=0;
        bookmark_position.first=player_pos().first;
        bookmark_position.second=player_pos().second;
        pushtoMoveKeep(Move::BOOKMARK,' ');
        when_wasOn[current_position.first][current_position.second]=moveNumber;
        return Move::BOOKMARK;
    }
    std::cout << "ARG" << std::endl;
    bool checkLoc=_314615600_a::isKnown(current_position.first,current_position.second+1);//checks if the player discovered whats above him already
    if(!checkLoc){
        current_position.second++;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::UP,' ');
        moved_to_new=true;
        lastMove=Move::UP;
        return Move::UP;
    }
    checkLoc=_314615600_a::isKnown(current_position.first,current_position.second-1); //same for down
    if(!checkLoc){
        current_position.second--;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::DOWN,' ');
        moved_to_new=true;
        lastMove=Move::DOWN;
        return Move::DOWN;
    }
    checkLoc=_314615600_a::isKnown(current_position.first-1,current_position.second); //same for left
    if(!checkLoc){
        current_position.first--;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::LEFT,' ');
        moved_to_new=true;
        lastMove=Move::LEFT;
        return Move::LEFT;
    }
    checkLoc=_314615600_a::isKnown(current_position.first+1,current_position.second); //same for right
    if(!checkLoc){
        current_position.first++;
        setLocMove(current_position.first,current_position.second);
        player_map[current_position.first][current_position.second]=' ';
        if(bookmark_on)
            pushtoMoveKeep(Move::RIGHT,' ');
        moved_to_new=true;
        lastMove=Move::RIGHT;
        return Move::RIGHT;
    }
    //if we got here,we already know ALL the locations which surround the player.Time to find which are a wall and which aren't.
    vector<Move> movevec;

    checkLoc=_314615600_a::isWall(current_position.first,current_position.second+1);//checks if the position above the player is a wall
    if(!checkLoc)
        movevec.push_back(Move::UP);
    checkLoc=_314615600_a::isWall(current_position.first,current_position.second-1);//same for down
    if(!checkLoc)
        movevec.push_back(Move::DOWN);
    checkLoc=_314615600_a::isWall(current_position.first-1,current_position.second);//same for left
    if(!checkLoc)
        movevec.push_back(Move::LEFT);
    checkLoc=_314615600_a::isWall(current_position.first+1,current_position.second);//same for right
    if(!checkLoc){
        movevec.push_back(Move::RIGHT);
    }
    if (movevec.empty())
        return Move::BOOKMARK;// everything is a wall
    else if (movevec.size()==1){
        if(bookmark_on)
            pushtoMoveKeep(movevec.front(),' ');
        lastMove=movevec.front();
        setbyMove(lastMove);
        return lastMove;
    }
    //now we have all the tiles around him which are not walls.lets visit the one we visited the earliest between them!
    for(int i=0;movevec.size()!=0;i++){//finally, find the place we visited the most in the past from our current options
        tmp3=movevec.back();
        movevec.pop_back();
        tmp1=findMoveNum(tmp3);
        if(tmp1<tmp2){
            tmp2=tmp1;
            returnMove=tmp3;
        }
    }
   setbyMove(returnMove);
    when_wasOn[current_position.first][current_position.second]=moveNumber;
    player_map[current_position.first][current_position.second]=' ';
    if(bookmark_on)
        pushtoMoveKeep(returnMove,' ');
    lastMove=returnMove;
    moved_to_new=false;
    return returnMove;
}
