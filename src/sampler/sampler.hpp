#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <vector>

#include "sample.hpp"

class Sampler
{
public:
    Sampler(int width, int height);

    ///  Samples the pixels in a regular grid.
    std::vector<Sample> generateSampleSet();

private:
    int width_; ///< @brief How many pixels in a row
    int height_; ///< @brief How many pixels in a column
};

#endif // SAMPLER_HPP
