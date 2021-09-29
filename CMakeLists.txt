cmake_minimum_required(VERSION 3.0.0)
project(DirAnalyzer VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(DirAnalyzer main.cpp)

target_link_libraries( DirAnalyzer
    pthread
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(googletest)

add_subdirectory(test)