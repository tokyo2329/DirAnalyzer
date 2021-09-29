#include <gtest/gtest.h>
#include "../main.h"
#include <thread>
#include <filesystem>

std::filesystem::path starting_path = ".";
int number_of_threads = std::thread::hardware_concurrency();
MultiThreadDirSearcher object(number_of_threads, starting_path);

TEST(MultiThreadDirSearcher, InitializesProperly) {
    EXPECT_EQ(true, object.have_to_work);
    EXPECT_EQ(number_of_threads, object.number_of_threads);
    EXPECT_EQ(0, object.get_file_number());
    EXPECT_EQ(0, object.get_directories_number());
}

TEST(MultiThreadDirSearcher, AddsToDirectoriesVector) {
    object.add_to_directories("/examplepath/");
    EXPECT_EQ("/examplepath/", object.get_directory());
}

TEST(MultiThreadDirSearcher, IncrementsFileNumber) {
    int before = object.get_file_number();
    int increment_by = 5;
    object.increment_file_number(increment_by);
    int after = object.get_file_number();
    EXPECT_EQ(before+increment_by, after);

    before = after;
    increment_by = 15;
    object.increment_file_number(increment_by);
    after = object.get_file_number();
    EXPECT_EQ(before+increment_by, after);
}

TEST(MultiThreadDirSearcher, IncrementsDirectoriesNumber) {
    int before = object.get_directories_number();
    int increment_by = 5;
    object.increment_directories_number(increment_by);
    int after = object.get_directories_number();
    EXPECT_EQ(before+increment_by, after);

    before = after;
    increment_by = 15;
    object.increment_directories_number(increment_by);
    after = object.get_directories_number();
    EXPECT_EQ(before+increment_by, after);
}

TEST(MultiThreadDirSearcher, ChecksIfVectorIsEmpty) {
    EXPECT_EQ(true, object.is_empty());
    object.add_to_directories("/test/");
    EXPECT_EQ(false, object.is_empty());
}

TEST(MultiThreadDirSearcher, GetsDirectory) {
    std::filesystem::path dir = "/example/directory/";
    object.add_to_directories(dir);
    auto value = object.get_directory();
    EXPECT_EQ(dir, value);
}