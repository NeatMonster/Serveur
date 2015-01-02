#ifndef __Serveur__ConfigManager__
#define __Serveur__ConfigManager__

#include "Types.h"

class ConfigManager {
public:
    ConfigManager();

    void load();

    void save();

    string_t getServerIP();

    ushort_t getServerPort();

private:
    string_t serverIP = "0.0.0.0";
    ushort_t serverPort = 25566;
};

#endif /* defined(__Serveur__ConfigManager__) */
