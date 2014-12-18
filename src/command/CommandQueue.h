#ifndef __Serveur__CommandQueue__
#define __Serveur__CommandQueue__

#include "Types.h"

#include <condition_variable>
#include <mutex>

class CommandQueue {
public:
    void push(string_t);

    bool tryPop(string_t*);

private:
    std::vector<string_t> vector;
    std::mutex mutex;
};

#endif /* defined(__Serveur__CommandQueue__) */
