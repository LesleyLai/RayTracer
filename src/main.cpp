#include <iostream>
#include <chrono>

int main(int argc, char *argv[]) {
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
    start_time = std::chrono::system_clock::now();

    // Do something

    end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    std::cout << "It takes " << elapsed_seconds.count() << "s to complete the rendering" << std::endl;

    return 0;
}
