#ifndef __Serveur__PacketQueue__
#define __Serveur__PacketQueue__

#include <condition_variable>
#include <mutex>
#include <queue>

template<typename T>
class PacketQueue {
public:
    void pop(T&);

    void push(T const &);

    bool tryPop(T&);

    void wake();

private:
    bool shouldWake = false;
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition;
};

#endif /* defined(__Serveur__PacketQueue__) */
