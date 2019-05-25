#include "safeQueue.h"

template<class T>
class SafeQueue {

    std::queue<T*> q;
    std::mutex m;

public:

    SafeQueue() {}

void addElement(T* elem) {
    std::lock_guard<std::mutex> lock(m);
    if (elem == nullptr) {
        return;
    }
    q.push(elem);
}

bool popElement(T& elem) {
    std::lock_guard<std::mutex> lock(m);
    if(q.empty()) {
        return false;
    }
    elem = q.front();
    q.pop();
    return true;
}

};
