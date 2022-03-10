cmake_minimum_required(VERSION 3.0.0)
project(DirAnalyzer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp main.h)
target_link_libraries(${PROJECT_NAME} Threads::Threads)