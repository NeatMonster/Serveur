#ifndef __Serveur__CommandGameMode__
#define __Serveur__CommandGameMode__

#include "Command.h"

class CommandGameMode : public Command {
public:
    CommandGameMode();

    void perform(CommandSender*, std::vector<string_t>);


};

#endif /* defined(__Serveur__CommandGameMode__) */
