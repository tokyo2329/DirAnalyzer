#include <iostream>
#include <filesystem>
#include <thread>
#include <future>
#include <vector>

class MultiThreadDirSearcher {

public:
    MultiThreadDirSearcher(int max_threads, std::filesystem::path starting_path)
        : have_to_work{true}, number_of_threads{max_threads}, starting_path{starting_path} {}
        
    ~MultiThreadDirSearcher() {
        
        for(auto& th : threads) {
            th.join();
        }

        have_to_work = false;

        stop_timer = std::chrono::high_resolution_clock::now();

        print_values();
        std::cout<<"#########################################\n";
        std::cout<<"##   MultiThreadDirSearcher is done    ##\n";
        std::cout<<"#########################################\n";
    }

    void start() {
        std::cout<<"#########################################\n";
        std::cout<<"## Initializing MultiThreadDirSearcher ##\n";
        std::cout<<"##     tool created by Mateusz Kociola ##\n";
        std::cout<<"#########################################\n";
        std::cout<<"...with "<<number_of_threads<<" thread(s)\n\n";

        start_timer = std::chrono::high_resolution_clock::now();

        add_to_directories(starting_path);

        for(int i=0; i<number_of_threads; i++) {
            threads.push_back(std::thread(&MultiThreadDirSearcher::searchDir, this));
        }
    }

    auto print_values() const -> void {
        auto time_it_took = std::chrono::duration_cast<std::chrono::milliseconds>(stop_timer - start_timer);
        std::cout<<"Number of files: "<<number_of_files<<std::endl;
        std::cout<<"Number of directories: "<<number_of_directories<<std::endl;
        std::cout<<"Overall number of lines: "<<number_of_directories+number_of_files<<std::endl;
        std::cout<<"It took: "<<time_it_took.count()<<" miliseconds"<<std::endl;
    }

    auto add_to_directories(std::filesystem::path path) -> void {
        std::unique_lock<std::mutex> lock(dir_vector_mt);
        directories_to_work_on.push_back(path);
    }

    auto increment_file_number(int value) -> void {
        std::unique_lock<std::mutex> lock(file_number_mt);
        number_of_files += value;
    }

    auto get_file_number() -> int{
        std::unique_lock<std::mutex> lock(file_number_mt);
        return number_of_files;
    }

    auto increment_directories_number(int value) -> void {
        std::unique_lock<std::mutex> lock(directories_number_mt);
        number_of_directories += value;
    }

    int get_directories_number() {
        std::unique_lock<std::mutex> lock(directories_number_mt);
        return number_of_directories;
    }

    bool is_empty() {
        std::unique_lock<std::mutex> lock(dir_vector_mt);

        return directories_to_work_on.empty() ? true : false;
    }

    std::filesystem::path get_directory() {
        std::unique_lock<std::mutex> lock(dir_vector_mt);
        auto p = directories_to_work_on.back();
        directories_to_work_on.pop_back();
        return p;
    }

    // atomics
    std::atomic<bool> have_to_work;

    // vectors
    std::vector<std::thread> threads;

    // starting values
    int number_of_threads{0};
    std::filesystem::path starting_path;

private:
    int number_of_files{0}, number_of_directories{0};

    // time
    std::chrono::time_point<std::chrono::system_clock> start_timer;
    std::chrono::time_point<std::chrono::system_clock> stop_timer;

    // vectos
    std::vector<std::filesystem::path> directories_to_work_on;

    // mutexes
    std::mutex dir_vector_mt;
    std::mutex file_number_mt;
    std::mutex directories_number_mt;

    // a thread loop
    void searchDir();

};

void MultiThreadDirSearcher::searchDir() {

    while(have_to_work) {

        if(!is_empty()) {

            auto current_path = get_directory();

            int current_number_of_files = 0, current_number_of_directories = 0;

            try
            {
                for(auto& file : std::filesystem::directory_iterator(current_path, std::filesystem::directory_options::skip_permission_denied)) {

                    if(file.is_directory()) {
                        current_number_of_directories++;
                        add_to_directories(file.path());
                    } else {
                        current_number_of_files++;
                    }

                }
                
            }
            catch(const std::exception& e)
            {
            }
            


            increment_file_number(current_number_of_files);
            increment_directories_number(current_number_of_directories);
        } else break;


    }
    
}