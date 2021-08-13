#include "log.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Log::Log() {
    Log::displayTime = false;
    Log::displayLevel = LOG_DEBUG;
}

// warning: この関数はかなり時間がかかる.
void Log::printNowTime() {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int year = local->tm_year + 1900;
    int month = local->tm_mon + 1;
    printf("%04d/%02d/%02d ", year, month, local->tm_mday);
    printf("%02d:%02d:%02d ", local->tm_hour, local->tm_min, local->tm_sec);
}

void Log::debug(const char *content, ...) {
    if (Log::displayLevel < LOG_DEBUG) return;
    char buff[BUFF_SIZE];
    va_list args;
    va_start(args, content);

    vsprintf(buff, content, args);

    if (Log::displayTime) Log::printNowTime();
    printf("DEBUG : %s\n", buff);

    va_end(args);
}

void Log::info(const char *content, ...) {
    if (Log::displayLevel < LOG_INFO) return;
    char buff[BUFF_SIZE];
    va_list args;
    va_start(args, content);

    vsprintf(buff, content, args);

    printf("\x1b[36m");
    if (Log::displayTime) Log::printNowTime();
    printf("INFO  : %s\n", buff);
    printf("\x1b[39m");

    va_end(args);
}

void Log::warn(const char *content, ...) {
    if (Log::displayLevel < LOG_WARN) return;
    char buff[BUFF_SIZE];
    va_list args;
    va_start(args, content);

    vsprintf(buff, content, args);

    printf("\x1b[33m");
    if (Log::displayTime) Log::printNowTime();
    printf("WARN  : %s\n", buff);
    printf("\x1b[39m");

    va_end(args);
}

void Log::error(const char *content, ...) {
    if (Log::displayLevel < LOG_ERROR) return;
    char buff[BUFF_SIZE];
    va_list args;
    va_start(args, content);

    vsprintf(buff, content, args);

    printf("\x1b[31m");
    if (Log::displayTime) Log::printNowTime();
    printf("ERROR : %s \x1b[39m \n", buff);
    printf("\x1b[39m");

    va_end(args);
}