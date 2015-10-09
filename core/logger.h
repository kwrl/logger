#ifndef LOGGER_H
#define LOGGER_H

#define LOG_NAME "SEMEOTICONS"

#include <string>
#include <mutex>
#include <iostream>
#include <syslog.h>

/*
Usage:
#include "logger.h"
...
...
...
std::info << "Some info message";
std::debug << "Some debug message";
std::err << "Some error message";

 */

namespace log {
    /*
       This class is used to provide a simple and consistent interface
       for the LoggerSingleton. Predefined instances for working with
       each syslog log level are provided in the namespace.

       There should be no need to create any additional instances of this class.
     */
    class Logger {
        public:
            Logger(unsigned int);
            ~Logger();

            void operator<<( std::string& ); 
            void print( std::string& );

        private:
            unsigned int log_level;
    };

    namespace detail {
        /*
           Handles the opening and closing of syslog connections,
           and takes care of concurrency.
         */
        class LoggerSingleton {
            public:
                static LoggerSingleton& getInstance() {
                    static LoggerSingleton instance;
                    return instance;
                }

                void print( unsigned int, std::string& );

            private:
                LoggerSingleton(); 
                LoggerSingleton(LoggerSingleton const&); //Not to be implemented
                void operator=(LoggerSingleton const&); //Not to be implemented
                ~LoggerSingleton();
                std::mutex lock;
        };

    };

    extern Logger emerg;    //LOG_EMERG
    extern Logger alert;    //LOG_ALERT
    extern Logger crit;     //LOG_CRIT
    extern Logger err;      //LOG_ERR
    extern Logger warning;  //LOG_WARNING
    extern Logger notice;   //LOG_NOTICE
    extern Logger info;     //LOG_INFO
    extern Logger debug;    //LOG_DEBUG
}

#endif
