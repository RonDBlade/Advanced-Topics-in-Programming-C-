#include "safeQueue.h"

template<class T>
class RewindQueue {

    std::vector<T*> vec;
    std::vector<T>::iterator it;
    std::mutex m;

public:

    RewindQueue() {}

void RewindQueue::setSize(int expectedSize){
    vec.reserve(expectedSize);
}

void RewindQueue::addElement(T* elem) {
    std::lock_guard<std::mutex> lock(m);
    if (elem == nullptr) {
        return;
    }
    vec.push_back(elem);
}

bool RewindQueue::popElement(T& elem) {
    std::lock_guard<std::mutex> lock(m);
    if(it == vec.end()) {
        return false;
    }
    if(it == nullptr){
        it = vec.begin();
    }
    elem = *it;
    it++;
    return true;
}

void RewindQueue::rewindQueue(){
    std::lock_guard<std::mutex> lock(m);
    it = vec.begin();
}

};
