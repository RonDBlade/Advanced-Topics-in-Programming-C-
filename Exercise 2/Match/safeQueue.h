#ifndef SAFEQUEUE_H_INCLUDED
#define SAFEQUEUE_H_INCLUDED

#include <mutex>
#include <queue>

void addElement(T* elem);
bool popElement(T& elem);

#endif // SAFEQUEUE_H_INCLUDED
