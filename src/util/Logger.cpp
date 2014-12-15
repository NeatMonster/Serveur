#include "Logger.h"

#include <iomanip>
#include <fstream>

Logger::Logger(Logger::Level level) {
    lock = std::unique_lock<std::mutex>(mutex);
    time_t now = ::time(0);
    tm *ltm = localtime(&now);
    *this << std::setfill('0') << "[" << std::setw(2) << ltm->tm_hour << ":"
        << std::setw(2) << ltm->tm_min << ":" << std::setw(2) << ltm->tm_sec << " ";
    switch (level) {
        case Level::INFO:
            *this << "INFO] ";
            break;
        case Level::WARNING:
            *this << "WARNING] ";
            break;
        case Level::SEVERE:
            *this << "SEVERE] ";
            break;
        case Level::DEBUG:
            *this << "DEBUG] ";
            break;
    }
}

Logger::~Logger() {
    std::cout << str();
    std::ofstream logFile("log.txt", std::ios::app | std::ios::ate);
    logFile << str();
    logFile.close();
    lock.unlock();
}

std::mutex Logger::mutex;
