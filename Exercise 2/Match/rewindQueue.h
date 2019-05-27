#ifndef SAFEQUEUE_H_INCLUDED
#define SAFEQUEUE_H_INCLUDED

#include <mutex>
#include <queue>

template<class T>
class RewindQueue {

    std::vector<T> vec;
    size_t placeInVec;
    std::mutex m;

public:
    RewindQueue(): placeInVec(0){}

    void setSize(int expectedSize){
        vec.reserve(expectedSize);
    }

    void addElement(T elem) {
        std::lock_guard<std::mutex> lock(m);
        vec.push_back(elem);
    }

    int popElement(T& elem) {
        std::lock_guard<std::mutex> lock(m);
        if(placeInVec == vec.size()) {
            return -1;
        }
        elem = vec[placeInVec];
        return placeInVec++;
    }

    bool updateElement(int placeToUpdate, T& elem){
        if (placeToUpdate < (int)vec.size()){
            std::lock_guard<std::mutex> lock(m);
            vec[placeToUpdate] = elem;
            return true;
        }
        return false;
    }

    void rewindQueue(){
        std::lock_guard<std::mutex> lock(m);
        placeInVec = 0;
    }

};

#endif // SAFEQUEUE_H_INCLUDED
