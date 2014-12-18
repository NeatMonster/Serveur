#ifndef __Serveur__CommandStop__
#define __Serveur__CommandStop__

#include "Command.h"

class CommandStop : public Command {
public:
    CommandStop();

    void perform(CommandSender*, std::vector<string_t>);
};

#endif /* defined(__Serveur__CommandStop__) */
