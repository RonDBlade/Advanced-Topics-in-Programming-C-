#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <map>
#include <utility>


using std::map;
using std::pair;

enum class Move{LEFT, RIGHT, UP, DOWN, BOOKMARK};

class Player{
    map<int, map<int,char> > player_map; /*should change to map of maps.From my understanding of the implementation we start the player from position
    (0,0) in his perspective,and if we treat some positions as "-" positions(down from (0,0) is (0,-1)),we cant do that with vectors*/
    map<int, map<int,int> > when_wasOn; //keeps for each location when we have last visited it.helps us decide which way to go.
    int moveNumber=0;//keeps the count of moves for
    pair<int, int> current_position;
    pair<int, int> bookmark_position; /*should keep this as game manager data,since he doesnt remember where he put it*/
    void hitWall(){}
    bool isKnown(int x,int y){//this PRIVATE method checks if player has been on this coordination yet.On HIS map,not the maze map.
        if(!player_map.count(x))//no point in this x coordination has been discovered,so this one hasn't either
            return false;
        if(!player_map[x].count(y))//this specific point hasn't been discovered yet
            return false;
        return true;//we have visited this cell in the past
    }
    bool isWall(int x,int y){
        return player_map[x][y]=='#';
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
            when_wasOn[current_position.first][current_position.second+1]=moveNumber;
        if(mov==Move::DOWN)
            when_wasOn[current_position.first][current_position.second-1]=moveNumber;
        if(mov==Move::LEFT)
            when_wasOn[current_position.first-1][current_position.second]=moveNumber;
        when_wasOn[current_position.first+1][current_position.second]=moveNumber;
    }
public:
    Player();
    pair<int, int> player_pos()const;
    pair<int, int> bookmark_pos()const;
    Move move();
    void updateMap(char to_put,Move where);
    void increaseMovenum();
    void setLocMove(int x,int y);
    int getLocMove(int x, int y);
    void hitBookmark();
    int firstPlyr();
    int secondPlyr();
    int firstBook();
    int secondBook();
};

#endif // PLAYER_H_INCLUDED
