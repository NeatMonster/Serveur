#include "PacketQueue.h"

template<typename T>
void PacketQueue<T>::pop(T &item) {
    std::unique_lock<std::mutex> lock(mutex);
    while (!shouldWake && queue.empty())
        condition.wait(lock);
    if (!shouldWake) {
        item = queue.front();
        queue.pop();
    }
}

template<typename T>
void PacketQueue<T>::push(T const &item) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(item);
    lock.unlock();
    condition.notify_one();
}

template<typename T>
bool PacketQueue<T>::tryPop(T &item) {
    std::unique_lock<std::mutex> lock(mutex);
    if (queue.empty())
        return false;
    item = queue.front();
    queue.pop();
    return true;
}

template<typename T>
void PacketQueue<T>::wake() {
    shouldWake = true;
    condition.notify_one();
}
