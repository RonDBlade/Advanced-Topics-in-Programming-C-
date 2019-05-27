#include "matchManager.h"

int main(int argc, char *argv[]){
    matchManager mM = matchManager();
    mM.processMatch(argc, argv);
    return 0;
}
