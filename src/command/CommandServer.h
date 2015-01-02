#ifndef __Serveur__CommandServer__
#define __Serveur__CommandServer__

#include "Command.h"

class CommandServer : public Command {
public:
    CommandServer();

    void perform(CommandSender*, std::vector<string_t>);
};

#endif /* defined(__Serveur__CommandServer__) */
