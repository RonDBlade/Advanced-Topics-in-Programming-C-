#ifndef SAFEQUEUE_H_INCLUDED
#define SAFEQUEUE_H_INCLUDED

#include <mutex>
#include <queue>

template<class T>
class RewindQueue {

    std::vector<T> vec;
    typename std::vector<T>::iterator it;
    std::mutex m;

public:
    RewindQueue() {
        it = vec.begin();
    }

    void setSize(int expectedSize){
        vec.reserve(expectedSize);
    }

    void addElement(T elem) {
        std::lock_guard<std::mutex> lock(m);
        vec.push_back(elem);
        std::cout << "Added " << vec.size() << " elements already" << std::endl;
    }

    bool popElement(T& elem) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "Trying to get out an element" << endl;
        if(it == vec.end()) {
            return false;
        }
        elem = *it;
        it++;
        return true;
    }

    void rewindQueue(){
        std::lock_guard<std::mutex> lock(m);
        it = vec.begin();
    }

};

#endif // SAFEQUEUE_H_INCLUDED
