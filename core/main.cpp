#include "logger.h"
#include <thread>
#include <unistd.h>
#include <iostream>

#define ITERATIONS  10000

void print_info() {
    std::string msg = "Dette er info";
    for(int ii=0; ii<ITERATIONS; ii++) {
        log::info << msg;
        //sleep(1);
    }
}

void print_debug() {
    std::string msg = "Dette er emerg";
    for(int ii=0; ii<ITERATIONS; ii++) {
        log::emerg << msg; 
        //sleep(1);
    }
}

void print_err() {
    std::string msg = "Dette er err";
    for(int ii=0; ii<ITERATIONS; ii++) {
        log::err << msg; 
        //sleep(1);
    }
}

int main() {
    std::thread t1(print_info);
    std::thread t2(print_debug);
    std::thread t3(print_err);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
