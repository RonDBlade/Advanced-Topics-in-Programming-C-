#include "utilities.h"

void changePositionByMove(pair<int, int> position, Move mov, int rows, int cols){
    switch(mov){
        case Move::UP:
            position.second = positiveModulo(position.second - 1, rows);
            break;
        case Move::RIGHT:
            position.first = positiveModulo(position.first + 1, cols);
            break;
        case Move::DOWN:
            position.second = positiveModulo(position.second + 1, rows);
            break;
        case Move::LEFT:
            position.first = positiveModulo(position.first - 1, cols);
            break;}
}
