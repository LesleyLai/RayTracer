#include <iostream>
#include <chrono>

#include "scene/scene.hpp"

int main(int argc, char *argv[]) {
    std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
    start_time = std::chrono::system_clock::now();

    Scene scene(500, 500);

    scene.render();

    end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    std::chrono::seconds oneSecond(1);

    std::cout << "It takes " ;
    if (elapsed_seconds < oneSecond) {
        std::cout << elapsed_seconds.count();
    } else {
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(elapsed_seconds).count();
    }
    std::cout << "s to complete the rendering" << std::endl;

    return 0;
}
