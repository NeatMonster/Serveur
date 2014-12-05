#ifndef __Serveur__Logger__
#define __Serveur__Logger__

#include <iostream>

class Logger {
public:
    static std::ostream &info();

    static std::ostream &warning();

    static std::ostream &severe();

private:
    static std::ostream &time();
};

#endif /* defined(__Serveur__Logger__) */
