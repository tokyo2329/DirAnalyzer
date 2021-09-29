cmake_minimum_required(VERSION 3.0.0)

add_executable(DirAnalyzerTests tests.cpp)
target_link_libraries(DirAnalyzerTests PUBLIC
    gtest_main
    DirAnalyzer
)

add_test(
    NAME DirAnalyzer
    COMMAND DirAnalyzer
)