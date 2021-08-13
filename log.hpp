#ifndef LOG_HPP
#define LOG_HPP

#include <stdio.h>

#define BUFF_SIZE 256

#define LOG_DEBUG 40
#define LOG_INFO 30
#define LOG_WARN 20
#define LOG_ERROR 10

class Log {
   public:
    int displayLevel;
    bool displayTime;

    Log();
    void printNowTime();

    void debug(const char *content, ...);
    void info(const char *content, ...);
    void warn(const char *content, ...);
    void error(const char *content, ...);
};

#endif