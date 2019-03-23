#include <vector>
#include <pair>

#define STARTING_MAP_SIZE 5 /*why?*/

using std::vector
using std::pair

class Player{
    vector<vector<int>> player_map; /*should change to map of maps.From my understanding of the implementation we start the player from position
    (0,0) in his perspective,and if we treat some positions as "-" positions(down from (0,0) is (0,-1)),we cant do that with vectors*/
    pair<int, int> current_position;
    pair<int, int> bookmark_position;

public:
    Player():{
        player_map.resize(STARTING_MAP_SIZE);
        for(int i = 0; i < STARTING_MAP_SIZE; i++){
            player_map[i].resize(STARTING_MAP_SIZE);
        }
        current_position.first = current_position.second = 0;
        bookmark_position.first = bookmark_position.second = 0;
    }
};
