#ifndef _314615600_B_H_INCLUDED
#define _314615600_B_H_INCLUDED
#include <map>
#include <utility>
#include <vector>
#include "AbstractAlgorithm.h"


using std::map;
using std::pair;
using std::vector;


class _314615600_b: public AbstractAlgorithm{
    map<int, map<int,char> > player_map;
    map<int, map<int,int> > when_wasOn; //keeps for each location when we have last visited it.helps us decide which way to go.
    int moveNumber=0;//keeps the count of moves for
    Move lastMove;//keeps the last move the player did,for restoring after we hit a wall
    pair<int, int> current_position;
    vector<pair<int, int> > bookmark_position; /*should keep this as game manager data,since he doesnt remember where he put it*/
    vector<vector<pair<Move,char> > >movekeep;//keeps us the moves we did until we hit a bookmark
    //IMPORTANT: to add the moves to this vector,we cant do it in move.this adds to the vector what move we did and were it got us to.so it has to be push_back()ed in gameManager
    int total_bookmarks=0; //the total amount of bookmarks we put down
    int biggest_met=0;//largest bookmark sequence number we already stepped on,so we can ignore younger ones.
    int put_bookmark=10;//when bookmark_count==put_bookmark then we put a new bookmark
    int bookmark_count=0;
    bool bookmark_on=false;//true when we have a bookmark on the board
    bool moved_to_new=false;

public:
    _314615600_b();
    Move move();
    void hitWall();
    void hitBookmark(int seq);


private:
    pair<int, int> player_pos()const;//return player position
    pair<int, int> bookmark_pos(int seq)const;//return bookmark position
    void updateMap(char to_put,Move where);
    void setLocMove(int x,int y);//sets the move of the location given
    int getLocMove(int x, int y);
    void setbyMove(Move mov);//set data on player map
    int findMoveNum(Move mov);//for a square around the player in the mov direction,checks when we last visited it
    void pushtoMoveKeep(Move moved,char tileWentTo);
    bool putBookmark();//checks if we should put a bookmark in the player position
    bool isWall(int x,int y);//checks if player already knows this is a wall or it isnt a wall
    bool isKnown(int x,int y);//checks if player has already been here
    void removeBookmarkUntill(int seq);//removes bookmarks until the bookmark we met,which is given at seq
    void cleanKeepUntil(int seq);//removes data from move_keep until the bookmark we met,which is given at seq
};

#endif // _314615600_B_H_INCLUDED
