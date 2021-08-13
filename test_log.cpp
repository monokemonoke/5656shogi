#include "log.hpp"

int main() {
    Log log;
    log.displayLevel = LOG_WARN;
    log.displayTime = true;
    log.debug("this message is from test_log.cpp");
    log.displayTime = false;
    log.debug("this message is from test_log.cpp");
    log.debug("this message is from test_log.cpp");
    log.error("this message is from test_log.cpp");
    log.warn("this message is from test_log.cpp");
    log.info("this message is from test_log.cpp");
    log.error("this message is from test_log.cpp");
}