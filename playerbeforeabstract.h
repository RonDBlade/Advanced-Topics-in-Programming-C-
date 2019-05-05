#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <map>
#include <utility>
#include <vector>


using std::map;
using std::pair;
using std::vector;

enum class Move{LEFT, RIGHT, UP, DOWN, BOOKMARK};

class Player{
    map<int, map<int,char> > player_map; /*should change to map of maps.From my understanding of the implementation we start the player from position
    (0,0) in his perspective,and if we treat some positions as "-" positions(down from (0,0) is (0,-1)),we cant do that with vectors*/
    map<int, map<int,int> > when_wasOn; //keeps for each location when we have last visited it.helps us decide which way to go.
    int moveNumber=0;//keeps the count of moves for
    Move lastMove;
    int bookmark_counter; //counts how many bookmarks we have set,so that when it is 0 we know we can set bookmark_on to false.
    pair<int, int> current_position;
    int max_bookmark=0;//tells us which bookmark is the highest we met,so that if we meet an older one,we won't redo the data we learned from it.
    vector<pair<pair<int, int>, int > > bookmark_position; //queue of pairs of pairs.the first pair is the x,y coordinations,and then the solo number is bookmark number
    int offset=0; //offset of which move we need to sub in the information about the bookmark position that we hit.
    vector<pair<vector<pair<Move,char> >,int> > movekeep;//keeps us the moves we did until we hit a bookmark.the int is the number of bookmark of the vector.
    //IMPORTANT: to add the moves to this vector,we cant do it in move.this adds to the vector what move we did and were it got us to.so it has to be push_back()ed in gameManager
    int put_bookmark=10;//when bookmark_count==put_bookmark then we put a new bookmark
    int bookmark_count=0;//for when to put bookmarks calculations
    bool bookmark_on=false;//true when we have a bookmark on the board
    bool moved_to_new=false;
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

    bool putBookmark(){
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

    void pushtoMoveKeep(Move moved,char tileWentTo){
    movekeep.back().push_back({moved,tileWentTo});
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

public:
    Player();
    pair<int, int> player_pos()const;
    pair<int, int> bookmark_pos()const;
    Move move();
    void updateMap(char to_put,Move where);
    void increaseMovenum();
    void setLocMove(int x,int y);
    int getLocMove(int x, int y);
    void hitBookmark(int seq);
    int firstPlyr();
    int secondPlyr();
    int firstBook();
    int secondBook();
    void setbyMove(Move mov);
    void hitWall();
};

#endif // PLAYER_H_INCLUDED
