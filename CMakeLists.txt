cmake_minimum_required(VERSION 2.8)
project(Logger)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package(Threads)

include_directories( core/  )

add_library(Log core/logger.cpp)
add_executable(Logger core/main.cpp)
target_link_libraries(Logger Log ${CMAKE_THREAD_LIBS_INIT})
