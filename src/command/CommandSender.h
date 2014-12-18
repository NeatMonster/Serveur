#ifndef __Serveur__CommandSender__
#define __Serveur__CommandSender__

#include "ChatMessage.h"
#include "Types.h"

class World;

class CommandSender {
public:
    virtual string_t getName() = 0;

    virtual World *getWorld() = 0;

    virtual void sendMessage(ChatMessage&) = 0;
};

#endif /* defined(__Serveur__CommandSender__) */
