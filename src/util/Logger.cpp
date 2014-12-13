#include "Logger.h"
#include <iomanip>

string_t Logger::format(const string_t str, LogLevel level)
{
    std::stringstream ss;
    time_t now = ::time(0);
    tm *ltm = localtime(&now);
    ss << std::setfill('0') << "[" << std::setw(2) << ltm->tm_hour << ":"
        << std::setw(2) << ltm->tm_min << ":" << std::setw(2) << ltm->tm_sec << " ";
    switch (level)
    {
    case LogLevel::INFO:
        ss << "INFO";
        break;

    case LogLevel::WARNING:
        ss << "WARNING";
        break;

    case LogLevel::SEVERE:
        ss << "SEVERE";
        break;

    case LogLevel::DEBUG:
        ss << "SEVERE";
        break;
    }

    ss << "] " << str;
    return ss.str();
}

void Logger::log(const string_t str, LogLevel level)
{
    //Formatage du log avec la date.
    string_t out = format(str, level);

    //On écrit les données dans un fichier et dans la console et on referme le flux fichier.
    std::ofstream ofs("log.txt", std::ios::app | std::ios::ate);
    ofs << out << std::endl;
    std::cout << out << std::endl;
    ofs.close();
}
