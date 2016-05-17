#ifndef FILEPARSER_HPP
#define FILEPARSER_HPP

#include <string>
#include <array>

class Scene;

class FileParser {
public:
    static void readfile(std::string filename);
private:
    template <typename T, std::size_t N>
    static bool readvals(std::stringstream &s, std::array<T, N> &values);

    /// Add an camera to the sene according to the input
    static void addCamera(Scene &scene, const std::array<float, 10> &input_values);
};



#endif // FILEPARSER_HPP
