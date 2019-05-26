#ifndef SAFEQUEUE_H_INCLUDED
#define SAFEQUEUE_H_INCLUDED

#include <mutex>
#include <queue>

template<class T>
class RewindQueue {

    std::vector<T*> vec;
    typename std::vector<T>::iterator it;
    std::mutex m;

public:
    RewindQueue() {}
    void setSize(int expectedSize);
    void addElement(T* elem);
    bool popElement(T& elem);
    void rewindQueue();
};

#endif // SAFEQUEUE_H_INCLUDED
