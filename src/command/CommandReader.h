#ifndef __Serveur__CommandReader__
#define __Serveur__CommandReader__

#include "CommandQueue.h"

#include <thread>

class CommandReader {
public:
    CommandReader(CommandQueue*);

    ~CommandReader();

private:
    bool running;
    std::thread thread;
    CommandQueue *commands;

    void run();

    int kbhit();
};

#endif /* defined(__Serveur__CommandReader__) */
