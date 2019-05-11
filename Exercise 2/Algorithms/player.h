#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <map>
#include <utility>
#include <vector>
#include "AbstractAlgorithm.h"


using std::map;
using std::pair;
using std::vector;


class Player: public AbstractAlgorithm {
    map<int, map<int,char> > player_map;
    map<int, map<int,int> > when_wasOn; //keeps for each location when we have last visited it.helps us decide which way to go.
    int moveNumber=0;//keeps the count of moves for
    Move lastMove;
    pair<int, int> current_position;
    pair<int, int> bookmark_position; /*should keep this as game manager data,since he doesnt remember where he put it*/
    vector<pair<Move,char> > movekeep;//keeps us the moves we did until we hit a bookmark
    //IMPORTANT: to add the moves to this vector,we cant do it in move.this adds to the vector what move we did and were it got us to.so it has to be push_back()ed in gameManager
    int put_bookmark=10;//when bookmark_count==put_bookmark then we put a new bookmark
    int bookmark_count=0;
    bool bookmark_on=false;//true when we have a bookmark on the board
    bool moved_to_new=false;
    int highest_bookmark=0;
    
public:
    Player();
    Move move();
    void hitWall(int seq);
    
private:
    pair<int, int> player_pos()const;
    pair<int, int> bookmark_pos()const;
    void updateMap(char to_put,Move where);
    void increaseMovenum();
    void setLocMove(int x,int y);
    int getLocMove(int x, int y);
    void hitBookmark();
    int firstPlyr();
    int secondPlyr();
    int firstBook();
    int secondBook();
    void setbyMove(Move mov);
    int findMoveNum(Move mov);
    void pushtoMoveKeep(Move moved,char tileWentTo);
    bool putBookmark();
    bool isWall(int x,int y);
    bool isKnown(int x,int y);
};

#endif // PLAYER_H_INCLUDED
