#ifndef __Serveur__CommandReader__
#define __Serveur__CommandReader__

#include "CommandQueue.h"

#include <thread>

class CommandReader {
public:
    CommandReader(CommandQueue*);

private:
    std::thread thread;
    CommandQueue *commands;

    void run();
};

#endif /* defined(__Serveur__CommandReader__) */
