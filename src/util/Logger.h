#ifndef __Serveur__Logger__
#define __Serveur__Logger__

#include "Types.h"

#include <iostream>
#include <fstream>
#include <sstream>

enum LogLevel{INFO, WARNING, SEVERE, DEBUG};

class Logger {
public:
    static void log(const string_t msg, LogLevel level = LogLevel::INFO);

private:
    static string_t format(const string_t str, LogLevel level);
};

#endif /* defined(__Serveur__Logger__) */
