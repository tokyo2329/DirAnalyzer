#include <iostream>
#include <thread>

#include "main.h"

auto main() -> int {

    auto _NUMBER_OF_THREADS{0};
    auto _PATH{"."};

    std::cout << "Please specify with how many threads should I work\n";
    std::cout << "(recommended value is " << std::thread::hardware_concurrency() << ", higher number is likely to crash!)\n";
    std::cin >> _NUMBER_OF_THREADS;

    if(_NUMBER_OF_THREADS <= 0) 
        _NUMBER_OF_THREADS = std::thread::hardware_concurrency();


    MultiThreadDirSearcher searcher{_NUMBER_OF_THREADS, _PATH};
    
    using namespace std::chrono;
    searcher.start();
    
    return 0;
}

