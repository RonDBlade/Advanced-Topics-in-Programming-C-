#include "matchManager.h"

int main(int argc, char *argv[]){
    std::shared_ptr<matchManager> mM = std::make_shared<matchManager>();
    mM->processMatch(argc, argv);
    return 0;
}
