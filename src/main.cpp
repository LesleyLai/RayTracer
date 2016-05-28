#include <iostream>
#include <chrono>


#include "parser/fileparser.hpp"
#include "scene/scene.hpp"

void printTotallyTimeCost(std::chrono::duration<double> elapsedTimes);

int main(int argc, char *argv[]) {
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    startTime = std::chrono::system_clock::now();

    if (argc < 2) {
        std::cout << "Please input a file:" << std::endl;
        std::string file_name;
        std::cin >> file_name;
        FileParser::readfile(file_name);
        return -1;
    } else {
        FileParser::readfile(argv[1]);
    }

    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTimes = endTime - startTime;

    printTotallyTimeCost(elapsedTimes);

    return 0;
}

void printTotallyTimeCost(std::chrono::duration<double> elapsedTimes) {
    std::chrono::seconds oneSecond(1);
    std::chrono::minutes tenminutes(10);

    std::cout << "It takes " ;

    if (elapsedTimes < tenminutes) {
    if (elapsedTimes < oneSecond) {
        std::cout << elapsedTimes.count();
    } else {
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(elapsedTimes).count();
    }
    std::cout << "s to complete the rendering" << std::endl;
    } else {
        std::cout << std::chrono::duration_cast<std::chrono::minutes>(elapsedTimes).count()
                  << "min to complete the rendering" << std::endl;

    }
}
