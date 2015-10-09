#include "logger.h"
#include <sstream>

namespace log {
    Logger::Logger(unsigned int log_level) : log_level(log_level) {}

    //Syntactic sugar
    void Logger::operator<<(std::string &msg) {
        print(msg);
    }

    /*
       Fetches the LoggerSingleton instance and passes the  

     */
    void Logger::print(std::string &msg) {
        detail::LoggerSingleton::getInstance().print(log_level, msg);
    }

    Logger::~Logger() {}

    namespace detail {
        LoggerSingleton::LoggerSingleton() {
            setlogmask(LOG_UPTO(LOG_DEBUG)); //Include all log levels
            openlog(LOG_NAME, 
                    LOG_CONS | 
                    LOG_PID | 
                    LOG_PERROR, 
                    LOG_LOCAL1
                   );
        }

        void LoggerSingleton::print(unsigned int log_level, std::string &msg) {
            lock.lock();
            syslog(log_level, "%s", msg.c_str());
            lock.unlock();
        }

        LoggerSingleton::~LoggerSingleton() {
            closelog();
        }
    }

    Logger emerg(LOG_EMERG);
    Logger alert(LOG_ALERT);
    Logger crit(LOG_CRIT);
    Logger err(LOG_ERR);
    Logger warning(LOG_WARNING);
    Logger notice(LOG_NOTICE);
    Logger info(LOG_INFO);
    Logger debug(LOG_DEBUG);
}
