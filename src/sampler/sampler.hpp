#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include "sample.hpp"

class Sampler
{
public:
    Sampler(int width, int height);

    ///  It will generate (x,y) of a screen sample and return true. Next time it
    ///  gets called, it will generate another sample for the next pixel. It will
    ///  return false when all the samples from all the pixels are generated.
    bool getSample(Sample* sample);

private:
    int width_; ///< @brief How many pixels in a row
    int height_; ///< @brief How many pixels in a column

    int x_index_ = 0;
    int y_index_ = 0;
};

#endif // SAMPLER_HPP
